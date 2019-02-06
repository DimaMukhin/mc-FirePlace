// Based on: http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/CHAPTER03/WINDOWS_VERSIONS/example2.cpp
// Modified to isolate the main program and use GLM

// Display a color cube
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.

#include "common.h"
#include "Mesh.h"
#include "Mesh2.h"
#include "BlockMeshFactory.h"
#include "FireParticle.h"
#include "FireParticleSystem.h"

#include <time.h>
#include <stdlib.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *WINDOW_TITLE = "Question 2";
const double FRAME_RATE_MS = 1000.0/60.0;

GLuint projectionUniformLocation, viewUniformLocation, modelUniformLocation;
Mesh *greenBlockMesh, *redBlockMesh;
Mesh2 *subdividedSquare;
FireParticleSystem *fireParticleSystem;

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

	/*greenBlockMesh = block::createBlockMesh(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	greenBlockMesh->init(vPosition, vColor);

	redBlockMesh = block::createBlockMesh(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	redBlockMesh->init(vPosition, vColor);

	fireParticleSystem = new FireParticleSystem(50, modelUniformLocation, redBlockMesh, glm::vec3(0, 0, 0), vPosition, vColor);*/

	GLuint numOfVertices = 25;
	glm::vec4 *vertices = new glm::vec4[numOfVertices] {
		glm::vec4(-0.5f, 0.0f, 0.5f, 1.0f),
		glm::vec4(-0.25f, 0.0f, 0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.5f, 1.0f),
		glm::vec4(0.25f, 0.0f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.0f, 0.5f, 1.0f),

		glm::vec4(-0.5f, 0.0f, 0.25f, 1.0f),
		glm::vec4(-0.25f, 0.0f, 0.25f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.25f, 1.0f),
		glm::vec4(0.25f, 0.0f, 0.25f, 1.0f),
		glm::vec4(0.5f, 0.0f, 0.25f, 1.0f),

		glm::vec4(-0.5f, 0.0f, 0.0f, 1.0f),
		glm::vec4(-0.25f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.25f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.5f, 0.0f, 0.0f, 1.0f),

		glm::vec4(-0.5f, 0.0f, -0.25f, 1.0f),
		glm::vec4(-0.25f, 0.0f, -0.25f, 1.0f),
		glm::vec4(0.0f, 0.0f, -0.25f, 1.0f),
		glm::vec4(0.25f, 0.0f, -0.25f, 1.0f),
		glm::vec4(0.5f, 0.0f, -0.25f, 1.0f),

		glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f),
		glm::vec4(-0.25f, 0.0f, -0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, -0.5f, 1.0f),
		glm::vec4(0.25f, 0.0f, -0.5f, 1.0f),
		glm::vec4(0.5f, 0.0f, -0.5f, 1.0f),
	};

	glm::vec4 *colors = new glm::vec4[numOfVertices] {
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),

		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),

		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),

		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),

		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),
	};

	GLuint numOfIndices = 6 * 16;
	GLuint *indices = new GLuint[numOfIndices] {
		0, 1, 6, 6, 5, 0,
		1, 2, 7, 7, 6, 1,
		2, 3, 8, 8, 7, 2,
		3, 4, 9, 9, 8, 3,

		5, 6, 11, 11, 10, 5,
		6, 7, 12, 12, 11, 6,
		7, 8, 13, 13, 12, 7,
		8, 9, 14, 14, 13, 8,

		10, 11, 16, 16, 15, 10,
		11, 12, 17, 17, 16, 11,
		12, 13, 18, 18, 17, 12,
		13, 14, 19, 19, 18, 13,

		15, 16, 21, 21, 20, 15,
		16, 17, 22, 22, 21, 16,
		17, 18, 23, 23, 22, 17,
		18, 19, 24, 24, 23, 18,
	};

	subdividedSquare = new Mesh2(vertices, colors, numOfVertices, indices, numOfIndices);
	subdividedSquare->init(vPosition, vColor);

    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

GLfloat angle = 0.0f;
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	subdividedSquare->display();

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
}

//----------------------------------------------------------------------------

void reshape( int width, int height )
{
	GLfloat aspect = GLfloat(width) / height;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.5f, 100.0f);
	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
}