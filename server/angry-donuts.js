var util = require('util');
var angryd = require('angry-donuts-addon');
var Readable = require('stream').Readable;

var ObjectReadStream = function(id, options) {
    console.log(id);
    Readable.call(this, options);
    //angryd.open(id);
    this.id = id;
    this.counter = 0;
};

util.inherits(ObjectReadStream, Readable); // inherit the prototype methods

ObjectReadStream.prototype._read = function(n) {
    //var buffer = 'foobar';
    //var buffer = angryd.read(this.id);
    this.push(angryd.read(this.id, this.counter));
    this.counter++;
    /*this.length -= buffer.length;
    if (this.length <= 0) { // stop the stream
        this.push(null);
    }*/
};

module.exports = {
    read_stream: function(id) {
        if (angryd.exists(id)) {
            return new ObjectReadStream(id);
        } else {
            return null;
        }
    },

    del: function(id) {
        if (angryd.exists(id)) {
            angryd.del(id);
            return true;
        } else {
            return false;
        }
    }
}

//var mystream = new MyStream();
//mystream.pipe(process.stdout);
