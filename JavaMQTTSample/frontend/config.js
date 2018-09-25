// host = '172.16.153.110';	// hostname or IP address
host = location.host;	// hostname or IP address
port = 1884;
useTLS = false;
username = null;
password = null;
// username = "bob";
// password = "smith";

// path as in "scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]"
//    defaults to "/mqtt"
//    may include query and fragment
//
path = "";
// path = "/data/cloud?device=12345";

cleansession = true;