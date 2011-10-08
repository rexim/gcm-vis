#ifndef STATES_HPP
#define STATES_HPP

#include <GL/gl.h>
#include "misc.hpp"

// STATE //////////////////////////////

class State
{
public:
    virtual State *tick(int msecs) = 0;
};

// READY //////////////////////////////

class Ready: public State
{
public:
    Ready(GLfloat seg1, GLfloat seg2, int duration);

    State *tick(int msecs);

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

protected:
    GLfloat segment;
};

#endif // STATES_HPP
