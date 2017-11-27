// express module for webservice functionality
var express = require(__dirname + '/node_modules/express');
// bodyparser for acception JSON encoded bodies
var bodyParser = require(__dirname + '/node_modules/body-parser');
// shelljs for executing shell commands
var shell = require(__dirname + '/node_modules/shelljs');
var app = express();
// Prefix to our web service methods. CoreService creates configuration similar to this for each installed application
var ws_prefix = '/app/backend/nodenursample/';

// Support JSON-encoded bodies
app.use( bodyParser.json() ); 

// Support URL-encoded bodies
app.use(bodyParser.urlencoded({ 
  extended: true
}));

// Performs an inventory using default rounds, Q and session and returns a JSON-array containing hex-string representation of EPCs seen in the RF-field
app.get(ws_prefix + 'inventory', function (req, res) {
        // Sync call to exec()
        var ret = shell.exec(__dirname + '/nurconrpi 1', {silent:true}).stdout;
        console.log(ret);
        var reslines = ret.match(/[^\r\n]+/g);
		res.setHeader('Content-Type', 'application/json');
        res.end(JSON.stringify(reslines)); //res.end(ret);
});

// Read data from tag singulated by tag's EPC memory and return a hex-string representation of the read data
app.post(ws_prefix + 'readTagByEPC', function(req, res) {
        var epc = req.body.epc;
        var bank = req.body.bank;
        var wordAddress = req.body.wordAddress;
        var readByteCount = req.body.readByteCount;
		console.log("readTagByEPC " + epc + " " + bank + " " + wordAddress + " " + readByteCount);
        var ret = shell.exec(__dirname + '/nurconrpi 2 ' + epc + ' ' + bank + ' ' + wordAddress + ' ' + readByteCount, {silent:true}).stdout;
        res.setHeader('Content-Type', 'application/json');
		res.end(JSON.stringify(ret));
        console.log(ret);
});

// Start listening at port 10126
var server = app.listen(10126, function () {
  var host = server.address().address
  var port = server.address().port
  console.log("Example app listening at http://%s:%s", host, port)
});

