// Copyright (c) 2011 by rexim
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef STATES_HPP
#define STATES_HPP

#include <string>
#include <GL/gl.h>
#include "misc.hpp"

// STATE //////////////////////////////

class State
{
public:
    virtual State *tick(int msecs) = 0;
    virtual const std::string name() const = 0;
};

// READY //////////////////////////////

class Ready: public State
{
public:
    Ready(GLfloat seg1, GLfloat seg2, int duration);

    State *tick(int msecs);
    const std::string name() const;

protected:
    GLfloat segment1, segment2;
    int countdown;
};

// MERGE //////////////////////////////

class Merge: public State
{
public:
    Merge(GLfloat seg1, GLfloat seg2, int duration);

    State *tick(int msecs);
    const std::string name() const;

protected:
    GLfloat segment1, segment2;
    int countdown;
    GLfloat yStep;
};

// SPLIT //////////////////////////////

class Split: public State
{
public:
    Split(GLfloat seg1, GLfloat seg2, int duration);

    State *tick(int msecs);
    const std::string name() const;

protected:
    GLfloat segment1, segment2;
    int countdown;
    Vector2D pos1;
    Vector2D vel1;
    Vector2D pos2;
    Vector2D vel2;
};

// STOP //////////////////////////////

class Stop: public State
{
public:
    Stop(GLfloat seg);

    State *tick(int msecs);
    const std::string name() const;

protected:
    GLfloat segment;
};

#endif // STATES_HPP
