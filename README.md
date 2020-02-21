
# node-xattr

A library to manipulate xattr on macOS.
APIs provided by this library are similar to node's fs module.

- [__getxattr__](#getxattr)
- [__setxattr__](#setxattr)
- [__listxattr__](#listxattr)
- [__removexattr__](#removexattr)

# What's xattr

> The xattr command can be used to display, modify or remove the extended attributes of one or more files, including directories and symbolic links.  Extended
> attributes are arbitrary metadata stored with a file, but separate from the filesystem attributes (such as modification time or file size).  The metadata is
> often a null-terminated UTF-8 string, but can also be arbitrary binary data.

> One or more files may be specified on the command line.  For the first two forms of the command, when there are more than one file, the file name is displayed

> along with the actual results.  When only one file is specified, the display of the file name is usually suppressed (unless the -v option described below, is also specified).

# Install

```sh
$ yarn add node-xattr
```

# setxattr

`setXattrSync(path, name, value)`

`setXattr(path, name, value, callback)`

Sync version
```js
const { setXattrSync } = require('node-xattr');
setXattrSync('./test.txt', 'key', 'value');
```

Async version
```js
const { setXattr } = require('node-xattr');
setXattr('./test.txt', 'key', 'value', function (err) {
  if (err) {
    console.error(err);
  }
});
```

# getxattr

`getXattrSync(path, name)` returns buffer

`getXattrSync(path, name, encoding)` returns string

`getXattr(path, name, callback)` returns buffer

`getXattr(path, name, encoding, callback)` returns string

Sync Version
```js
const { getXattrSync } = require('node-xattr');
const buffer = getXattrSync('./test.txt', 'key');
const string = getXattrSync('./test.txt', 'key', 'utf8');
```


Async Version
```js
const { getXattr } = require('node-xattr');

getXattr('./test.txt', 'key', function (err, buffer) {
  if (err) {
    console.error(err);
    return;
  }
  console.log(buffer);
});

getXattr('./test.txt', 'key', 'utf8', function (err, string) {
  if (err) {
    console.error(err);
    return;
  }
  console.log(string);
});
```

# listxattr

`listXattrSync(path)`

`listXattr(path, callback)`

Sync Version:
```js
const { listXattrSync } = require('node-xattr');
const list = listXattrSync('./test.txt');
```

Async Version:
```js
const { listXattr } = require('node-xattr');
listXattrSync('./test.txt', function (err, list) {
  if (err) {
    console.error(err);
    return;
  }
  console.log(list);
});
```

# removexattr

`removeXattrSync(path, name)`

`removeXattr(path, name, callback)`

SyncVersion
```js
const { removeXattrSync } = require('node-xattr');
removeXattrSync('./test.txt', 'key');
```

Async verion:
```js
const { removeXattr } = require('node-xattr');
removeXattr('./test.txt', 'key', function (err) {
  if (err) {
    console.error(err);
  }
});
```
