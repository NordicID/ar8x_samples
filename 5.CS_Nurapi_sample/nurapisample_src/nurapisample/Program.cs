using Backend.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading;
using System.ServiceModel.Web;
using NurApiDotNet;
using Nmqtt;

namespace nurapisample
{
    public partial class WcfEntryPoint : WcfInterface
    {
        public List<string> GetInventoryResults()
        {
            return Program.GetInventoryResults();
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
        static private NurApi hNur;
        static List<string> inventoryResults = new List<string>();
        static MqttClient client = null;
        static void Main(string[] args)
        {
            StaticInitHelper.Run(true);

            ServiceHost svcHost = null;
            try
            {
                string URL = "http://127.0.0.1:10011/app/backend/nurapisample";
                svcHost = SelfHost.Create(URL,
                    typeof(WcfEntryPoint), typeof(WcfInterface));
            }
            catch (Exception ex)
            {
                svcHost = null;
                Console.WriteLine("Service can not be started \n\nError Message [" + ex.Message + "]");
            }

            try
            {
                // init the nurapi instance
                hNur = new NurApi();
                // add the events we need
                hNur.InventoryStreamEvent += HNur_InventoryStreamEvent;
                hNur.ConnectedEvent += HNur_ConnectedEvent;
                hNur.DisconnectedEvent += HNur_DisconnectedEvent;
                // connect to the local instance(127.0.0.1:4333 is the default setting, modify this to fit your needs)
                hNur.ConnectSocket("127.0.0.1", 4333);
            }
            catch (Exception eX)
            {
                svcHost = null;
                Console.WriteLine("Could not init NurApi instance [" + eX.Message + "]");
            }

            try
            {
                client = new Nmqtt.MqttClient("localhost", 1883, "nurapisample");
                ConnectionState connectionState = client.Connect();
                Console.WriteLine("MQTT connection state is [" + connectionState + "]");
            }
            catch(Exception ex)
            {
                svcHost = null;
                Console.WriteLine("Could not init MQTT instance [" + ex.Message + "]");
            }

            if (svcHost != null)
            {
                Console.WriteLine("Running");
                for (;;)
                    Thread.Sleep(1000);
                svcHost.Close();
                svcHost = null;
            }

            if(svcHost != null)
                StaticInitHelper.Run(false);
        }

        private static void HNur_DisconnectedEvent(object sender, NurApi.NurEventArgs e)
        {
            Console.WriteLine("Nur Disconnected");
        }

        private static void HNur_ConnectedEvent(object sender, NurApi.NurEventArgs e)
        {
            Console.WriteLine("Nur Connected");
            try
            {
                hNur.StartInventoryStream();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Could not start inventory stream [" + ex.Message + "]");
            }
        }

        private static void HNur_InventoryStreamEvent(object sender, NurApi.InventoryStreamEventArgs e)
        {
            try
            {
                if (e.data.tagsAdded > 0)
                {
                    NurApi.TagStorage tags = hNur.GetTagStorage();
                    foreach (NurApi.Tag tag in tags)
                    {
                        //have we seen this tag yet?
                        if (!inventoryResults.Contains(tag.GetEpcString()))
                        {
                            inventoryResults.Add(tag.GetEpcString());
                            if (client != null)
                                client.PublishMessage("nurapisample/epc", System.Text.Encoding.ASCII.GetBytes(tag.GetEpcString()));
                        }
                    }
                }
                //if streaming stopped, restart it
                if (e.data.stopped)
                    hNur.StartInventoryStream();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Something went wrong during inventory stream event [" + ex.Message + "]");
            }
            
        }

        public static List<string> GetInventoryResults()
        {
            return inventoryResults;
        }

        
    }
}
