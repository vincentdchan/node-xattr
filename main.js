const {
  getXattrSync: __getXattrSync,
  getXattr: __getXattr,
  setXattr: __setXattr,
  listXattr: __listXattr,
  removeXattr: __removeXattr,
  ...rest
} = require('bindings')('node-xattr');
const { promisify } = require('util');

function getXattrSync(path, name, encoding) {
  const buffer = __getXattrSync(path, name);
  if (typeof encoding !== 'undefined') {
    return buffer.toString(encoding);
  }
  return buffer;
}

function promisifyGetXattr(path, name, encoding) {
  return new Promise((resolve, reject) => {
    __getXattr(path, name, function (err, data) {
      if (err) {
        return reject(err);
      }

      if (typeof encoding === 'string') {
        return resolve(data.toString(encoding));
      }

      return resolve(data);
    });
  });
}

const getXattr = promisifyGetXattr;
const setXattr = promisify(__setXattr);
const listXattr = promisify(__listXattr);
const removeXattr = promisify(__removeXattr);

module.exports = {
  getXattrSync,
  getXattr,
  setXattr,
  listXattr,
  removeXattr,
  ...rest,
}
