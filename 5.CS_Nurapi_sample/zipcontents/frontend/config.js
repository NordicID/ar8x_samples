host = location.host;	// hostname or IP address
port = (location.protocol == "https:") ? 1884 : 1885; // wss port : ws port
useTLS = location.protocol == "https:";
topic = 'nurapisample/epc';		// topic to subscribe to
username = null;
password = null;
// username = "jjolie";
// password = "aa";

// path as in "scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]"
//    defaults to "/mqtt"
//    may include query and fragment
//
path = "";
// path = "/data/cloud?device=12345";

cleansession = true;
