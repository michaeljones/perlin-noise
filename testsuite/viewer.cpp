#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>

#include <iostream>

#include <perlin.h>

#define ESCAPE 27
#define KEY_Q 938

/* The number of our GLUT window */
int window; 

void InitGL(int Width, int Height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
	glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
	glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset The Projection Matrix
	
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
	
	glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
	if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
		Height=1;

	glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
	glLoadIdentity();				// Reset The View

    perlin::GeneratorFactory factory;

    perlin::Noise3D* noise = factory.create3D();

	glBegin( GL_POINTS );

	static int z=0;

	z += 1;

    for ( int i=-250; i<250; ++i )
    {
        for ( int j=-250; j<250; ++j )
        {
            float value = noise->generate( i/20.0f, j/20.0f, z/20.0f );
            value = value/2.0 + 0.5f;

			glColor3f( value, value, value );

			glVertex3f( i/40.0f, j/40.0f, -20.0f );
        }
    }

    delete noise;

	glEnd();

	glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
	/* avoid thrashing this procedure */
	usleep(10);
	
	/* If escape is pressed, kill everything. */
	if ( key == ESCAPE || key == KEY_Q ) 
	{ 
		/* shut down our window */
		glutDestroyWindow(window); 
		
		/* exit the program...normal termination. */
		exit(0);									 
	}
}

int main(int argc, char **argv) 
{	
	/* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
		 X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */	
	glutInit(&argc, argv);	

	/* Select type of Display mode:	 
		 Double buffer 
		 RGBA color
		 Alpha components supported 
		 Depth buffer */	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);	

	/* get a 640 x 480 window */
	glutInitWindowSize(640, 480);	

	/* the window starts at the upper left corner of the screen */
	glutInitWindowPosition(0, 0);	

	/* Open a window */	
	window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");	

	/* Register the function to do all our OpenGL drawing. */
	glutDisplayFunc(&DrawGLScene);	

	/* Go fullscreen.	This is as soon as possible. */
	glutFullScreen();

	/* Even if there are no events, redraw our gl scene. */
	glutIdleFunc(&DrawGLScene);

	/* Register the function called when our window is resized. */
	glutReshapeFunc(&ReSizeGLScene);

	/* Register the function called when the keyboard is pressed. */
	glutKeyboardFunc(&keyPressed);

	/* Initialize our window. */
	InitGL(640, 480);
	
	/* Start Event Processing Engine */	
	glutMainLoop();	

	return 1;
}

