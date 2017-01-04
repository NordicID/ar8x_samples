using Backend.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading;
using System.ServiceModel.Web;
using System.IO;
using Newtonsoft.Json;
using System.Reflection;

namespace NormaConfig
{
    public partial class WcfEntryPoint : WcfInterface
    {
        public String Ping()
        {
            Console.WriteLine("Ponging");
            return "Pong";
        }

        private bool VerifyContent(List<Device> items)
        {
            foreach (Device item in items)
            {
                if (item.Reader.ClientPort <= 0)
                    return false;
                // ReaderPort -1 when "disabled"
                /*if (item.Reader.ReaderPort <= 0)
                    return false;*/
                if (item.Reader.ReaderAddress.StartsWith("null") || item.Reader.ReaderAddress == "" || item.Reader.ReaderAddress.Length <= 1)
                    return false;
            }
            return true;
        }

        public bool SetDevices(List<Device> items)
        {
            Console.WriteLine("SetDevices");
            if (!VerifyContent(items))
                return false;
            string path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            DeviceObject obj = new DeviceObject();
            obj.Devices = items;
            string content = JsonConvert.SerializeObject(obj);
            File.WriteAllText(path + "/Config.json", content);
            return true;
        }
        public List<Device> GetDevices()
        {
            string path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            if (!File.Exists(path + "/Config.json"))
            {
                Console.WriteLine("Config file does not exist");
                return null;
            }

            string content = File.ReadAllText(path + "/Config.json");
            DeviceObject tim = JsonConvert.DeserializeObject<DeviceObject>(content);
            return tim.Devices;
        }

        public DeviceStatusObject GetDeviceSetup(string deviceId)
        {
            string path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            if (!File.Exists(path + "/" + deviceId + ".json"))
            {
                Console.WriteLine("Device info file does not exist");
                return null;
            }
                
            string content = File.ReadAllText(path + "/" + deviceId + ".json");
            DeviceStatusObject ret = JsonConvert.DeserializeObject<DeviceStatusObject>(content);
            return ret;
        }

        public List<DeviceStatusObject> GetDeviceSetupAll()
        {
            List<DeviceStatusObject> devices = new List<DeviceStatusObject>();
            string path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);

            string[] files = Directory.GetFiles(path);
            foreach (string s in files)
            {
                Console.WriteLine("GetDevicesStatus " + s);
                if (s.EndsWith(".json") && !s.Contains("Config.json"))
                {
                    string content = File.ReadAllText(s);
                    try
                    {
                        devices.Add(JsonConvert.DeserializeObject<DeviceStatusObject>(content));
                    }
                    catch(Exception ex)
                    {
                        Console.WriteLine("Error converting " + s + " to device status object: " + ex.Message);
                    }
                }
            }

            /*if (!File.Exists(path + "/Config.json"))
                Console.WriteLine("Config file does not exist");*/

            return devices;
        }

        public string GetLog()
        {
            string ret = "";
            string path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            if (!File.Exists(path + "/Norma.log"))
            {
                Console.WriteLine("Log file does not exist");
                return "Log file " + path + "/Norma.log does not exist";
            }

            FileStream fs = null;
            StreamReader rd = null;
            try
            {
                fs = File.OpenRead(path + "/Norma.log");
                rd = new StreamReader(fs, Encoding.UTF8);
                ret = rd.ReadToEnd();
            }
            catch (Exception e)
            {
                ret = e.ToString();
            }
            finally
            {
                if (rd != null)
                    rd.Close();
                if (fs != null)
                    fs.Close();
            }
            return ret;
        }

        public NormaStatus GetDeviceStatusAll()
        {
            string path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            if (!File.Exists(path + "/NormaStatus.log"))
            {
                Console.WriteLine("NormaStatus does not exist");
                return null;
            }

            string content = File.ReadAllText(path + "/NormaStatus.log");
            NormaStatus ret = JsonConvert.DeserializeObject<NormaStatus>(content);
            bool found = false;
            if (ret != null && ret.Instances.ReaderStatus != null && ret.Instances.ReaderStatus.Count > 0)
            {
                List<Device> configureDevices = GetDevices();
                for (int i = ret.Instances.ReaderStatus.Count - 1; i >= 0; i--)
                {
                    found = false;
                    foreach (Device dev in configureDevices)
                    {
                        Console.WriteLine("GetDeviceStatusAll " + dev.Reader.ReaderAddress + " " + ret.Instances.ReaderStatus[i].InstanceName);
                        if (ret.Instances.ReaderStatus[i].InstanceName.StartsWith(dev.Reader.ReaderAddress))
                        {
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        ret.Instances.ReaderStatus.RemoveAt(i);
                }
            }

            return ret;
        }
        public NormaStatus GetDeviceStatus(string deviceId)
        {
            bool found = false;
            NormaStatus stat = GetDeviceStatusAll();
            if (stat != null && stat.Instances != null && stat.Instances.ReaderStatus != null && stat.Instances.ReaderStatus.Count > 0)
            {
                for (int i = stat.Instances.ReaderStatus.Count; i >= 0; i--)
                {
                    if (stat.Instances.ReaderStatus[i].InstanceName != deviceId)
                    {
                        stat.Instances.ReaderStatus.RemoveAt(i);
                    }
                    else
                        found = true;
                }
            }
            if (found)
                return stat;
            else
                return null;
        }

        public void GetOptions()
        {
            WebOperationContext.Current.OutgoingResponse.Headers.Add("Access-Control-Allow-Origin", "*");
            WebOperationContext.Current.OutgoingResponse.Headers.Add("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
            WebOperationContext.Current.OutgoingResponse.Headers.Add("Access-Control-Allow-Headers", "Content-Type");
        }
    }

    public class Program
    {
        static public Dictionary<string, Type> ServiceDesc = new Dictionary<string, Type>();

        static void Main(string[] args)
        {
            StaticInitHelper.Run(true);

            ServiceHost svcHost = null;
            try
            {
                string URL = "http://127.0.0.1:10123/app/backend/norma";
                svcHost = SelfHost.Create(URL,
                    typeof(WcfEntryPoint), typeof(WcfInterface));
            }
            catch (Exception eX)
            {
                svcHost = null;
                Console.WriteLine("Service can not be started \n\nError Message [" + eX.Message + "]");
            }

            if (svcHost != null)
            {
                Console.WriteLine("Running");
                for (;;)
                    Thread.Sleep(1000);
                /*
                Console.WriteLine("\nPress any key to close the Service");
				for (;;) {
					ConsoleKeyInfo i = Console.ReadKey ();
					if (i.KeyChar != '\0')
						break;
					Thread.Sleep (100);
				}*/
                svcHost.Close();
                svcHost = null;
            }

            StaticInitHelper.Run(false);
        }
    }
}
