namespace RangeFinder
{
    public class ComPort
    {
        public string Name { get; }
        public string Device { get; }

        public string FullName => $"{Name} ({Device})";

        public ComPort((string, string) port)
        {
            Name = port.Item1;
            Device = port.Item2;
        }
    }
}
