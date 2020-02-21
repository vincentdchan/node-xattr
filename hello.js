const { getXattrSync } = require('bindings')('node-xattr');

console.log(getXattrSync('hello.js', 'hello')); // 'world'
