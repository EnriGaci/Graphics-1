#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <math.h>

#include "GL/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions

model md;
static float tx = 0.0;
static float tz = 0.0;
static float ty = 0.0;
static float shipTx = 0.0;
static float shipTy = 0.0;
static float shipTz = 0.0;
static bool animate = false;
static bool go_on=true;

bool* keyStates = new bool[256];

static float blendingPower = 0.8;
static int change = 1;

static float cometTx = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 10; 
static float cometTy = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 10; 

static float sunRayScale1 = 0.0;
static float sunRayScale2 = 0.0;
static float sunRayScale3 = 0.0;

static float elikesRotation = 0.0;
static float shipRotateX = 0.0;
static float shipRotateY = 0.0;
static float shipSpeed = 6.0f;
static float pedals = 0.0;
static float flaps = 0.0;

Sun sun;

using namespace std;

typedef struct Star {

	int x;
	int y;
	int z;
	float blending;
	
}Star;

Star starArray[30];

void keimeno(const char *str,float size)
{

	int max = strlen(str);
	glPushMatrix();

		glScalef(size,size,size);
		for (int i=0;i<max;i++)
		  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);

	glPopMatrix();
        cout << "COLISION DETECTED" << endl;
}

void Render()
{    
  //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();


  glTranslatef( shipTx , shipTy , -110 );
		glRotatef( shipRotateX , 1, 0 , 0);
		glRotatef( shipRotateY , 0 , 1 , 0);
  glTranslatef( -shipTx , -shipTy , +110 );

 //Stars
	int i;
	for ( i = 0; i < 100; ++i)
	{
		glPushMatrix();

			starArray[i].blending = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			glColor4f( 1, 1, 1 , starArray[i].blending );
			glTranslatef(starArray[i].x ,starArray[i].y,starArray[i].z);
			glutSolidSphere(2, 100, 100);

		glPopMatrix();
	}
//-----

//Sun
	glPushMatrix();

		sun.SunRadius = 8 ;
		sun.SunSlices = 100;
		sun.SunStacks = 100;
		sun.x = 100;
		sun.y = 70 ;
		sun.z = -150;

		glPushMatrix();
		
			glColor3f(1, 1, 0.4);
			glTranslatef( sun.x ,sun.y ,sun.z ); // θέση ήλιου
			glutSolidSphere(sun.SunRadius, sun.SunSlices, sun.SunStacks);

		glPopMatrix();
		
		// Ακτίνες ήλιου
		glPushMatrix();
			 
			glColor4f( 1, 1, 0.4, blendingPower );
			glTranslatef(sun.x , sun.y , sun.z ); 
			glScalef( sunRayScale1 , sunRayScale2 , sunRayScale3);
			glutSolidSphere( sun.SunRadius*1.5 , sun.SunSlices , sun.SunStacks );

		glPopMatrix();
		//--------------

	glPopMatrix();
//---

//Spaceship
	glPushMatrix();
        
        glTranslatef(shipTx,shipTy,-110 );
        keyOperations();
        glRotatef(pedals,0,0,1);
        glRotatef(flaps,1,0,0);

		GLdouble radius = 8;
		GLint slices = 100;
		GLint stacks = 100;

		//Σώμα
		glPushMatrix();
		
			glColor3f(0.8, 0.1, 0.1);
			glutSolidSphere(radius, slices, stacks);

		glPopMatrix();
		//----------

		//Φτερά
		glPushMatrix();
		
			glColor3f(0.2, 0.2, 0.2);
			glScalef(1 , 0.08 , 0.2);
			glutSolidSphere( radius *2.8 , slices, stacks);

		glPopMatrix();
		//----------

        GLUquadricObj *obj = gluNewQuadric(); // σχήμα που χρησιμοποιώ για έλικα

		//Ουρά
		glPushMatrix();
		
			glColor3f(0.2, 0.2, 0.2);

	        glPushMatrix();
		        glColor3f(0.2, 0.2, 0.2);
                glTranslatef( 0.0 , 6.0 , 19);
		        glScalef( 0.5, 0.04 , 0.12);
		        glutSolidSphere( radius *2.8 , slices, stacks);
	        glPopMatrix();

            glPushMatrix();
                glTranslatef( 0.0 , 0.0 , 4 );
                glBegin(GL_POLYGON);
		            gluCylinder(obj, 6, 1 , 16, 30, 30);
		        glEnd();
            glPopMatrix();

            glPushMatrix();
                glTranslatef( 0.0 , -1.5 , 19 );
                glRotatef( -90 , 1 , 0 , 0 );
                glBegin(GL_POLYGON);
	                gluCylinder(obj, 1, 2.0 , 8, 30, 30);
		        glEnd();
            glPopMatrix();

		glPopMatrix();
		//-----

		//Πιλότος
		glPushMatrix();
		
			glColor3f(0.3, 0.3, 0.3);
			glTranslatef(0,8,0);
			glutSolidSphere( radius / 4 , slices, stacks);

		glPopMatrix();
		//-------

		//Πιλοτήριο
		glPushMatrix();
		
			glColor4f(0.1, 0.1, 0.1 , 0.7 );
			glTranslatef(0,8,0);
			glutSolidSphere( radius / 2 , slices, stacks);

		glPopMatrix();
		//-------
                

	            //Ελικες//
	            
	    /* Δεξιά έλικα */
	    glPushMatrix();

	        glColor3f(0.1, 0.1, 0.8 );
	        glTranslatef( radius*2.5 - 8 , 0 , -3.8 );
	        glRotatef( elikesRotation , 0 , 0 , 1 );
	        glRotatef( 90 , 1 , 0 , 0 );
	        glBegin(GL_POLYGON);
	        gluCylinder(obj, 1.0, 0.5 , 5, 30, 30);
	        glEnd();

	    glPopMatrix();

	    glPushMatrix();

	        glColor3f(0.1, 0.1, 0.8 );
	        glTranslatef( radius*2.5 - 8 , 0 , -3.8 );
	        glRotatef( elikesRotation , 0 , 0 , 1 );
	        glRotatef( -90 , 1 , 0 , 0 );
	        glBegin(GL_POLYGON);
	        gluCylinder(obj, 1.0, 0.5 , 5, 30, 30);
	        glEnd();

	    glPopMatrix();

	    glPushMatrix();

	        glColor3f(0.1, 0.1, 0.8 );
	        glTranslatef( radius*2.5 - 8 , 0 , -3.8 );
	        glRotatef( elikesRotation , 0 , 0 , 1 );
	                    glRotatef( 90 , 0 , 0 , 1 );
	        glRotatef( -90 , 1 , 0 , 0 );
	        glBegin(GL_POLYGON);
	        gluCylinder(obj, 1.0, 0.5 , 5, 30, 30);
	        glEnd();

	    glPopMatrix();

	    glPushMatrix();

	        glColor3f(0.1, 0.1, 0.8 );
	        glTranslatef( radius*2.5 - 8 , 0 , -3.8 );
	        glRotatef( elikesRotation , 0 , 0 , 1 );
            glRotatef( -90 , 0 , 0 , 1 );
	        glRotatef( -90 , 1 , 0 , 0 );
	        glBegin(GL_POLYGON);
	        gluCylinder(obj, 1.0, 0.5 , 5, 30, 30);
	        glEnd();

	    glPopMatrix();

	            
	    /*---------------*/

	    /* Αριστερή έλικα */
	    glPushMatrix();

	        glColor3f(0.1, 0.1 , 0.8 );
	        glTranslatef( -(radius*2.5) + 8 , 0 , -3.8 );
	        glRotatef( elikesRotation , 0 , 0 , 1 );
	        glRotatef( 90 , 1 , 0 , 0 );
	        glBegin(GL_POLYGON);
	        gluCylinder(obj, 1.0, 0.5 , 5, 30, 30);
	        glEnd();
	    glPopMatrix();

	    glPushMatrix();

	        glColor3f(0.1, 0.1 , 0.8 );
	        glTranslatef( -(radius*2.5) + 8 , 0 , -3.8 );
	        glRotatef( elikesRotation , 0 , 0 , 1 );
	        glRotatef( -90 , 1 , 0 , 0 );
	        glBegin(GL_POLYGON);
	        gluCylinder(obj, 1.0, 0.5 , 5, 30, 30);
	        glEnd();
	    glPopMatrix();

	    glPushMatrix();

	        glColor3f(0.1, 0.1, 0.8 );
	        glTranslatef( -(radius*2.5) + 8 , 0 , -3.8 );
	        glRotatef( elikesRotation , 0 , 0 , 1 );
            glRotatef( 90 , 0 , 0 , 1 );
	        glRotatef( -90 , 1 , 0 , 0 );
	        glBegin(GL_POLYGON);
	        gluCylinder(obj, 1.0, 0.5 , 5, 30, 30);
	        glEnd();

	    glPopMatrix();

	    glPushMatrix();

	        glColor3f(0.1, 0.1, 0.8 );
	        glTranslatef( -(radius*2.5) + 8 , 0 , -3.8 );
	        glRotatef( elikesRotation , 0 , 0 , 1 );
            glRotatef( -90 , 0 , 0 , 1 );
	        glRotatef( -90 , 1 , 0 , 0 );
	        glBegin(GL_POLYGON);
	        gluCylinder(obj, 1.0, 0.5 , 5, 30, 30);
	        glEnd();

	    glPopMatrix();

	    /*---------------*/

	glPopMatrix();
//-----------	

	glTranslatef( 0, 0 , shipTz );

//Comet
	glPushMatrix();
		glColor3f(1.0f, 0.35f, 0.05f);  // Set drawing colour
		glTranslatef(tx,ty,tz);
		glTranslatef(0,0, shipTz  - 600 );
		glScalef(0.02 , 0.02 , 0.02);
		DisplayModel(md);
	glPopMatrix();
//-----

  if (go_on) check_colision();
  if(!go_on){
		glColor3f(0.5, 0.2, 0.6);
		glTranslatef(-20.0,20,-350);
		keimeno("COLISION : EXIT PLEASE!!!!!",0.05f);
  }

  
  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
  glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one
}

void Resize(int w, int h)
{ 
  // define the visible area of the window ( in pixels )
  if (h==0) h=1;
  glViewport(0,0,w,h); 

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 
  gluPerspective(60.0, (float)w/(float)h, 1.0, 500.0);
}

void Idle()
{
	if(animate){
		tx += cometTx;
		ty += cometTy;
                
        if( !(keyStates['a']) && !(keyStates['d']) ){
                if( (pedals>0 && pedals<6) || (pedals<0 && pedals>-6) ) pedals=0;
                else if(pedals<0) pedals+=8; 
                else if(pedals>0) pedals-=8;                       
        }

        if( !(keyStates['w']) && !(keyStates['s']) ){
                if( (flaps>0 && flaps<6) || (flaps<0 && flaps>-6) ) flaps=0;
                else if(flaps<0) flaps+=10; 
                else if(flaps>0) flaps-=10;                       
        }
               
		shipTz += 3.0f;
		elikesRotation -= 200.0f;

		srand(time(NULL));

		if( shipTz >= 350 ){

			shipTz = 0;

			int chance = rand() , direction;
			if( chance % 2 == 0)
				direction = 1;
			else
				direction = -1;

			cometTx = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 10)* direction;

			chance = rand();

			if( chance % 2 == 0)
				direction = 1;
			else
				direction = -1; 

			cometTy = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 10)*direction;
		}

		float xScale = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 10 ;
		float yScale = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 10;
		float zScale = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 10;

		blendingPower -= 0.01 * change;
		sunRayScale1 += xScale ;
		sunRayScale2 += yScale ;
		sunRayScale3 += zScale ;
		
		if( blendingPower < 0.0){
			sunRayScale1 = 0.0;
			sunRayScale2 = 0.0;
			sunRayScale3 = 0.0;
			blendingPower = 0.6;
		}
	}

	glutPostRedisplay();
}

void keyOperations (void) { 

	if ( keyStates['q'] ) {
		exit(0);
	}	
	if ( keyStates['a'] ) {
		shipTx -= shipSpeed;
                if(pedals<80) pedals+=shipSpeed;
	}
	if ( keyStates['d'] ) {
		shipTx += shipSpeed;
                if(pedals>-80) pedals-=shipSpeed;
	}
	if ( keyStates['w'] ) {
		shipTy += shipSpeed;
                if(flaps<60) flaps += shipSpeed;
	}
	if ( keyStates['s'] ) {
		shipTy -= shipSpeed;
                if(flaps>-60) flaps -= shipSpeed;
	}
	if ( keyStates['i'] ) {
		shipRotateX += shipSpeed;
	}
	if ( keyStates['k'] ) {
		shipRotateX -= shipSpeed;
	}
	if ( keyStates['j'] ) {
		shipRotateY -= shipSpeed;
	}
	if ( keyStates['l'] ) {
		shipRotateY += shipSpeed;
	}

} 

void keyUp (unsigned char key, int x, int y) {  
	keyStates[key] = false; // Set the state of the current key to not pressed  
}

void Keyboard(unsigned char key,int x,int y) {
	
	keyStates[key] = true;

	glutPostRedisplay();

}

void Mouse(int button,int state,int x,int y) {
	 if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	 {
		 animate = !animate;
         glutPostRedisplay();
         if(!go_on && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) exit(0);
	 }
}

void StarsInit(){

	int i , maxRange , count; 

	srand(time(NULL));

	count = sizeof(starArray) / sizeof(Star);
	maxRange = 450;

	for ( i = 0; i < count; ++i)
	{
		starArray[i].x = rand() % maxRange + ( (rand() % maxRange) - maxRange );
		starArray[i].y = rand() % maxRange + ( (rand() % maxRange) - maxRange );
		starArray[i].z = rand() % maxRange + ( (rand() % maxRange) - maxRange );

		while( ( (starArray[i].x * starArray[i].x) + (starArray[i].y * starArray[i].y) + (starArray[i].z*starArray[i].z) ) < 180000 ){

			starArray[i].x = rand() % maxRange + ( (rand() % maxRange) - maxRange );
			starArray[i].y = rand() % maxRange + ( (rand() % maxRange) - maxRange );
			starArray[i].z = rand() % maxRange + ( (rand() % maxRange) - maxRange );

		}

		starArray[i].blending = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}

}


void Setup()  // TOUCH IT !! 
{ 

	StarsInit();

	ReadFile(&md);

	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);
    
	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { sun.x, sun.y, sun.z, 1.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
        
	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	
    /*    
        GLfloat specref[] = { 0.05, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT,GL_AMBIENT,specref);
        specref[0]=0.5;
        specref[1]=0.4;
        specref[2]=0.4;
        glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);
        specref[0]=0.7;
        specref[1]=0.04;
        specref[2]=0.04;
        glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,0.078125);
        
   */

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//01
	glFrontFace(GL_CCW);
 

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

void ReadFile(model *md)
{
	char v;
	char c , c2;
	int i = 0 , j = 0, k;
	string line;

	ifstream obj_file("asteroid.obj");                   // Open the file for reading OBJINFO.TXT
   
	if (obj_file.fail()){
                cout <<"ERROR READING FILE" << endl;
		exit(1);
        }

	md->vertices = 9122;                               // Get the number of vertices
	md->faces = 18240;									// Get the number of faces

	while(!obj_file.eof())
	{
    	c = obj_file.peek(); // des ton epomeno xarakthra

	    if ( c == 'v'){ // ean einai v

	    	obj_file.get(c2); // pare to xarakthra kai apo8hkeuse ton 
	    	
		    if( (c = obj_file.peek() ) != 'n' ){ // des ton epomeno xarakthra an den einai vn tote apo8hkeuse th grammh

	    		obj_file >> md->obj_points[i].x;
				obj_file >> md->obj_points[i].y;
				obj_file >> md->obj_points[i].z;
			    i++;
			}

		}
		else if( c == 'f'){ //alliws an o prwtos xarakthras einai f
			
			obj_file >> v;

			obj_file >> md->obj_faces[j].vtx[0];

			obj_file.get(c2);
			obj_file.get(c2);
			obj_file >> k;

			obj_file >> md->obj_faces[j].vtx[1];

			obj_file.get(c2);
			obj_file.get(c2);
			obj_file >> k;

			obj_file >> md->obj_faces[j].vtx[2];

			obj_file.get(c2);
			obj_file.get(c2);
			obj_file >> k;
			j++;
			
		}
		else{ // alliws
			getline (obj_file,line); // phgaine sthn epomenh grammh
		}
	    	
	}

   obj_file.close();

}

void DisplayModel(model md)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md.faces; i++)
	{
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0]-1].x,md.obj_points[md.obj_faces[i].vtx[0]-1].y,md.obj_points[md.obj_faces[i].vtx[0]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1]-1].x,md.obj_points[md.obj_faces[i].vtx[1]-1].y,md.obj_points[md.obj_faces[i].vtx[1]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2]-1].x,md.obj_points[md.obj_faces[i].vtx[2]-1].y,md.obj_points[md.obj_faces[i].vtx[2]-1].z);
	}

	glEnd();
	glPopMatrix();

}

float absv(float n1,float n2){
 	float n=n1-n2;
 	if (n<0) return -n;
	return n;
 }

void check_colision(){
 	if(absv(tx,shipTx)<25 && absv(ty,shipTy)<25 && shipTz>235 && shipTz<250){
 		animate=go_on=false;
 	}
 }
