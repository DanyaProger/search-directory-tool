using Microsoft.Extensions.Configuration;

namespace SD.Tests
{
    internal class TestsConfiguration
    {
        static private string totalCmdExe;
        static private string bashExe;
        static TestsConfiguration()
        {
            DirectoryInfo directory = new DirectoryInfo(Directory.GetCurrentDirectory());
            while (directory != null && !directory.GetFiles("*.csproj").Any())
            {
                directory = directory.Parent;
            }
            if (directory == null)
                throw new NullReferenceException();
            IConfiguration configuration = new ConfigurationBuilder().AddJsonFile(Path.Combine(directory.FullName, "testsettings.json")).Build();

            loadConfiguration(configuration);
        }

        static void loadConfiguration(IConfiguration configuration)
        {
            BashExe = configuration["bash"];
            TotalCmdExe = configuration["totalcmd"];
        }

        public static string TotalCmdExe
        {
            get
            {
                return totalCmdExe;
            }
            private set
            {
                if (value == null)
                    throw new NullReferenceException();
                totalCmdExe = value;
            }
        }

        public static string BashExe
        {
            get
            {
                return bashExe;
            }
            private set
            {
                if (value == null)
                    throw new NullReferenceException();
                bashExe = value;
            }
        }
    }
}
