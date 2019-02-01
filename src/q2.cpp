// Based on: http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/CHAPTER03/WINDOWS_VERSIONS/example2.cpp
// Modified to isolate the main program and use GLM

// Display a color cube
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.

#include "common.h"
#include "Mesh.h"
#include "BlockMeshFactory.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *WINDOW_TITLE = "Question 2";
const double FRAME_RATE_MS = 1000.0/60.0;

GLuint projectionUniformLocation, viewUniformLocation, modelUniformLocation;
Mesh *blockMesh;

//----------------------------------------------------------------------------

// OpenGL initialization
void
init()
{
    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    GLuint vColor = glGetAttribLocation( program, "vColor" ); 

	projectionUniformLocation = glGetUniformLocation(program, "projection");
	viewUniformLocation = glGetUniformLocation(program, "view");
	modelUniformLocation = glGetUniformLocation(program, "model");

	// setting default value for model transformation so we dont get junk if we forget to set it
	glm::mat4 uniform;
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(uniform));

	// setting default view transformation
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));

	blockMesh = block::createBlockMesh();
	blockMesh->init(vPosition, vColor);

    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glm::mat4 model;

	model = glm::translate(glm::mat4(), glm::vec3(-0.5f, -0.5f, 0.5f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	blockMesh->display();

	model = glm::translate(glm::mat4(), glm::vec3(0.5f, -0.5f, 0.5f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	blockMesh->display();

	model = glm::translate(glm::mat4(), glm::vec3(0.5f, -0.5f, -0.5f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	blockMesh->display();

	model = glm::translate(glm::mat4(), glm::vec3(-0.5f, -0.5f, -0.5f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	blockMesh->display();

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

void
mouse( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN ) {
    }
}

//----------------------------------------------------------------------------

void
update( void )
{
    
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
	GLfloat aspect = GLfloat(width) / height;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.5f, 100.0f);
	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
}