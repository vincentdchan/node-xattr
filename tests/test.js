const { expect } = require('chai');
const {
  setXattrSync,
  getXattrSync,
  listXattrSync,
  removeXattrSync,
  setXattr,
  getXattr,
  listXattr,
  removeXattr,
  macUtils,
} = require('..');
const { writeFileSync, unlinkSync } = require('fs');
const { join } = require('path');

const TestFile = '/tmp/node-attr-test-file.txt';
const TestKey = 'TestKey';
const TestData = 'TestData';

describe('Promisify Function', function() {

  before(() => {
    try {
      unlinkSync(TestFile);
    } catch (err) {
      // nothing
    }
    writeFileSync(TestFile, 'data', 'utf8');
  });

  it('setXAttr', async function () {
    await setXattr(TestFile, TestKey, TestData);
    expect(await getXattr(TestFile, TestKey, 'utf8')).to.equal(TestData);
  });

  it('listXAttr', async function () {
    const list = await listXattr(TestFile);
    expect(list).to.deep.equal([TestKey]);
  });

  it('removeXAttr', async function () {
    await removeXattr(TestFile, TestKey);
    const list = await listXattr(TestFile);
    expect(list).to.deep.equal([]);
  });

});

describe('Sync Function', function() {

  before(() => {
    try {
      unlinkSync(TestFile);
    } catch (err) {
      // nothing
    }
    writeFileSync(TestFile, 'data', 'utf8');
  });

  it('setXAttr', function () {
    setXattrSync(TestFile, TestKey, TestData);
    expect(getXattrSync(TestFile, TestKey, 'utf8')).to.equal(TestData);
  });

  it('listXAttr', function () {
    const list = listXattrSync(TestFile);
    expect(list).to.deep.equal([TestKey]);
  });

  it('removeXAttr', function () {
    removeXattrSync(TestFile, TestKey);
    const list = listXattrSync(TestFile);
    expect(list).to.deep.equal([]);
  });

});

describe('setCustomIcon', function() {
  beforeEach(() => {
    try {
      unlinkSync(TestFile);
    } catch (err) {
      // nothing
    }
    writeFileSync(TestFile, 'data', 'utf8');
  });

  const iconPath = join(__dirname, 'spider-man.icns');

  it('setCustomIcon', function() {
    macUtils.setCustomIconSync(TestFile, iconPath);
  });

  it('setCustomIconAsync', async function() {
    await macUtils.setCustomIcon(TestFile, iconPath);
  });

});
