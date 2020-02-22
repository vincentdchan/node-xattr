[![npm version](https://badge.fury.io/js/node-xattr.svg)](https://badge.fury.io/js/node-xattr)

# node-xattr

A library to manipulate xattr on macOS with Typescript support.
APIs provided by this library are similar to node's fs module.

- [__getxattr__](#getxattr)
- [__setxattr__](#setxattr)
- [__listxattr__](#listxattr)
- [__removexattr__](#removexattr)

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

```
setXattrSync(path: string, name: string, value: string | Buffer): void;

setXattr(path: string, name: string, value: string | Buffer): Promise<void>;
```

Sync version
```js
const { setXattrSync } = require('node-xattr');
setXattrSync('./test.txt', 'key', 'value');
```

Async version
```js
const { setXattr } = require('node-xattr');

setXattr('./test.txt', 'key', 'value').catch(err => console.error(err));
```

# getxattr

```
getXattrSync(path: string, name: string): Buffer;

getXattrSync(path: string, name: string, encoding: string): string;

getXattr(path: string, name: string): Promise<Buffer>;

getXattr(path: string, name: string, encoding: string): Promise<string>;
```

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

getXattr('./test.txt', 'key').then(buffer => console.log(buffer)).catch(err => console.error(err));

getXattr('./test.txt', 'key', 'utf8').then(str => console.log(str)).catch(err => console.error(err));
```

# listxattr

```
listXattrSync(path: string): string[];

listXattr(path: string): Promise<string[]>;
```

Sync Version:
```js
const { listXattrSync } = require('node-xattr');

const list = listXattrSync('./test.txt');
```

Async Version:
```js
const { listXattr } = require('node-xattr');

listXattr('./test.txt').then(list => console.log(list)).catch(err => console.error(err));
```

# removexattr

```
removeXattrSync(path: string, name: string): void;

removeXattr(path: string, name: string): Promise<void>;
```

SyncVersion
```js
const { removeXattrSync } = require('node-xattr');
removeXattrSync('./test.txt', 'key');
```

Async verion:
```js
const { removeXattr } = require('node-xattr');
removeXattr('./test.txt', 'key').catch(err => console.error(err));
```
