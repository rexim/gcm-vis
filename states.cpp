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

#include <iostream>
#include <algorithm>
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include "states.hpp"

using namespace std;

static void drawParallel(GLfloat segment1, GLfloat segment2, GLfloat yDistance)
{
    GLfloat xStart = -max(segment1, segment2) / 2.0f;
    
    glBegin(GL_LINES);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(xStart, yDistance / 2.0f);
    glVertex2f(xStart + max(segment1, segment2), yDistance / 2.0f);

    glVertex2f(xStart, -yDistance / 2.0f);
    glVertex2f(xStart + min(segment1, segment2), -yDistance / 2.0f);
    
    glEnd();
}

// READY //////////////////////////////

Ready::Ready(GLfloat seg1, GLfloat seg2, int duration):
    segment1(seg1), segment2(seg2), countdown(duration)
{}

State *Ready::tick(int msecs)
{
    drawParallel(segment1, segment2, 0.6f);

    if(countdown > 0) {
        countdown -= msecs;
        return this;
    } else
        return new Merge(segment1, segment2, 700);
}

const std::string Ready::name() const
{
    return "Ready";
}

// MERGE //////////////////////////////

Merge::Merge(GLfloat seg1, GLfloat seg2, int duration):
    segment1(seg1), segment2(seg2),
    countdown(duration),
    yStep(0.6f / duration)
{}

State *Merge::tick(int msecs)
{
    drawParallel(segment1, segment2, yStep * countdown);

    if(countdown > 0) {
        countdown -= msecs;
        return this;
    } else {
        if(abs(segment1 - segment2) < 0.000001)
            return new Stop(segment1);
        else
            return new Split(segment1, segment2, 700);
    }
    
    return this;
}

const std::string Merge::name() const
{
    return "Merge";
}

// SPLIT //////////////////////////////

Split::Split(GLfloat seg1, GLfloat seg2, int duration):
    segment1(seg1), segment2(seg2),
    countdown(duration)
{
    GLfloat xStart = -max(segment1, segment2) / 2.0f;

    if(segment1 < segment2) {
        pos1 = Vector2D(xStart, 0.0f);
        pos2 = Vector2D(xStart + segment1, 0.0f);

        segment2 -= segment1;
    } else {
        pos1 = Vector2D(xStart + segment2, 0.0f);
        pos2 = Vector2D(xStart, 0.0f);

        segment1 -= segment2;
    }

    xStart = -max(segment1, segment2) / 2.0f;

    if(segment1 < segment2) {
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
    glVertex2f(pos1.x + segment1, pos1.y);

    glVertex2f(pos2.x, pos2.y);
    glVertex2f(pos2.x + segment2, pos2.y);
    glEnd();

    if(countdown > 0) {
        pos1 += vel1 * msecs;
        pos2 += vel2 * msecs;

        countdown -= msecs;
        return this;
    } else
        return new Ready(segment1, segment2, 700);
}

const std::string Split::name() const
{
    return "Split";
}

// STOP //////////////////////////////

Stop::Stop(GLfloat seg):
    segment(seg)
{}

State *Stop::tick(int)
{
    glBegin(GL_LINES);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-segment / 2.0f, 0.0f);
    glVertex2f(segment / 2.0f, 0.0f);

    glEnd();
    return this;
}

const std::string Stop::name() const
{
    return "Stop";
}
