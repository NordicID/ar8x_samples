using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Runtime.Serialization;
using Newtonsoft.Json;

namespace NormaConfig
{
    [DataContract]
    public class Reader
    {
        [DataMember]
        public bool Active { get; set; }
        [DataMember]
        public string ReaderAddress { get; set; }
        [DataMember]
        public int ClientPort { get; set; }
        [DataMember]
        public bool UseTLS { get; set; }
        [DataMember]
        public int? ReaderPort { get; set; }
    }

    [DataContract]
    public class Device
    {
        [DataMember]
        public Reader Reader { get; set; }
    }

    [DataContract]
    public class DeviceObject
    {
        [DataMember]
        public List<Device> Devices { get; set; }
    }

    public class DeviceCapabilities
    {
        public int curCfgMaxAnt { get; set; }
        public int curCfgMaxGPIO { get; set; }
        public int flagSet1 { get; set; }
        public int flagSet2 { get; set; }
        public int maxTxdBm { get; set; }
        public int maxTxmW { get; set; }
        public int moduleConfigFlags { get; set; }
        public int moduleType { get; set; }
        public int res { get; set; }
        public int szTagBuffer { get; set; }
        public int txAttnStep { get; set; }
        public int txSteps { get; set; }
    }

    public class GetModuleSetup
    {
        public int antPower { get; set; }
        public int antPowerEx { get; set; }
        public int antennaMask { get; set; }
        public int antennaMaskEx { get; set; }
        public int autotuneMode { get; set; }
        public int autotunethreshold_dBm { get; set; }
        public int inventoryLength { get; set; }
        public int inventoryQ { get; set; }
        public int inventoryRounds { get; set; }
        public int inventoryRssiFilterMax { get; set; }
        public int inventoryRssiFilterMin { get; set; }
        public int inventorySession { get; set; }
        public int inventoryTarget { get; set; }
        public int inventoryTriggerTimeout { get; set; }
        public int killTO { get; set; }
        public int linkFreq { get; set; }
        public int lockTO { get; set; }
        public int opFlags { get; set; }
        public int periodSetup { get; set; }
        public int powerOffset { get; set; }
        public int readRssiFilterMax { get; set; }
        public int readRssiFilterMin { get; set; }
        public int readTO { get; set; }
        public int regionId { get; set; }
        public int rxDecoding { get; set; }
        public int rxSensitivity { get; set; }
        public int scanSingleTriggerTimeout { get; set; }
        public int selectedAntenna { get; set; }
        public int txLevel { get; set; }
        public int txModulation { get; set; }
        public int writeRssiFilterMax { get; set; }
        public int writeRssiFilterMin { get; set; }
        public int writeTO { get; set; }
    }

    public class GetReaderInfo
    {
        public string altSerial { get; set; }
        public string fccId { get; set; }
        public string hwVersion { get; set; }
        public int maxAntennas { get; set; }
        public string name { get; set; }
        public int numAntennas { get; set; }
        public int numGpio { get; set; }
        public int numRegions { get; set; }
        public int numSensors { get; set; }
        public string serial { get; set; }
        public int swVerMajor { get; set; }
        public int swVerMinor { get; set; }
    }

    public class RegionInfo
    {
        public List<int> baseFrequency { get; set; }
        public List<int> channelCount { get; set; }
        public List<int> channelSpacing { get; set; }
        public List<int> channelTime { get; set; }
        public List<int> regionId { get; set; }
    }

    public class DeviceStatusObject
    {
        public DeviceCapabilities DeviceCapabilities { get; set; }
        public GetModuleSetup GetModuleSetup { get; set; }
        public GetReaderInfo GetReaderInfo { get; set; }
        public RegionInfo RegionInfo { get; set; }
    }

    public class Status
    {
        public bool Active { get; set; }
        public string ClientConnection { get; set; }
        public string LastLLRPError { get; set; }
        public string ReaderConnection { get; set; }
        public string ReaderLastError { get; set; }
    }

    public class ReaderStatus
    {
        public string InstanceName { get; set; }
        public Status Status { get; set; }
    }

    public class Instances
    {
        public List<ReaderStatus> ReaderStatus { get; set; }
    }

    public class NormaStatus
    {
        public string LastUpdate { get; set; }
        public Instances Instances { get; set; }
    }

    [ServiceContract]
    public partial interface WcfInterface
    { 
        [OperationContract,
         WebInvoke(Method = WebRequestMethods.Http.Get,
         UriTemplate = "/Ping",
         RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
        ]
        String Ping();

        [OperationContract,
        WebInvoke(Method = WebRequestMethods.Http.Get,
        UriTemplate = "/GetDevices",
        RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
       ]
        List<Device> GetDevices();

        [OperationContract,
            WebInvoke(Method = WebRequestMethods.Http.Post,
                UriTemplate = "/SetDevices",
                BodyStyle = WebMessageBodyStyle.Bare,
                RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
        ]
        bool SetDevices(List<Device> items);

        [OperationContract,
        WebInvoke(Method = WebRequestMethods.Http.Get,
        UriTemplate = "/GetDeviceSetupAll",
        RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
       ]
        List<DeviceStatusObject> GetDeviceSetupAll();

        [OperationContract,
       WebInvoke(Method = WebRequestMethods.Http.Post,
       UriTemplate = "/GetDeviceSetup",
       RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
      ]
        DeviceStatusObject GetDeviceSetup(string deviceId);

        [OperationContract,
            WebInvoke(Method = WebRequestMethods.Http.Get,
            UriTemplate = "/GetDeviceStatusAll",
        RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
            ]
        NormaStatus GetDeviceStatusAll();

        [OperationContract,
          WebInvoke(Method = WebRequestMethods.Http.Post,
          UriTemplate = "/GetDeviceSetup",
          RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
         ]
        NormaStatus GetDeviceStatus(string deviceId);

        [OperationContract,
            WebInvoke(Method = WebRequestMethods.Http.Get,
            UriTemplate = "/GetLog",
        RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
            ]
        string GetLog();

        /*
        [OperationContract,
        WebInvoke(Method = WebRequestMethods.Http.Get,
        UriTemplate = "/GetStatusLog",
        RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
       ]
        List<Device> GetStatusLog();/*

        [OperationContract,
        WebInvoke(Method = WebRequestMethods.Http.Get,
        UriTemplate = "/GetLog",
        RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
       ]
        List<string> GetLog();
        /*[OperationContract]
		[WebInvoke(Method = "OPTIONS", UriTemplate = "*")]
		void GetOptions();*/
    }
}
