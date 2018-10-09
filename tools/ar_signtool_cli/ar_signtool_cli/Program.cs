using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace ar_signtool_cli
{
    class Program
    {
        static int Main(string[] args)
        {
            Console.WriteLine("ar_signtool_cli " + Assembly.GetExecutingAssembly().GetName().Version.ToString());

            if (args.Length < 1)
            {
                Console.WriteLine("USAGE: ar_signtool_cli 'input file or folder' [output zip]");
                return 1;
            }

            try
            {
                string input = args[0];

                // Strip trailing slash
                if (input.EndsWith(Path.DirectorySeparatorChar.ToString())) {
                    input = input.Remove(input.Length - 1);
                }

                FileInfo inputFi = new FileInfo(input);

                string output = args.Length > 1 ? args[1] : null;
                if (output == null) {
                    output = System.Environment.CurrentDirectory + Path.DirectorySeparatorChar + Path.GetFileNameWithoutExtension(inputFi.Name) + "_signed.zip";
                }
                Console.WriteLine("Input: " + input);
                Console.WriteLine("Output: " + output);
                Console.WriteLine("");

                if (inputFi.Attributes == FileAttributes.Directory)
                {
                    Console.WriteLine("Signing folder, please wait...");
                    ar8x_appsignlib.ar8x_appsignlib.SignFolder(input, output);
                }
                else
                {
                    Console.WriteLine("Signing zip, please wait...");
                    ar8x_appsignlib.ar8x_appsignlib.SignZipFile(input, output);
                }
                Console.WriteLine("Done");

                return 0;
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine("ERROR:");
                Console.Error.WriteLine(ex.ToString());
                return 5;
            }
        }
    }
}
