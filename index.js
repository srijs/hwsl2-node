var hwsl2 = require('./build/Release/hwsl2');

var Hash = module.exports = function () {
  Object.defineProperty(this, 'hash', {
    enumerable: false,
    value: hwsl2.empty()
  });
};

Hash.empty = function () {
  return new Hash();
};

Hash.prototype.concat = function (other) {
  var result = new Hash();
  result.hash = hwsl2.concat(this.hash, other.hash);
  return result;
};

Hash.prototype.toString = function () {
  return hwsl2.serialize(this.hash);
};

Hash.prototype.equals = function (other) {
  return hwsl2.equals(this.hash, other.hash);
};

Hash.prototype.append = function (buf, cb) {
  hwsl2.append(this.hash, buf, cb);
};

Hash.prototype.prepend = function (buf, cb) {
  hwsl2.prepend(this.hash, buf, cb);
};

Hash.hash = function (buf, cb) {
  var hash = Hash.empty();
  hash.append(buf, function () {
    cb(null, hash);
  });
};

