#include <iostream>
#include <algorithm>
#include <cmath>
#include "states.hpp"

using namespace std;

static void drawParallel(GLfloat s1, GLfloat s2, GLfloat yDistance)
{
    GLfloat xStart = -max(s1, s2) / 2.0f;
    
    glBegin(GL_LINES);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(xStart,               yDistance / 2.0f);
    glVertex2f(xStart + max(s1, s2), yDistance / 2.0f);

    glVertex2f(xStart,               -yDistance / 2.0f);
    glVertex2f(xStart + min(s1, s2), -yDistance / 2.0f);
    
    glEnd();
}

// STATE //////////////////////////////

State::State(GLfloat s1, GLfloat s2):
    m_s1(s1), m_s2(s2)
{}

GLfloat State::s1() const
{
    return m_s1;
}

GLfloat State::s2() const
{
    return m_s2;
}

// READY //////////////////////////////

Ready::Ready(GLfloat s1, GLfloat s2, int duration):
    State(s1, s2), countdown(duration)
{}

State *Ready::tick(int msecs)
{
    drawParallel(s1(), s2(), 0.6f);

    if(countdown > 0) {
        countdown -= msecs;
        return this;
    } else
        return new Merge(s1(), s2(), 700);
}

// MERGE //////////////////////////////

Merge::Merge(GLfloat s1, GLfloat s2, int duration):
    State(s1, s2), countdown(duration),
    yStep(0.6f / duration)
{
}

State *Merge::tick(int msecs)
{
    drawParallel(s1(), s2(), yStep * countdown);

    if(countdown > 0) {
        countdown -= msecs;
        return this;
    } else
        return new Split(s1(), s2(), 700);
    
    return this;
}

// SPLIT //////////////////////////////

Split::Split(GLfloat s1, GLfloat s2, int duration):
    State(s1, s2), countdown(duration)
{
    GLfloat xStart = -max(m_s1, m_s2) / 2.0;

    if(m_s1 < m_s2) {
        pos1 = Vector2D(xStart, 0.0f);
        pos2 = Vector2D(xStart + m_s1, 0.0f);

        m_s2 -= m_s1;
    } else {
        pos1 = Vector2D(xStart + m_s2, 0.0f);
        pos2 = Vector2D(xStart, 0.0f);

        m_s1 -= m_s2;
    }

    xStart = -max(m_s1, m_s2) / 2.0;

    if(m_s1 < m_s2) {
        vel1 = Vector2D(xStart, -0.3f) - pos1;
        vel2 = Vector2D(xStart, 0.3f) - pos2;
    } else {
        vel1 = Vector2D(xStart, 0.3f) - pos1;
        vel2 = Vector2D(xStart, -0.3f) - pos2;
    }

    vel1 = vel1 / duration;
    vel2 = vel2 / duration;


}

State *Split::tick(int msecs)
{
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(pos1.x, pos1.y);
    glVertex2f(pos1.x + m_s1, pos1.y);

    glVertex2f(pos2.x, pos2.y);
    glVertex2f(pos2.x + m_s2, pos2.y);
    glEnd();

    if(countdown > 0) {
        pos1 += vel1 * msecs;
        pos2 += vel2 * msecs;

        countdown -= msecs;
        return this;
    } else
        return new Ready(s1(), s2(), 700);
}

// STOP //////////////////////////////

Stop::Stop(GLfloat s1, GLfloat s2):
    State(s1, s2)
{}

State *Stop::tick(int)
{
    glBegin(GL_LINES);

    glVertex2f(-m_s1 / 2.0f, 0.0f);
    glVertex2f(m_s1 / 2.0f, 0.0f);

    glEnd();
    return this;
}
