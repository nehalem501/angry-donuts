var libpath = require('path');
var http = require('http');
var url = require('url');
var assert = require('assert');
var angryd = require('./angry-donuts.js');
var express = require('express');
var validate = require('uuid-validate');

var port = 8080;

var app = express();
var router = express.Router();


router.get('/', function(req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.status(404).send("No ID");
});

router.post('/', function(req, res) {
});

router.get('/:id', function(req, res) {
    var id = req.params.id;
    if (validate(id)) {
        var file = angryd.read_stream(id);
        if (file === null) {
            res.setHeader('Content-Type', 'text/plain');
            res.status(404).send("Not found");
        } else {
            file.pipe(res);
        }
    } else {
        res.setHeader('Content-Type', 'text/plain');
        res.status(500).send("Not valid ID");
    }
});

router.delete('/:id', function(req, res) {
    var id = req.params.id;
    if (validate(id)) {
        if (angryd.del(id)) {
            res.setHeader('Content-Type', 'text/plain');
            res.status(200).send("OK");
        } else {
            res.setHeader('Content-Type', 'text/plain');
            res.status(404).send("Not found");
	}
    } else {
        res.setHeader('Content-Type', 'text/plain');
        res.status(500).send("Not valid ID");
    }
});

app.use('/', router);

app.listen(port, function() {
    console.log('Server listening on Port ' + port);
});


