gcm-vis
=======

About
=====
This is visualization of Greatest Common Measure algorithm for two
segments. I made it after listening to Alexander Stepanov's
[lecture](http://www.stepanovpapers.com/gcd.pdf) "Greatest Common Measure:
the Last 2500 Years".

Building
========
### Dependencies
 * SDL (for OpenGL)
 * CMake

### Linux
Go to the source directory:
    $ cd gcm-vis/

Make separated build directory:
    $ mkdir build
    $ cd build/
    
Configure and build gcm-vis:
    $ cmake ..
    $ make

Run:
    $ ./gcm-vis

### Windows
I haven't tested it under Windows.

License
=======
This program is distributed under terms of MIT License:

Copyright (c) 2011 by rexim

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
