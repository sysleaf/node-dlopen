
var dlopen = require('../');
var assert = require('assert');
const path = require('path');

describe('module', function () {
  it('should be funcion that return object with desired methods', function () {
    assert(typeof dlopen === 'function');
    const libpath = path.join(__dirname, '../build/Release/binding.node')
    var lib =  dlopen(libpath);
    assert(lib instanceof dlopen);
    assert(dlopen.prototype.hasOwnProperty('get'));
    assert(dlopen.prototype.hasOwnProperty('close'));
    assert(lib.get('printf') instanceof Buffer);
    assert(lib.close() === undefined);
  });
});
