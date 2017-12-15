using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace nurapisample
{
    [ServiceContract]
    public partial interface WcfInterface
    {
        [OperationContract,
         WebInvoke(Method = WebRequestMethods.Http.Get,
         UriTemplate = "/GetInventoryResults",
         RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)
        ]
        List<string> GetInventoryResults();

        /*[OperationContract]
		[WebInvoke(Method = "OPTIONS", UriTemplate = "*")]
		void GetOptions();*/
    }
}
