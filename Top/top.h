#ifndef __TOP_INCLUDED_H__
#define __TOP_INCLUDED_H__
#include "common.h"
#include <cmath>
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
using namespace std;

class place
{
    public:
        float place1[3];
        float place2[3];
        float place3[3];
        float place4[3];
        float place5[3];
    place();
};
place::place()
{
    place1[0] = 0.0; place1[1] = -10.0; place1[2] = 0.0;
    place2[0] = -35.0; place2[1] = 28.0; place2[2] = 0.0;
    place3[0] = 35.0; place3[1] = 35.0; place3[2] = 0.0;
    place4[0] = 35.0; place4[1] = 25.0; place4[2] = 0.0;
    place5[0] = 50; place1[1] = -10.0; place1[2] = 0.0;
}

class Top
{
    public:
        float Vertex[3];
        float angle;
        float Cone[2];
        GLUquadric *fig;
        float Cylinder1[3];
        float Cylinder2[3];
        float Cylinder3[3];
        float Cylinder4[3];
        float Sphere;
        float velx; float vely;
        int tangle;
        float temp_angle;
        float temp_angle2;
        float alpha;
        float beta;
        float speed;
        float rotateSpeed; 
    Top();
    void draw();
    void setVertex(float arr[]);
    void move(int val);
};

Top::Top()
{
    fig = gluNewQuadric();
    Vertex[0] = -55; Vertex[1] = -34; Vertex[2] = 0.0;
    angle = 0.0;
    Cone[0] = 0.05; Cone[1] = 0.2;
    Cylinder1[0] = 0.5; Cylinder1[1] = 0.5; Cylinder1[2] = 0.04;
    Cylinder2[0] = 0.15; Cylinder2[1] = 0.15; Cylinder2[2] = 0.08;
    Cylinder3[0] = 0.07; Cylinder3[1] = 0.07; Cylinder3[2] = 0.1;
    Cylinder4[0] = 0.015; Cylinder4[1] = 0.015; Cylinder4[2] = 0.2;
    Sphere = 0.05;
    tangle = 45;
    temp_angle = 0.0;
    temp_angle2 = 0.0;
    alpha = 0.0;
    beta = 0.0;
    speed = 5.0;
    rotateSpeed = 5.0;
}
void Top::setVertex(float arr[])
{
    for(int i = 0; i < 3; i++)
        Vertex[i] = arr[i];
}
void Top::draw()
{
    glPushMatrix();
    glTranslatef(Vertex[0], Vertex[1], Vertex[2]);
    glRotatef(atan(beta)*180/PI,0.0,0.0,1.0);
    glRotatef(atan(alpha)*180/PI,0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, Cone[1]);
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glRotatef(temp_angle2, 0.0, 0.0, 1.0);
    glRotatef(temp_angle, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCone(Cone[0], Cone[1], 10, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, Cone[1]);
    glRotatef(temp_angle2, 0.0, 0.0, -1.0);
    glRotatef(temp_angle, 0.0, -1.0, 0.0);
    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 1.0);
    gluCylinder(fig, Cylinder1[0], Cylinder1[1], Cylinder1[2], 20, 20);
    glTranslatef(0.0, 0.0, Cylinder1[2]);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    createFilledCircle(Cylinder1[0], 0, 360);
    glEnd();
    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, -1.0);
    glTranslatef(0.0, Cylinder1[0]/2, Sphere/2);
    glColor3f(1.0, 0.5, 1.0);
    glutSolidSphere(Sphere/2, 20, 20);
    glPopMatrix(); 
    glColor3f(0.5, 0.5, 0.5);
    gluCylinder(fig, Cylinder2[0], Cylinder2[1], Cylinder2[2], 20, 20);
    glTranslatef(0.0, 0.0, Cylinder2[2]);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    createFilledCircle(Cylinder2[0], 0, 360);
    glEnd();
    glColor3f(0.75, 1.0, 0.45);
    gluCylinder(fig, Cylinder3[0], Cylinder3[1], Cylinder3[2], 20, 20);
    glTranslatef(0.0, 0.0, Cylinder3[2]);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 1.0);
    createFilledCircle(Cylinder3[0], 0, 360);
    glEnd();
    glTranslatef(0.0, 0.0, Sphere);
    glColor3f(0.34, 0.12, 0.54);
    glutSolidSphere(Sphere, 20, 20);
    glTranslatef(0.0, 0.0, Sphere - 0.02);
    glColor3f(1.0, 0.23, 0.78);
    gluCylinder(fig, Cylinder4[0], Cylinder4[1], Cylinder4[2], 20, 20);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}
void Top::move(int x)
{
    tangle += x;
}

class Target
{
    public:
        float Vertex[3];
        float Cylinder[3];
        GLUquadric *fig;
        Target();
        void set(float arr[]);
        void draw();
};
Target::Target()
{
    fig = gluNewQuadric();
    Cylinder[0] = 2.0;
    Cylinder[2] = 2.0;
}
void Target::set(float arr[])
{
    for(int i = 0; i < 3; i++)
        Vertex[i] = arr[i];
}
void Target::draw()
{
    glPushMatrix();
    glTranslatef(Vertex[0], Vertex[1], Vertex[2]);
    glColor3f(0.34, 0.45, 0.12);
    gluCylinder(fig, Cylinder[0], Cylinder[0], Cylinder[2], 20, 20);
    glTranslatef(0.0, 0.0, Cylinder[2]);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5, 0.5, 0.5);
    createFilledCircle(Cylinder[0], 0, 360);
    glEnd();
    glPopMatrix();
}

class SETIT
{
    public:
        float Cone[2];
        float Vertex[3];
        float angle;
    SETIT();
    void draw();
};
SETIT::SETIT()
{
    Vertex[0] =  -55.0; Vertex[1] = -34.0; Vertex[2] = 0.45;
    Cone[0] = 0.05; Cone[1] = 1.0;
    angle = 0.0;
}
void SETIT::draw()
{
    glPushMatrix();
    glTranslatef(Vertex[0], Vertex[1], Vertex[2]);
    glColor3f(1.0, 1.0, 1.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(angle, -1.0, 0.0, 0.0);
    glutSolidCone(Cone[0], Cone[1], 10, 2);
    glPopMatrix();
}
    


    

    
       
  
#endif
