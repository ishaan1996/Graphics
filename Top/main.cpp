#include <iostream>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include "scene.h"
#include "camera.h"
#include "top.h"
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

using namespace std;

float deltaMove = 0.0;
float arr1[3], arr2[3];

place NOW;
Surface P;
PlayerView V1, V2, V3, V4;
Heli cam;
Flag F;
Mountain M[4];
Boundary B;
Valley V;
Cylinder Hide;
Cone C1[36];
Cone C2[36];
Top T;
Target Hit;
SETIT SET;

class Flag
{
     public:
     int cameraType;
     int isDragging;
     float xDragStart;
     float yDragStart;
     float deltaAngle;
     float angle;
     int score;
     int timer;
     int release;
     int count;
     float speed;
     Flag();
};
Flag::Flag()
{
     cameraType = 2;
     isDragging = 0;
     xDragStart = 0.0;
     yDragStart = 0.0;
     deltaAngle = 0.0;
     angle = 0.0;
     score = 0;
     timer = 0;
     release = 0;
     count = 1;
     speed = 0;
}
void createFilledCircle(float rad, int start, int end)
{
      for(int i = start; i <= end; i++)
         glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
}
void scoreDraw()
{
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2i(0.0f, 0.0f);
    string p;
    /*if(F.timer % 1000 == 0)
        F.score -= 1;
    */
    int score = F.score;
    int arr[4];
    int j = 0;
    int hello = F.speed;
    char spp = hello + '0';
    char sign;
    if(score == 0)
        p = "0";
    if(score < 0)
    {    
        sign = '-';
        score = -score;
    } 
    else if(score >= 0)
        sign = ' '; 
    while(score != 0)
    {
        arr[j++] = score%10 + '0';
        score /= 10;
    }
    p = p + sign;
    for(int k = j - 1; k >= 0; k--)
    {
        char ch;
        ch = arr[k];
        p = p + ch;
    }
    string s = "YOUR SCORE IS : " + p + "    ||||||||||||    " + "Speed = " + spp; 
    void *font = GLUT_BITMAP_HELVETICA_18;
    for(string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    glPopMatrix();
}
void checkColl()
{
    float distance1 = sqrt(((T.Vertex[0] - Hit.Vertex[0])*(T.Vertex[0] - Hit.Vertex[0]))+ ((T.Vertex[1] - Hit.Vertex[1])*(T.Vertex[1] - Hit.Vertex[1])));
    if(distance1 < Hit.Cylinder[0] + 0.5)
    {
        F.score += 10;
        F.count = (F.count + 1)%5;
        if(F.count % 5 == 0)
            Hit.set(NOW.place5);
        else if(F.count % 5 == 1)
            Hit.set(NOW.place1);
        else if(F.count % 5 == 2)
            Hit.set(NOW.place2);
        else if(F.count % 5 == 3)
            Hit.set(NOW.place3);
        else if(F.count % 5 == 4)
            Hit.set(NOW.place4);

        F.speed = 0;
        F.release = 0;
        T.angle = 0;
        T.speed = 0;
        T.temp_angle = 0;
        T.temp_angle2 = 0;
        T.tangle = 0;
        T.Vertex[0] = -55.0; T.Vertex[1] = -34.0; T.Vertex[2] = 0.0;
       
    }
    if(T.Vertex[0] >= 60 || T.Vertex[0] <= -60 || T.Vertex[1] >= 38 || T.Vertex[1] <= -38)
    {
        cout << "OOPS LOOKS LIKE YOU HIT THE WALL" << endl;
        cout << "GAME OVER" << endl;
        cout << "FINAL SCORE" << " : " << F.score << endl;
        exit(0);
    }
}
void MountainInit()
{
    V2.atVertex[0] = 0.0; V2.atVertex[1] = 0.0;V2.atVertex[2] = 99.0; V2.toVertex[0] = 0.0; V2.toVertex[1] = 0.0; V2.toVertex[2] = -100.0;  
    V2.upVector[0] = 0.0; V2.upVector[1] = 1.0; V2.upVector[2] = 0.0; 
    arr1[0] = -45.0; arr1[1] = 28.0; arr1[2] = 0.0; arr2[0] = 8.0; arr2[1] = 0.0; arr2[2] = 0.0;
    M[0].set(arr1, arr2);
    arr1[0] = -arr1[0]; arr1[1] = -arr1[1];
    M[1].set(arr1, arr2);
    arr1[0] = 25.0; arr1[1] = 25.0;
    M[2].set(arr1, arr2);
    arr1[0] = 25.0; arr1[1] = 9.0;
    V.set(arr1, arr2);
    arr1[0] = 0.0; arr1[1] = -10.0; arr1[2] = 0.0;
    Hit.set(arr1);
}
void renderScene()
{
    float setArr[3] = {0.0};
    int i, j, count = 0;
    glClearColor(0.0, 0.7, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    switch(F.cameraType)
    {
        case 1: V1.view();
                break;
        case 2: V2.view();
                break;
        case 3: V3.view();
                break;
        case 4: V4.view();
                break;
        case 5: cam.view();
                break;
    }
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 800, 0.0, 400);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    scoreDraw();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    B.draw();
    for(i = 0; i < 3; i++)
        M[i].draw();
    V.draw();
/*    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    for(i = 0; i < 6; i++)
    {
        for(j = 0; j < 6; j++)
        {
            setArr[0] = (0.9)*j; setArr[1] = (0.9)*i; setArr[2] = 0.0;
            C1[6*count + j].set(0.4, 0.5, setArr);
            C1[6*count + j].draw();
        }
        count++;
    }
    glPopMatrix();
    count = 0;
    glPushMatrix();
    glTranslatef(-25.0, -25.0, 0.0);
    for(i = 0; i < 6; i++)
    {
        for(j = 0; j < 6; j++)
        {
            setArr[0] = (0.9)*j; setArr[1] = (0.9)*i; setArr[2] = 0.0;
            C2[6*count + j].set(0.4, 0.7, setArr);
            C2[6*count + j].draw();
        }
        count++;
    }
    glPopMatrix();*/
    P.draw();
    if(F.release == 1)
        T.draw();
    Hit.draw();
    if(F.release == 0)
        SET.draw();
    glutSwapBuffers();
}
void updateCamera()
{
    if(F.cameraType == 1)
    {
        if(deltaMove)
            V1.updateCameraCoord(deltaMove); 
    }
    if(F.cameraType == 3)
    {
        V3.atVertex[0] = T.Vertex[0]; V3.atVertex[1] = T.Vertex[1]; V3.atVertex[2] = 1.0; //V3.toVertex[0] = cos(DEG2RAD(T.tangle)) ; 
        V3.toVertex[0] = cos(atan((Hit.Vertex[1] - T.Vertex[1])/(Hit.Vertex[0] - T.Vertex[0]))); 
        V3.toVertex[1] = sin(atan((Hit.Vertex[1] - T.Vertex[1])/(Hit.Vertex[0] - T.Vertex[0])));
        V3.toVertex[2] = T.Vertex[2] + 1.0;
        if(atan(T.beta) > 0)
        {
             V3.upVector[0] = 0.0; V3.upVector[1] = atan(T.alpha); V3.upVector[2] = atan(T.beta);
        }
        else
        {
             V3.upVector[0] = 0.0; V3.upVector[1] = 0.0; V3.upVector[2] = 1.0;
        }
    }
    if(F.cameraType == 4)
    {
        V4.atVertex[0] = T.Vertex[0] - (cos(DEG2RAD(T.tangle))*2.0); V4.atVertex[1] = T.Vertex[1] - (sin(DEG2RAD(T.tangle))*2.0); V4.atVertex[2] = T.Vertex[2] + 1.0;
        V4.toVertex[0] = cos(DEG2RAD(T.tangle)); V4.toVertex[1] = sin(DEG2RAD(T.tangle)); V4.toVertex[2] = T.Vertex[2] + 1.0; 
        if(atan(T.beta) > 0)
        {    
             V4.upVector[0] = 0.0; V4.upVector[1] = atan(T.alpha); V4.upVector[2] = atan(T.beta);
        }
        else
        {
            V4.upVector[0] = 0.0; V4.upVector[1] = 0.0; V4.upVector[2] = 1.0;
        }

    }
    if(F.cameraType == 5)
    {
        if(deltaMove)
            cam.updateCameraCoord(deltaMove);
    }
    glutPostRedisplay();
}       
void pressSpecialKey(int key, int xx, int yy)
{
    switch (key) 
    {
        case GLUT_KEY_UP : deltaMove = 1.0; break;
        case GLUT_KEY_DOWN : deltaMove = -1.0; break;
    }
}
void releaseSpecialKey(int key, int x, int y)
{
    switch (key) 
    {
        case GLUT_KEY_UP : deltaMove = 0.0; break;
        case GLUT_KEY_DOWN : deltaMove = 0.0; break;
    }
} 
void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) 
    {
        if (state == GLUT_DOWN) 
        { 
            F.isDragging = 1;
	    F.xDragStart = x;
            F.yDragStart = y;
	}
	else  
        {
            if(F.cameraType == 1)
	        V1.angle += F.deltaAngle;
            else if(F.cameraType == 5)
                cam.angle += F.deltaAngle;
	    F.isDragging = 0;
	}
    }
}
void mouseMove(int x, int y)
{
    if (F.isDragging) 
    {
        if(F.cameraType == 1)
        { 
            F.deltaAngle = (x - F.xDragStart) * 0.005;
	    V1.toVertex[0] = -sin(V1.angle + F.deltaAngle);
	    V1.toVertex[1] = cos(V1.angle + F.deltaAngle);
        }
        else if(F.cameraType == 5)
        {
            F.deltaAngle = (x - F.xDragStart) * 0.005;
            float delta2 = (y - F.yDragStart) * 0.005;
            cam.toVertex[0] = -sin(cam.angle + F.deltaAngle);
            cam.toVertex[1] = cos(cam.angle + F.deltaAngle);
            cam.toVertex[2] = sin(cam.angle + delta2);
        }
    }
}
void pressKey(unsigned char key, int x, int y)
{
    if(key == 'p')
        F.cameraType = 1;
    if(key == 'o')
        F.cameraType = 2;
    if(key == 't')
        F.cameraType = 3;
    if(key == 'f')
        F.cameraType = 4;
    if(key == 'h')
        F.cameraType = 5;
    if(key == 'q')
        T.move(1);
    if(key == 'w')
        T.move(-1);
    if(key == 'm')
        SET.angle -= 1;
    if(key == 'n')
        SET.angle += 1;
    if(key == 32)
    {
        T.tangle = SET.angle;
        F.release = 1;
        T.speed = F.speed;
    }
    if(key == 'b')
    {
        F.speed += 1;
        if(F.speed >= 7)
            F.speed = 7;
    }
    if(key == 'v')
    {
        F.speed -= 1;
        if(F.speed <= 0)
            F.speed = 0;
    }
}
void changeSize(int w, int h)
{
    float ratio =  ((float) w) / ((float) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}
void update2(int value)
{
    if(F.release == 1)
    {
    float argg[3];
     argg[0] = T.Vertex[0] + (cos(DEG2RAD(T.tangle)) * T.speed);
    argg[1] = T.Vertex[1] + (sin(DEG2RAD(T.tangle)) * T.speed);

    T.speed *= 0.95;
    argg[2] = get_Z(argg[0], argg[1]);
    Tuple gg = get_normal(argg[0], argg[1]);
    T.alpha = gg.alpha;
    T.beta = gg.beta;
    T.setVertex(argg);
    T.temp_angle += 0.01;
    T.temp_angle2 += 1;
    if(T.temp_angle >= 23)
        exit(0);
    T.angle = (T.angle + 1);
    checkColl();
    F.timer += 5;
    }
    glutTimerFunc(25, update2, 0);
}
int main(int argc, char **argv)
{
    cout << "HELLO WELCOME TO THE TOP GAME: PLAY IT AND WIN IT" << endl;
    MountainInit();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Top Spinning Game");
    glutFullScreen();
    glutReshapeFunc(changeSize);
    glutDisplayFunc(renderScene);
    glutIdleFunc(updateCamera);
    glutSpecialFunc(pressSpecialKey);
    glutSpecialUpFunc(releaseSpecialKey);
    glutKeyboardFunc(pressKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutTimerFunc(25, update2, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutMainLoop();
    return 0;
}
    
