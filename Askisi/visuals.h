#ifndef _VISUALS_H_
#define _VISUALS_H_

#include <GL/gl.h>

typedef struct Sun{

	float x; 
	float y; 
	float z;
	GLdouble SunRadius ;
	GLint SunSlices ;
	GLint SunStacks ;

}Sun;

struct point 
{
	float x; 
	float y; 
	float z; 
};

struct face
{
	int vtx[3];
};

struct model
{
	point obj_points[9122];
	face obj_faces[18240];
	int vertices;
	int faces;
};


//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

void ReadFile(model*);
//Function for reading a model file

void DisplayModel(model);
// Function for displaying a model

void Keyboard(unsigned char key,int x,int y);
// Function for handling keyboard events.

void Mouse(int button,int state,int x,int y); 
// Function for handling mouse events


void keyOperations(void);	// κάνει τις μεταβολές που γίνονται με τα κουμπια

void keyUp(unsigned char key, int x, int y); // κρατάει ποια κουμπια πατήθηκαν

void StarsInit(void); // φτιάχνει τα αστέρια

GLuint LoadTexture(void);

void background(void);

void check_colision();

float absv(float n1,float n2);

#endif
