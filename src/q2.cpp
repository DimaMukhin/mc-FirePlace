// Based on: http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/CHAPTER03/WINDOWS_VERSIONS/example2.cpp
// Modified to isolate the main program and use GLM

/*
	Assignment 1
	Question 2
	Instructor: John Braico
	Programed By: Dima Mukhin
	Student #: 7773184
*/

#include "common.h"
#include "Mesh2.h"
#include "MineCraftBlock.h"
#include "FireParticleSystem.h"

#include <time.h>
#include <stdlib.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *WINDOW_TITLE = "Question 2";
const double FRAME_RATE_MS = 1000.0/60.0;

GLuint projectionUniformLocation, viewUniformLocation, modelUniformLocation, baseColorUniformLocation;
MineCraftBlock *mcBlock;
FireParticleSystem *fpSystem;

//----------------------------------------------------------------------------

// OpenGL initialization
void init()
{
	// initializing random number generator
	srand(static_cast <unsigned> (time(0)));

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    GLuint vColorIntensity = glGetAttribLocation( program, "vColorIntensity" );

	projectionUniformLocation = glGetUniformLocation(program, "projection");
	viewUniformLocation = glGetUniformLocation(program, "view");
	modelUniformLocation = glGetUniformLocation(program, "model");
	baseColorUniformLocation = glGetUniformLocation(program, "baseColor");

	// setting default value for model transformation so we dont get junk if we forget to set it
	glm::mat4 uniform;
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(uniform));

	// setting default view transformation
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));

	// setting default base color
	glm::vec4 defaultBaseColor = glm::vec4(0.1f, 0.4f, 0.1f, 1.0f);
	glUniform4fv(baseColorUniformLocation, 1, glm::value_ptr(defaultBaseColor));

	// initializing minecraft block
	mcBlock = new MineCraftBlock(modelUniformLocation);
	mcBlock->init(vPosition, vColorIntensity);

	// initializing fire particle system
	fpSystem = new FireParticleSystem(100, modelUniformLocation, mcBlock, glm::vec3(0, 0, 0), vPosition, vColorIntensity, baseColorUniformLocation);

    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); 
}

//----------------------------------------------------------------------------

GLfloat angle = 0.0f;
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// displaying particle system
	fpSystem->display();

	// fireplace (logs)
	glUniform4fv(baseColorUniformLocation, 1, glm::value_ptr(glm::vec3(0.45f, 0.2f, 0.0f)));
	for (GLfloat angle = 0.0f; angle < 360.0f; angle += 60.0f) {
		glm::mat4 stickmodel;
		stickmodel = glm::scale(stickmodel, glm::vec3(0.25f, 0.25f, 0.25f));
		stickmodel = glm::rotate(stickmodel, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

		stickmodel = glm::translate(stickmodel, glm::vec3(-1.0f, 0.5f, 0.0f));
		mcBlock->display(stickmodel);

		stickmodel = glm::translate(stickmodel, glm::vec3(-1.0f, 0.0f, 0.0f));
		mcBlock->display(stickmodel);

		stickmodel = glm::translate(stickmodel, glm::vec3(-1.0f, 0.0f, 0.0f));
		mcBlock->display(stickmodel);
	}

	// floor
	glUniform4fv(baseColorUniformLocation, 1, glm::value_ptr(glm::vec3(0.1f, 0.4f, 0.0f)));
	glm::mat4 floorModel;

	floorModel = glm::translate(glm::mat4(), glm::vec3(-0.5f, -0.5f, 0.5f));
	mcBlock->display(floorModel);

	floorModel = glm::translate(glm::mat4(), glm::vec3(0.5f, -0.5f, 0.5f));
	mcBlock->display(floorModel);

	floorModel = glm::translate(glm::mat4(), glm::vec3(0.5f, -0.5f, -0.5f));
	mcBlock->display(floorModel);

	floorModel = glm::translate(glm::mat4(), glm::vec3(-0.5f, -0.5f, -0.5f));
	mcBlock->display(floorModel);

    glutSwapBuffers();
	glFinish();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
       case 033: // Escape Key
       case 'q': case 'Q':
	       exit( EXIT_SUCCESS );
          break;
    }
}

//----------------------------------------------------------------------------
bool moveCamera = false;
void mouse( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN ) {
		moveCamera = !moveCamera;
    }
}

//----------------------------------------------------------------------------
GLfloat cameraAngleOfRotation = 0.0f;
void update( void )
{
	// update fire particle system
	fpSystem->update();

	// updating camera
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 5.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, glm::radians(cameraAngleOfRotation), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));

	// rotate the camera
	if (moveCamera) {
		cameraAngleOfRotation += 0.2f;
		if (cameraAngleOfRotation >= 360.0f)
			cameraAngleOfRotation = 0.0f;
	}
}

//----------------------------------------------------------------------------

void reshape( int width, int height )
{
	GLfloat aspect = GLfloat(width) / height;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.5f, 100.0f);
	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
}