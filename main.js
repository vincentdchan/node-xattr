const { getXattrSync: __getXattrSync, getXattr: __getXattr, ...rest } = require('bindings')('node-xattr');

function getXattrSync(path, name, encoding) {
  const buffer = __getXattrSync(path, name);
  if (typeof encoding !== 'undefined') {
    return buffer.toString(encoding);
  }
  return buffer;
}

function getXattr(path, name) {
  let encoding;
  let cb;
  if (typeof arguments[2] === 'string') {
    encoding = arguments[2]
    cb = arguments[3];
  } else {
    cb = arguments[2];
  }
  if (typeof cb !== 'function') {
    throw new Error('the third argument must be either a string or a function');
  }

  __getXattr(path, name, function (err, data) {
    if (err) {
      return cb(err);
    }

    if (typeof encoding !== 'string') {
      return cb(err, data.toString(encoding));
    }

    return cb(err, data);
  });
}

module.exports = {
  getXattrSync,
  getXattr,
  ...rest,
}
