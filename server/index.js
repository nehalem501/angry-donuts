var libpath = require('path');
var http = require('http');
var url = require('url');
var assert = require('assert');
var angryd = require('./angry-donuts.js');
var express = require('express');
var validate = require('uuid-validate');

var port = 8080;
var path = "/path/to/your/base_directory/";


var app = express();
var router = express.Router();


router.get('/', function(req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.send("No ID");
});

router.post('/', function(req, res) {
});

router.get('/:id', function(req, res) {
    var id = req.params.id;
    if (validate(id, 1)) {
        //res.send("valid UUID"); // TODO
        //var file = fs.createReadStream('file');
        var file = angryd.read_stream(id);
        file.pipe(res);
    } else {
        res.setHeader('Content-Type', 'text/plain');
        res.send("Not valid ID");
    }
});

router.delete('/:id', function(req, res) {
});

app.use('/storage', router);

app.listen(port, function() {
    console.log('Server listening on Port ' + port);
});


