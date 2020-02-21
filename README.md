[![npm version](https://badge.fury.io/js/node-xattr.svg)](https://badge.fury.io/js/node-xattr)

# node-xattr

A library to manipulate xattr on macOS with Typescript support.
APIs provided by this library are similar to node's fs module.

- [__getxattr__](#getxattr)
- [__setxattr__](#setxattr)
- [__listxattr__](#listxattr)
- [__removexattr__](#removexattr)
- [__promises__](#promises)

# What's xattr

> Extended attributes are arbitrary metadata stored with a file, but separate from the filesystem attributes (such as modification time or file size). The metadata is often a null-terminated UTF-8 string, but can also be arbitrary binary data.

# Install

```sh
$ yarn add node-xattr
```

# When to use the sync version

Technically, the sync version would be a little faster. Because the async version waits for a queue to schedule.
Also, it's realtime.
The disadvantage of the sync version is that it will probably block the process. So DO NOT use sync version in 
some UI process(such as the renderer process of Electron).
The best scenario to use sync version is in background worker/process/thread.

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

# promises

node-xattr support Promise API in `promises` namespace;

```js
const { promises } = require('node-xattr');
```

You can just use Promise API just like sync version above:

```js
await promises.setXattr(path, name, value);
```
