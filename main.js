const { getXattrSync: __getXattrSync, setXattrSync, listXattrSync, removeXattrSync } = require('bindings')('node-xattr');

function getXattrSync(path, name, encoding) {
  const buffer = __getXattrSync(path, name);
  if (typeof encoding !== 'undefined') {
    return buffer.toString(encoding);
  }
  return buffer;
}

module.exports = {
  getXattrSync,
  setXattrSync,
  listXattrSync,
  removeXattrSync,
}
