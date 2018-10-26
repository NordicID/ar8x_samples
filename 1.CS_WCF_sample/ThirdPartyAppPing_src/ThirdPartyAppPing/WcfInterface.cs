using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace ThirdPartyAppPing
{
    [ServiceContract]
    public partial interface WcfInterface
    {
        [OperationContract,
         WebInvoke(Method = WebRequestMethods.Http.Get,
         UriTemplate = "/Ping",
         RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
        ]
        String Ping();
    }
}
