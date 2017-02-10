const addon = require('angry-donuts-addon');
const assert = require('assert');

assert(addon.test("hello") == "olleh");
assert(addon.test() == undefined);
assert(addon.test(88) == undefined);

console.log("Hooray!  The addon worked as expected.");
