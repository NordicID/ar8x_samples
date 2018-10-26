using Backend.Utils;
using System;
using System.Collections.Generic;
using System.ServiceModel;
using System.Threading;
using System.ServiceModel.Web;

namespace ThirdPartyAppPing
{
    public partial class WcfEntryPoint : WcfInterface
    {
        public String Ping()
        {
            Console.WriteLine("Ponging");
            return "Pong";
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
                string URL = "http://127.0.0.1:10001/app/backend/appexample";
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
                svcHost.Close();
                svcHost = null;
            }
            StaticInitHelper.Run(false);
        }
    }
}
