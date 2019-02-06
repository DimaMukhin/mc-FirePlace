// Based on: http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/CHAPTER03/WINDOWS_VERSIONS/example2.cpp
// Modified to isolate the main program and use GLM

// Display a color cube
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.

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

	mcBlock = new MineCraftBlock(modelUniformLocation);
	mcBlock->init(vPosition, vColorIntensity);

	fpSystem = new FireParticleSystem(50, modelUniformLocation, mcBlock, glm::vec3(0, 0, 0), vPosition, vColorIntensity, baseColorUniformLocation);

    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

GLfloat angle = 0.0f;
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//mcBlock->display();

	fpSystem->display();

	//fireParticleSystem->display();

	//// fireplace

	//for (GLfloat angle = 0.0f; angle < 360.0f; angle += 60.0f) {
	//	glm::mat4 stickmodel;
	//	stickmodel = glm::scale(stickmodel, glm::vec3(0.25f, 0.25f, 0.25f));
	//	stickmodel = glm::rotate(stickmodel, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	//	stickmodel = glm::translate(stickmodel, glm::vec3(-1.0f, 0.5f, 0.0f));
	//	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(stickmodel));
	//	redBlockMesh->display();

	//	stickmodel = glm::translate(stickmodel, glm::vec3(-1.0f, 0.0f, 0.0f));
	//	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(stickmodel));
	//	redBlockMesh->display();

	//	stickmodel = glm::translate(stickmodel, glm::vec3(-1.0f, 0.0f, 0.0f));
	//	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(stickmodel));
	//	redBlockMesh->display();
	//}

	//// floor
	//glm::mat4 floorModel;

	//floorModel = glm::translate(glm::mat4(), glm::vec3(-0.5f, -0.5f, 0.5f));
	//glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(floorModel));
	//greenBlockMesh->display();

	//floorModel = glm::translate(glm::mat4(), glm::vec3(0.5f, -0.5f, 0.5f));
	//glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(floorModel));
	//greenBlockMesh->display();

	//floorModel = glm::translate(glm::mat4(), glm::vec3(0.5f, -0.5f, -0.5f));
	//glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(floorModel));
	//greenBlockMesh->display();

	//floorModel = glm::translate(glm::mat4(), glm::vec3(-0.5f, -0.5f, -0.5f));
	//glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(floorModel));
	//greenBlockMesh->display();

    glutSwapBuffers();
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

void mouse( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN ) {
    }
}

//----------------------------------------------------------------------------

void update( void )
{
	//fireParticleSystem->update();
	fpSystem->update();
}

//----------------------------------------------------------------------------

void reshape( int width, int height )
{
	GLfloat aspect = GLfloat(width) / height;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.5f, 100.0f);
	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
}