var Hash = require('./index');

var h = Hash.empty();
console.log(Hash.empty().equals(h));
h.append(new Buffer([1,2,3]), function () {
  console.log(h.toString());
});
var h2 = Hash.empty();
h2.prepend(new Buffer([1,2,3]), function () {
  console.log(h2.toString());
});
var h3 = Hash.empty().concat(Hash.empty());
console.log(h3.equals(h2));
