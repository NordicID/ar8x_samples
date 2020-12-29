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
        static int PrintUsage()
        {
            Console.WriteLine("USAGE: ar_signtool_cli 'input file or folder' [output zip]");
            Console.WriteLine("  output file may contain values from package manifest, e.g. ar8x_{name}_v{version}.zip");
            return 1;
        }

        static int Main(string[] args)
        {
            Console.WriteLine("ar_signtool_cli " + Assembly.GetExecutingAssembly().GetName().Version.ToString());

            if (args.Length < 1)
            {
                PrintUsage();
                return 1;
            }

            try
            {
                string input = null;
                string output = null;

                for (int n=0; n<args.Length; n++)
                {
                    if (input == null)
                        input = args[n];
                    else if (output == null)
                        output = args[n];
                    else
                    {
                        Console.WriteLine("Invalid argument: " + args[n]);
                        return PrintUsage();
                    }
                }

                if (input == null) {
                    Console.WriteLine("Missing input file argument");
                    return PrintUsage();
                }

                // Strip trailing slash
                if (input.EndsWith(Path.DirectorySeparatorChar.ToString()))
                {
                    input = input.Remove(input.Length - 1);
                }
                FileInfo inputFi = new FileInfo(input);

                if (output == null) {
                    output = System.Environment.CurrentDirectory + Path.DirectorySeparatorChar + Path.GetFileNameWithoutExtension(inputFi.Name) + "_signed.zip";
                }
                Console.WriteLine("Input: " + input);
                Console.WriteLine("Output: " + output);

                if (inputFi.Attributes.HasFlag(FileAttributes.Directory))
                {
                    Console.WriteLine("Signing folder, please wait...");
                    ar8x_appsignlib.ar8x_appsignlib.SignFolder(input, output);
                }
                else
                {
                    Console.WriteLine("Signing zip, please wait...");
                    ar8x_appsignlib.ar8x_appsignlib.SignZipFile(input, output);
                }

                if (ar8x_appsignlib.ar8x_appsignlib.LastSignedManifest != null)
                {
                    // Substitute variables from package manifest
                    string finalOutput = output;
                    Console.WriteLine("Package manifest:");
                    foreach (var pair in ar8x_appsignlib.ar8x_appsignlib.LastSignedManifest)
                    {
                        Console.WriteLine($" {pair.Key} = '{pair.Value}'");
                        finalOutput = finalOutput.Replace($"{{{pair.Key}}}", pair.Value);
                    }
                    if (finalOutput != output)
                    {
                        if (File.Exists(finalOutput))
                            File.Delete(finalOutput);
                        File.Move(output, finalOutput);
                        Console.WriteLine("Final output: " + finalOutput);
                    }
                } 
                else
                {
                    Console.WriteLine("WARNING: Missing or invalid properties/manifest file in package");
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
