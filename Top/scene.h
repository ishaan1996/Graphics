#ifndef __SCENE_INCLUDED_H__
#define __SCENE_INCLUDED_H__
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

using namespace std;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Class for defining the surface(plane) of the scene */
class Surface
{
	public:
		float len;
		float vertex1[3];
		float vertex2[3];
		float vertex3[3];
		float vertex4[3];

		Surface();
		void draw();
};

Surface::Surface()
{
	len = 200.0;
	vertex1[0] = 100.0; vertex1[1] = 100.0; vertex1[2] = 0.0;
	vertex2[0] = -100.0; vertex2[1] = 100.0; vertex2[2] = 0.0;
	vertex3[0] = -100.0; vertex3[1] = -100.0; vertex3[2] = 0.0;
	vertex4[0] = 100.0; vertex4[1] = -100.0, vertex4[2] = 0.0;
}

void Surface::draw()
{
	glPushMatrix();
	glColor4f(210.0f/256.0f, 42.0f/256.0f, 0.0f/256.0f, 0.7);
	glBegin(GL_POLYGON);
	glVertex3f(vertex1[0], vertex1[1], vertex1[2]);
	glVertex3f(vertex2[0], vertex2[1], vertex2[2]);
	glVertex3f(vertex3[0], vertex3[1], vertex3[2]);
	glVertex3f(vertex4[0], vertex4[1], vertex4[2]);
	glEnd();
	glPopMatrix();
}

/* Class for defining the mountains in the scene */
class Mountain
{
	public:
		float transVertex[3];
		float moveToVertex[3];

		void set(float arr1[], float arr2[]);
		void draw();
};
void Mountain::set(float arr1[], float arr2[])
{
	for(int i = 0; i < 3; i++)
	{
		transVertex[i] = arr1[i];
		moveToVertex[i] = arr2[i];
	}
}
void Mountain::draw()
{
	int i;
	float j, height;
	float raise;
	float set;
	glPushMatrix();
	glTranslatef(transVertex[0], transVertex[1], transVertex[2]);
	for(i = 0; i <= 180; i++)
	{
		glPushMatrix();
		glRotatef(i, 0, 0, -1);
		glTranslatef(moveToVertex[0], moveToVertex[1], moveToVertex[2]);
		j = 0.0; height = 0.0;
		while(j < 16)
		{
			if(j < 2)
				raise = 0.2;
			else if(j < 4)
				raise = 0.4;
			else if(j < 6)
				raise = 0.6;
			else if(j < 8)
				raise = 0.4;
			else if(j < 10)
				raise = -0.4;
			else if(j < 12)
				raise = -0.6;
			else if(j < 14)
				raise = -0.4;
			else
				raise = -0.2;

			glBegin(GL_TRIANGLE_STRIP);
			set = 139.0f/256.0f;
			if(height / 15 > set)
				set = height / 15;
			glColor3f(set, 0.30f, 0.30f);
			glVertex3f(-j, -0.45, height);
			glVertex3f(-j - 1, -0.45, height + raise);
			glVertex3f(-j, 0, height);
			glVertex3f(-j - 1, 0, height + raise);
			height += raise;
			glEnd();
			j++;
		}
		glPopMatrix();
	}
	glPopMatrix();
}

/* Class to make boundaries on the side frame */
class Boundary
{
	public:
		float treeRadius;
		float treeHeight;
		float baseDown;
		float baseUp;
		float Vertex1[2];
		GLUquadric *trunk;

		Boundary();
		void draw();
};
Boundary::Boundary()
{
	treeRadius = 0.75;
	trunk = gluNewQuadric();
	treeHeight = 0.8;
	baseDown = 0.2;
	baseUp = 0.1;
	Vertex1[0] = 38.0, Vertex1[1] = 60.0;
}
void Boundary::draw()
{
	int i;
	for(i = 0; i <= 8; i++)
	{
		glPushMatrix();
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

		glTranslatef(60, 38 - (i*9.5), 0);
		glColor3f(1.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(0.0, 0.0, treeRadius + treeHeight);
		glutSolidSphere(treeRadius, 20, 20);
		glPopMatrix();
		glColor3f(0.18f, 0.0, 0.0);
		gluCylinder(trunk, baseDown, baseUp, treeHeight, 20, 20);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-60, 38 - (i*9.5), 0);
		glColor3f(1.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(0.0, 0.0, treeRadius + treeHeight);
		glutSolidSphere(treeRadius, 20, 20);
		glPopMatrix();
		glColor3f(0.18, 0.0, 0.0);
		gluCylinder(trunk, baseDown, baseUp, treeHeight, 20, 20);
		glPopMatrix();
	}
	for(i = 1; i <= 14; i++)
	{
		glPushMatrix();
		glTranslatef(-60 + (i * 8), 38, 0);
		glColor3f(1.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(0.0, 0.0, treeRadius + treeHeight);
		glutSolidSphere(treeRadius, 20, 20);
		glPopMatrix();
		glColor3f(0.18, 0.0, 0.0);
		gluCylinder(trunk, baseDown, baseUp, treeHeight, 20, 20);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-60 + (i * 8), -38, 0);
		glColor3f(1.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(0.0, 0.0, treeRadius + treeHeight);
		glutSolidSphere(treeRadius, 20, 20);
		glPopMatrix();
		glColor3f(0.18, 0.0, 0.0);
		gluCylinder(trunk, baseDown, baseUp, treeHeight, 20, 20);
		glPopMatrix();
	} 

}

/* Class for making valleys */
class Valley
{
	public:
		float transVertex[3];
		float moveToVertex[3];

		void set(float arr1[], float arr2[]);
		void draw();
};
void Valley::set(float arr1[], float arr2[])
{
	for(int i = 0; i < 3; i++)
	{
		transVertex[i] = arr1[i];
		moveToVertex[i] = arr2[i];
	}
}
void Valley::draw()
{
	int i;
	float j, height;
	float raise;
	float set;
	glPushMatrix();
	glTranslatef(transVertex[0], transVertex[1], transVertex[2]);
	for(i = 0; i <= 180; i++)
	{
		glPushMatrix();
		glRotatef(i, 0, 0, -1);
		glTranslatef(moveToVertex[0], moveToVertex[1], moveToVertex[2]);
		j = 0.0; height = 0.0;
		while(j < 16)
		{
			if(j < 2)
				raise = 0.2;
			else if(j < 4)
				raise = 0.4;
			else if(j < 6)
				raise = 0.6;
			else if(j < 8)
				raise = 0.4;
			else if(j < 10)
				raise = -0.4;
			else if(j < 12)
				raise = -0.6;
			else if(j < 14)
				raise = -0.4;
			else
				raise = -0.2;

			glBegin(GL_TRIANGLE_STRIP);
			set = 139.0f/256.0f;
			if(height / 15 > set)
				set = height / 15;
			glColor3f(set, 0.30f, 0.30f);
			glVertex3f(-j, -0.45, -height);
			glVertex3f(-j - 1, -0.45, -(height + raise));
			glVertex3f(-j, 0, -height + 0.01);
			glVertex3f(-j - 1, 0, -(height + raise));
			height += raise;
			glEnd();
			j++;
		}
		glPopMatrix();
	}
	glPopMatrix();
}

/* Class for creating Solid Cylinders */
class Cylinder
{
	public:
		GLUquadric *fig;
		float base;
		float top;
		float height;
		float Vertex[3];    
		Cylinder();
		void set(float b, float t, float h, float arr[]);
		void draw();
};
Cylinder::Cylinder()
{
	fig = gluNewQuadric();
}
void Cylinder::set(float b, float t, float h, float arr[])
{
	base = b; top = t; height = h;
	for(int i = 0; i < 3; i++)
		Vertex[i] = arr[i];
}
void Cylinder::draw()
{
	glPushMatrix();
	glTranslatef(Vertex[0], Vertex[1], Vertex[2]);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	gluCylinder(fig, base, top, height, 20, 20);  
	glPopMatrix();
}

/* Class for making Needle like looking obstacles */
class Cone
{
	public:
		float base; 
		float height;
		float Vertex[3];

		void set(float b, float h, float arr[]);
		void draw();
};
void Cone::set(float b, float h, float arr[])
{
	for(int i = 0; i < 3; i++)
		Vertex[i] = arr[i];
	base = b;
	height = h;
}
void Cone::draw()
{
	glPushMatrix();
	glTranslatef(Vertex[0], Vertex[1], Vertex[2]);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCone(base, height, 10, 2);
	glPopMatrix();
}

float get_Z(float x, float y)
{
	float z;
	float distance1 = sqrt(((25-x)*(25-x))+((25-y)*(25-y)));
	float distance2 = sqrt((-45-x)*(-45-x) + ((28-y)*(28-y)));
	float distance3 = sqrt((45-x)*(45-x) + ((-28-y)*(-28-y)));
	float distance4 = sqrt((25-x)*(25-x) + ((9-y)*(9-y)));
	int quot;
	float rem;
	if(distance1<8)
	{
		distance1 = 8 - distance1;
		quot = distance1/2;
		rem = distance1 - (quot*2);
		if(quot<1)
		{	z = 0;
			z+=rem*0.2;
		}
		else if(quot<2)
		{	z = 0.4;
			z+= rem*0.4;
		}
		else if(quot<3)
		{
			z = 1.2;
			z+=rem*0.6;
		}
		else if(quot<4)
		{
			z = 2.4;
			z+=rem*0.7;
		}
	}
	else if(distance2<8)
	{
		distance2 = 8 - distance2;
		quot = distance2/2;
		rem = distance2 - (quot*2);
		if(quot<1)
		{	z = 0;
			z+=rem*0.2;
		}
		else if(quot<2)
		{	z = 0.4;
			z+= rem*0.4;
		}
		else if(quot<3)
		{
			z = 1.2;
			z+=rem*0.6;
		}
		else if(quot<4)
		{
			z = 2.4;
			z+=rem*0.7;
		}
	}
	else if(distance3<8)
	{
		distance3 = 8 - distance3;
		quot = distance3/2;
		rem = distance3 - (quot*2);
		if(quot<1)
		{	z = 0;
			z+=rem*0.2;
		}
		else if(quot<2)
		{	z = 0.4;
			z+= rem*0.4;
		}
		else if(quot<3)
		{
			z = 1.2;
			z+=rem*0.6;
		}
		else if(quot<4)
		{
			z = 2.4;
			z+=rem*0.7;
		}
	}
	else if(distance4<8)
	{
		distance4 = 8 - distance4;
		quot = distance4/2;
		rem = distance4 - (quot*2);
		if(quot<1)
		{	z = 0;
			z-=rem*0.2;
		}
		else if(quot<2)
		{	z = -0.4;
			z -= rem*0.4;
		}
		else if(quot<3)
		{
			z = -1.2;
			z -=rem*0.6;
		}
		else if(quot<4)
		{
			z = -2.4;
			z -=rem*0.7;
		}
	}

	else
		z = 0;
	return z;
}

struct Tuple
{
	float alpha;
	float beta;
	float z;
};
Tuple get_normal(float x, float y)
{
	float distance1 = sqrt(((25-x)*(25-x))+((25-y)*(25-x)));
	float distance2 = sqrt((-45-x)*(-45-x) + ((28-y)*(28-y)));
	float distance3 = sqrt((45-x)*(45-x) + ((-28-y)*(-28-y)));
	float distance4 = sqrt((25-x)*(25-x) + ((9-y)*(9-y)));
	Tuple angles;
	float k;
	if(distance1<8.1)
	{
		distance1 = 8 - distance1;
		angles.beta = (y-25)/(x-25);

		if(distance1 < 2.001)
		{
			k = 0.2;
		}
		else if(distance1 < 4.001)
		{
			k = 0.4;
		}
		else if(distance1 < 6.001)
		{
			k = 0.6;
		}
		else if(distance1 < 8.001)
		{
			k = 0.4;
		}
		x = x - 25;
		y = y - 25;
		if(x<0)
		{
			k = -k;
		}
		angles.alpha = k;
	}
	else if(distance2<8.1)
	{
		distance2 = 8 - distance2;
		angles.beta = (y-(-45))/(x-28);

		if(distance2 < 2.001)
		{
			k = 0.2;
		}
		else if(distance2 < 4.001)
		{
			k = 0.4;
		}
		else if(distance2 < 6.001)
		{
			k = 0.6;
		}
		else if(distance2 < 8.001)
		{
			k = 0.4;
		}
		x = x - 28;
		y = y - (-45);
		if(x<0)
		{
			k = -k;
		}
		angles.alpha = k;
	}

	else if(distance3<8.1)
	{
		distance3 = 8 - distance3;
		angles.beta = (y-45)/(x-(-28));

		if(distance3 < 2.001)
		{
			k = 0.2;
		}
		else if(distance3 < 4.001)
		{
			k = 0.4;
		}
		else if(distance3 < 6.001)
		{
			k = 0.6;
		}
		else if(distance3 < 8.001)
		{
			k = 0.4;
		}
		x = x - (-28);
		y = y - 45;
		if(x<0)
		{
			k = -k;
		}
		angles.alpha = k;
	}
	if(distance4<8.1)
	{
		distance4 = 8 - distance4;
		angles.beta = (y-9)/(x-25);

		if(distance4 < 2.001)
		{
			k = 0.2;
		}
		else if(distance4 < 4.001)
		{
			k = 0.4;
		}
		else if(distance4 < 6.001)
		{
			k = 0.6;
		}
		else if(distance4 < 8.001)
		{
			k = 0.4;
		}
		x = x - 25;
		y = y - 9;
		if(x<0)
		{
			k = -k;
		}
		angles.alpha = -k;
	}

	else
	{
		angles.alpha = 0.0;
		angles.beta = 0.0;
	}
	return angles;
}

#endif
