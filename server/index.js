var libpath = require('path');
var http = require('http');
var url = require('url');
var assert = require('assert');
var angryd = require('angry-donuts-addon');

var port = 8080;
var path = "/path/to/your/base_directory/";

// Regex for testing UUIDs
var pattern = /^[0-9a-f]{8}-[0-9a-f]{4}-[1-5][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i;

/*
   assert(addon.test("hello") == "olleh");
   assert(addon.test() == undefined);
   assert(addon.test(88) == undefined);

   console.log("Hooray!  The addon worked as expected.");
   */

http.createServer(function (request, response) {
    var uri = url.parse(request.url).pathname;
    console.log('requested uri ' + uri);
    var filename = libpath.join(path, uri);

    libpath.exists(filename, function (exists) {
        if (!exists) {
            console.log('404 File Not Found: ' + filename);
            response.writeHead(404, {
                "Content-Type": "text/plain"
            });
            response.write("404 Not Found\n");
            response.end();
            return;
        } else{
            //console.log('Starting download: ' + filename);
            //var stream = fs.createReadStream(filename, { bufferSize: 64 * 1024 });
            //stream.pipe(response);
        }
    });

}).listen(port);

console.log('Server listening on Port ' + port);
