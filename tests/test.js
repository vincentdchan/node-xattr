const { expect } = require('chai');
const { setXattrSync, getXattrSync, listXattrSync, removeXattrSync } = require('../main');
const { writeFileSync, unlinkSync } = require('fs');

const TestFile = '/tmp/node-attr-test-file.txt';
const TestKey = 'TestKey';
const TestData = 'TestData';

describe('Sync Function', () => {

  before(() => {
    try {
      unlinkSync(TestFile);
    } catch (err) {
      // nothing
    }
    writeFileSync(TestFile, 'data', 'utf8');
  });

  it('setXAttr', () => {
    setXattrSync(TestFile, TestKey, TestData);
    expect(getXattrSync(TestFile, TestKey, 'utf8')).to.equal(TestData);
  });

  it('listXAttr', () => {
    const list = listXattrSync(TestFile);
    expect(list).to.deep.equal([TestKey]);
  });

  it('removeXAttr', () => {
    removeXattrSync(TestFile, TestKey);
    const list = listXattrSync(TestFile);
    expect(list).to.deep.equal([]);
  });

});
