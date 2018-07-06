ldll
===========
### Native bindings to libuv's uv_dlopen() and friends using n-api

[![npm version](https://badge.fury.io/js/ldll.svg)](http://badge.fury.io/js/ldll)
[![Build Status](https://travis-ci.org/sysleaf/node-dlopen.svg?branch=master)](https://travis-ci.org/sysleaf/node-dlopen)
[![Coverage Status](https://coveralls.io/repos/github/sysleaf/node-dlopen/badge.svg)](https://coveralls.io/github/sysleaf/node-dlopen)

This module offers access to libuv's `dlopen()`, `dlclose()`, `dlsym()` and
`dlerror()` functions.

A high-level object-oriented `Library` class is also exported.


Installation
------------

Install with `npm`:

``` bash
$ npm install ldll
```


Example
-------

``` js
var dlopen = require('ldll');

// dynamically open the `libc` library
var libc = dlopen('libc');

// get a reference to the `printf` function pointer.
// from here, it's easy to invoke the function pointer via node-ffi.
var printfPointer = libc.get('printf');
```


License
-------

(The MIT License)

Copyright (c) 2014 Vikash Kumar &lt;krvikash35@gmail.com&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
