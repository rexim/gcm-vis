#ifndef STATES_HPP
#define STATES_HPP

#include <GL/gl.h>
#include "misc.hpp"

// STATE //////////////////////////////

class State
{
public:
    State(GLfloat s1, GLfloat s2);

    GLfloat s1() const;
    GLfloat s2() const;
    
    virtual State *tick(int msecs) = 0;

protected:
    GLfloat m_s1, m_s2;
};

// READY //////////////////////////////

class Ready: public State
{
public:
    Ready(GLfloat s1, GLfloat s2, int duration);

    State *tick(int msecs);

protected:
    int countdown;
};

// MERGE //////////////////////////////

class Merge: public State
{
public:
    Merge(GLfloat s1, GLfloat s2, int duration);

    State *tick(int msecs);

protected:
    int countdown;
    GLfloat yStep;
};

// SPLIT //////////////////////////////

class Split: public State
{
public:
    Split(GLfloat s1, GLfloat s2, int duration);

    State *tick(int msecs);

protected:
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
    Stop(GLfloat s1, GLfloat s2);

    State *tick(int msecs);
};

#endif // STATES_HPP
