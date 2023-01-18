using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Management;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;

namespace RangeFinder
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("EApi64.dll", EntryPoint = "AXLibInitialize")]
        public static extern UInt32 AXLibInitialize64();

        [DllImport("EApi64.dll", EntryPoint = "AXBoardGetValue")]
        public static extern UInt32 AXBoardGetValue64(UInt32 ID, ref byte BOARD_DIO, ref UInt32 BufLen, ref UInt32 index, ref UInt32 pValue);

        [DllImport("EApi64.dll", EntryPoint = "AXBoardSetValue")]
        public static extern UInt32 AXBoardSetValue64(UInt32 ID, ref UInt32 pBuffer, ref UInt32 BufLen, ref UInt32 index, ref UInt32 pValue);

        [DllImport("EApi64.dll", EntryPoint = "AXBoardGetStringA")]
        public static extern UInt32 AXBoardGetStringA64(UInt32 Id, ref byte pBuffer, ref UInt32 pBufLen);

        [DllImport("EApi32.dll", EntryPoint = "AXLibInitialize")]
        public static extern UInt32 AXLibInitialize32();

        [DllImport("EApi32.dll", EntryPoint = "AXBoardGetValue")]
        public static extern UInt32 AXBoardGetValue32(UInt32 ID, ref byte BOARD_DIO, ref UInt32 BufLen, ref UInt32 index, ref UInt32 pValue);

        [DllImport("EApi32.dll", EntryPoint = "AXBoardSetValue")]
        public static extern UInt32 AXBoardSetValue32(UInt32 ID, ref UInt32 pBuffer, ref UInt32 BufLen, ref UInt32 index, ref UInt32 pValue);

        [DllImport("EApi32.dll", EntryPoint = "AXBoardGetStringA")]
        public static extern UInt32 AXBoardGetStringA32(UInt32 Id, ref byte pBuffer, ref UInt32 pBufLen);

        public delegate UInt32 AXLibInitialize_F();
        public delegate UInt32 AXBoardGetValue_F(UInt32 ID, ref byte BOARD_DIO, ref UInt32 BufLen, ref UInt32 index, ref UInt32 pValue);
        public delegate UInt32 AXBoardSetValue_F(UInt32 ID, ref UInt32 pBuffer, ref UInt32 BufLen, ref UInt32 index, ref UInt32 pValue);
        public delegate UInt32 AXBoardGetStringA_F(UInt32 Id, ref byte pBuffer, ref UInt32 pBufLen);

        AXLibInitialize_F AXLibInitialize;
        AXBoardGetValue_F AXBoardGetValue;
        AXBoardSetValue_F AXBoardSetValue;
        AXBoardGetStringA_F AXBoardGetStringA;

        private UInt32 EAPI_STATUS_SUCCESS = 0x00;

        // ************* Get Board String *************
        private UInt32 EAPI_ID_BOARD_MANUFACTURER_STR = 0;  /* Board Manufacturer Name String */
        private UInt32 EAPI_ID_BOARD_NAME_STR = 1;          /* Board Name String */
        private UInt32 EAPI_ID_BOARD_BIOS_REVISION_STR = 4; /* Board Bios Revision String */

        private static UInt32 ProductResult;

        // ************* Monitoring *************
        private UInt32 EAPI_ID_BOARD_SENSOR_COUNTER_TEMP = 12;
        private UInt32 EAPI_ID_BOARD_SENSOR_TEMP = 13;
        private UInt32 EAPI_ID_BOARD_SENSOR_COUNTER_VOLTAGE = 14;
        private UInt32 EAPI_ID_BOARD_SENSOR_VOLTAGE = 15;
        private UInt32 EAPI_ID_BOARD_SENSOR_COUNTER_FAN = 16;
        private UInt32 EAPI_ID_BOARD_SENSOR_FAN = 17;

        private static UInt32 TempResult;
        private static UInt32 TempCounter = 0;
        private static UInt32 VolResult;
        private static UInt32 VolCounter = 0;
        private static UInt32 FanResult;
        private static UInt32 FanCounter = 0;

        private static UInt32 pIndex = 0;

        // ************* DigitalIO *************
        private UInt32 EAPI_ID_BOARD_SENSOR_COUNTER_DIO_INTERNAL = 31;
        private UInt32 EAPI_ID_BOARD_SENSOR_GET_DIO_INTERNAL = 32;
        private UInt32 EAPI_ID_BOARD_SENSOR_SET_DIO_INTERNAL = 32;

        private readonly byte[] _getRange = new byte[] { 0x80, 0x06, 0x02, 0x78 };
        private readonly byte[] _turnOnLaser = new byte[] { 0x80, 0x06, 0x05, 0x01, 0x74 };
        private readonly byte[] _turnOffLaser = new byte[] { 0x80, 0x06, 0x05, 0x00, 0x75 };
        private readonly byte[] _setResolution1 = new byte[] { 0xFA, 0x04, 0x0C, 0x01, 0xF5 };
        private readonly byte[] _setResolution01 = new byte[] { 0xFA, 0x04, 0x0C, 0x02, 0xF4 };

        private readonly List<ComPort> _comPorts = new List<ComPort>();
        private static readonly SerialPort SerialPort = new SerialPort();
        private const int _messageSize = 12;
        private int[] _byteMessage = new int[12];
        private int _bytesRead = 0;
        private Stopwatch _stopwatch = new Stopwatch();
        private Mutex _DIOMutex;

        public MainWindow()
        {
            InitializeComponent();

            _DIOMutex = new Mutex(true, "DIOMutex");
            _DIOMutex.ReleaseMutex();

            if (IntPtr.Size == 4)
            {
                // 32 bit
                AXLibInitialize = AXLibInitialize32;
                AXBoardGetValue = AXBoardGetValue32;
                AXBoardSetValue = AXBoardSetValue32;
                AXBoardGetStringA = AXBoardGetStringA32;
            }
            else
            {
                // 64 bit
                AXLibInitialize = AXLibInitialize64;
                AXBoardGetValue = AXBoardGetValue64;
                AXBoardSetValue = AXBoardSetValue64;
                AXBoardGetStringA = AXBoardGetStringA64;
            }

            if (AXLibInitialize() != EAPI_STATUS_SUCCESS)
            {
                MessageBox.Show("Initial Library is failed(EApi)");
            }

            bool type = true;
            bool status = true;
            var res = GetDIOpinStatus(0, ref type, ref status);
            var res1 = GetDIOpinStatus(1, ref type, ref status);
            File.AppendAllText("logs.txt", $"{res} --- {res1}");

            int dioCount = 0;
            GetDIOCount(ref dioCount);

            DataContext = this;

            FindPorts();
            var rangefinderPort = _comPorts.FirstOrDefault();

            SerialPort.BaudRate = 9600;
            SerialPort.DataBits = 8;
            SerialPort.Parity = Parity.None;
            SerialPort.DataReceived += DataReceivedHandler;
            SerialPort.PortName = rangefinderPort?.Name ?? "COM1";
            SerialPort.Open();
        }

        private static (string, string)? ParseComName(ManagementBaseObject obj)
        {
            var name = obj["Name"]?.ToString();
            if (name == null)
            {
                return null;
            }

            var device = obj["Description"]?.ToString();
            var startIndex = name.LastIndexOf("(");
            var endIndex = name.LastIndexOf(")");

            if (startIndex == -1 || endIndex == -1) return null;

            name = name.Substring(startIndex + 1, endIndex - startIndex - 1);

            return (name, device);
        }

        private void FindPorts()
        {
            try
            {
                var searcher = new ManagementObjectSearcher("root\\CIMV2", "SELECT * FROM Win32_PnPEntity");

                foreach (var obj in searcher.Get())
                {
                    var managementObject = (ManagementObject)obj;
                    if (managementObject != null
                        && (managementObject["Caption"] == null
                        || !managementObject["Caption"].ToString().Contains("COM")))
                        continue;

                    var port = ParseComName(managementObject);
                    if (port != null)
                    {
                        _comPorts.Add(new ComPort(ParseComName(managementObject).Value));
                    }
                }
            }
            catch (Exception ex)
            {
                File.AppendAllText("logs.txt", ex.Message);
            }
        }

        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs args)
        {
            try
            {
                var elapsedTime = _stopwatch.Elapsed;

                var bytesToRead = SerialPort.BytesToRead;

                var answer = new StringBuilder();
                for (int i = 0; i < bytesToRead; i++)
                {
                    _byteMessage[_bytesRead] = SerialPort.ReadByte();

                    _bytesRead++;
                }

                if (_bytesRead == _messageSize)
                {
                    _stopwatch.Stop();

                    var convertedBytes = _byteMessage.Select(x => x.ToString("X")).ToArray();
                    var stringMessage = string.Join(" ", convertedBytes);
                    File.AppendAllText("answer.txt", $"{stringMessage}\n");

                    var bytes = _byteMessage.Select(x => BitConverter.GetBytes(x)[0]).ToArray();
                    var message = new byte[8];
                    Array.Copy(bytes, 3, message, 0, message.Length);
                    var textAnswer = Encoding.ASCII.GetString(message);

                    Dispatcher.Invoke(() => AnswerTextBox.AppendText($"{textAnswer} м ({elapsedTime.TotalSeconds:N2} сек.)\n"));

                    _bytesRead = 0;
                    Array.Clear(_byteMessage, 0, _byteMessage.Length);
                }

            }
            catch (Exception ex)
            {
                File.AppendAllText("logs.txt", ex.Message + ex.StackTrace);
            }
        }

        private void GetRangeButton_Click(object sender, RoutedEventArgs e)
        {
            _stopwatch.Restart();
            ExecuteCommand(_getRange);
        }

        private void TurnOnLaserButton_Click(object sender, RoutedEventArgs e)
        {
            ExecuteCommand(_turnOnLaser);
        }

        private void TurnOffLaserButton_Click(object sender, RoutedEventArgs e)
        {
            ExecuteCommand(_turnOffLaser);
        }

        private void Resolution1Button_Click(object sender, RoutedEventArgs e)
        {
            ExecuteCommand(_setResolution1);
        }

        private void Resolution01Button_Click(object sender, RoutedEventArgs e)
        {
            ExecuteCommand(_setResolution01);
        }

        private void ExecuteCommand(byte[] command)
        {
            SerialPort.Write(command, 0, command.Length);
        }

        private void Pin1CheckBox_Checked(object sender, RoutedEventArgs e)
        {
            try
            {
                var checkBox = (CheckBox)sender;
                _DIOMutex.WaitOne();
                SetDOStatus(1, checkBox.IsChecked.Value);
                _DIOMutex.ReleaseMutex();
            }
            catch(Exception ex)
            {
                File.AppendAllText("logs.txt", ex.Message + ex.StackTrace);
            }
        }

        private bool SetDOStatus(int DIO_index, bool status)
        {
            UInt32[] BOARD_DIO = new UInt32[64];
            UInt32 BufLen = (UInt32)BOARD_DIO.Length;
            UInt32 u32Status = (UInt32)(status ? 0x1 : 0x0);
            UInt32 u32Index = Convert.ToUInt32(DIO_index);
            uint r = AXBoardSetValue(EAPI_ID_BOARD_SENSOR_SET_DIO_INTERNAL, ref BOARD_DIO[0], ref BufLen, ref u32Index, ref u32Status);
            if (r == EAPI_STATUS_SUCCESS)
            {
                return true;
            }
            return false;
        }

        private bool GetDIOpinStatus(int DIO_index, ref bool type, ref bool status)
        {
            byte[] BOARD_DIO = new byte[64];
            UInt32 BufLen = (UInt32)BOARD_DIO.Length;
            UInt32 u32Status = 0;
            UInt32 u32Index = (UInt32)DIO_index;
            uint r = AXBoardGetValue(EAPI_ID_BOARD_SENSOR_GET_DIO_INTERNAL, ref BOARD_DIO[0], ref BufLen, ref u32Index, ref u32Status);
            if (r == EAPI_STATUS_SUCCESS)
            {
                type = (u32Index == 1) ? true : false;
                status = (u32Status == 1) ? true : false;
                return true;
            }
            return false;
        }

        private bool GetDIOCount(ref int count)
        {
            byte[] BOARD_DIO = new byte[64];
            UInt32 BufLen = (UInt32)BOARD_DIO.Length;
            UInt32 u32Value = 0;
            UInt32 u32Index = 0;
            uint r = AXBoardGetValue(EAPI_ID_BOARD_SENSOR_COUNTER_DIO_INTERNAL, ref BOARD_DIO[0], ref BufLen, ref u32Index, ref u32Value);
            if (r == EAPI_STATUS_SUCCESS)
            {
                count = (int)u32Value;
                return true;
            }
            return false;
        }
    }
}
