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
  promises,
} = require('..');
const { writeFileSync, unlinkSync } = require('fs');

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
    await promises.setXattr(TestFile, TestKey, TestData);
    expect(await promises.getXattr(TestFile, TestKey, 'utf8')).to.equal(TestData);
  });

  it('listXAttr', async function () {
    const list = await promises.listXattr(TestFile);
    expect(list).to.deep.equal([TestKey]);
  });

  it('removeXAttr', async function () {
    await promises.removeXattr(TestFile, TestKey);
    const list = await promises.listXattr(TestFile);
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

describe('Async Function', () => {

  before(() => {
    try {
      unlinkSync(TestFile);
    } catch (err) {
      // nothing
    }
    writeFileSync(TestFile, 'data', 'utf8');
  });

  it('setXAttr', function (done) {
    setXattr(TestFile, TestKey, TestData, done);
  });

  it('getXAttr', function (done) {
    getXattr(TestFile, TestKey, 'utf8', function (err, data) {
      if (err) {
        return done(err);
      }
      expect(data).to.equal(TestData);
      done();
    });
  });

  it('listXAttr', function (done) {
    listXattr(TestFile, function (err, data) {
      if (err) {
        return done(err);
      }
      expect(data).to.deep.equal([TestKey]);
      done();
    });
  });

  it('removeXAttr', function (done) {
    removeXattr(TestFile, TestKey, function (err) {
      if (err) {
        return done(err);
      }
      const list = listXattrSync(TestFile);
      expect(list).to.deep.equal([]);
      done();
    });
  });

});
