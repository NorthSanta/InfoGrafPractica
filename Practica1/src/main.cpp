//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include "glm.hpp"
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


using namespace glm;
using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
float vertex1 = 0.5;
float vertex2 = -0.5;
float mixed;
float rot;
float angleX, angleY;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Shader* shade;
mat4 finalMatrix;
mat4 matrix = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1

};
mat4 rotation = matrix;
mat4 proj;
mat4 vision;
mat4 model;
GLuint texture;
GLuint texture2;
int main() {
	//initGLFW
//TODO
	if (!glfwInit()) {
		cout << "Error GLFW" << endl;
		exit(EXIT_FAILURE);
	}
	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
//TODO
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	//set GLEW and inicializate
//TODO
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al cargar glew" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//set function when callback
//TODO
	glfwSetKeyCallback(window, key_callback);
	//set windows and viewport
//TODO
	
	//fondo
//TODO
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 0.8, 1.0);
	
	//cargamos los shader
	shade = new Shader("./src/textureVertex3D.vertexshader", "./src/textureFragment3D.fragmentshader");
	

	GL_MAX_VERTEX_ATTRIBS;
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	vec3 vectprop = vec3(1, 2, 2); 
	
	// Definir el buffer de vertices
	/*GLfloat Vertex[]{
		vertex1,0,0,
		-0.5,1,0,
		0.5,1,0,
		vertex2,0,0
	};*/
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	int width, height;
	unsigned char* image = SOIL_load_image("./src/texture.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	int width2, height2;
	unsigned char* image2 = SOIL_load_image("./src/texture2.png", &width2, &height2, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image2);

	GLint Element[]{
		1,0,3,
		3,2,1
		
	};


	
	mat4 scalar = scale(matrix, vec3(0.5f, -0.5f, 0));
	mat4 translation = translate(matrix, vec3(0.5f, 0.5f, 0));

	

	/*GLfloat VertexBufferObject[] = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};*/
	GLfloat VertexBufferCube[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	vec3 CubesPositionBuffer[] = {
		vec3(0.0f ,  0.0f,  0.0f),
		vec3(2.0f ,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f , -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f , -2.0f, -2.5f),
		vec3(1.5f ,  2.0f, -2.5f),
		vec3(1.5f ,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};

	// Definir el EBO
	GLuint EBO;
	// Crear los VBO, VAO y EBO
	GLuint VBO;
	GLuint VAO;
	//reservar memoria para el VAO, VBO y EBO
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	//Establecer el objeto
	glBindVertexArray(VAO);
	
		//Declarar el VBO y el EBO
		glBindBuffer(GL_ARRAY_BUFFER,VBO );
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferCube), VertexBufferCube, GL_STATIC_DRAW);
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubesPositionBuffer), CubesPositionBuffer, GL_STATIC_DRAW);

		//Enlazar el buffer con openGL
		

	
		//Establecer las propiedades de los vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		//liberar el buffer
	
		glBindVertexArray(0);
		//liberar el buffer de vertices

		float AspectRatio = WIDTH / HEIGHT;
		float FOV = radians(60.f);
		

		proj = perspective(FOV, AspectRatio, 0.1f, 100.f);
		
		vision = translate(vision, vec3(0, 0, -3));
		
		model = rotate(model, radians(50.f), glm::vec3(1.0f, 0.0f, 0.0));
		model = translate(model, vec3(0, -0.5f, 0));
		model = scale(model, vec3(1, 1, 1));
		
		//finalMatrix = proj*vision*model;

		glEnable(GL_DEPTH_TEST);
		//pintar texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shade->Program, "ourTexture"), 0);

	//bucle de dibujado
		while (!glfwWindowShouldClose(window))
		{
			
			GLint proji = glGetUniformLocation(shade->Program, "proj");
			glUniformMatrix4fv(proji, 1, GL_FALSE, value_ptr(proj));
			GLint visi = glGetUniformLocation(shade->Program, "vision");
			glUniformMatrix4fv(visi, 1, GL_FALSE, value_ptr(vision));
			/*GLint modeli = glGetUniformLocation(shade->Program, "model");
			glUniformMatrix4fv(modeli, 1, GL_FALSE, value_ptr(model));*/
			/*GLint variableRot = glGetUniformLocation(shade->Program, "rotation");
			glUniformMatrix4fv(variableRot, 1, GL_FALSE, value_ptr(rotation));
			GLint variableTrans = glGetUniformLocation(shade->Program, "translation");
			glUniformMatrix4fv(variableTrans, 1, GL_FALSE, value_ptr(translation));
			GLint variableScale = glGetUniformLocation(shade->Program, "scalar");
			glUniformMatrix4fv(variableScale, 1, GL_FALSE, value_ptr(scalar));*/
		
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

			//model = translate(model, vec3(-0.01, 0, 0));
			//model = rotate(model,radians(1.0f), vec3(0.0f, 1.f, 0.0f));
			
			
			//definir la matriz de proyeccion
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//glOrtho(-10, 10, -10.f, 10.f, -1.0f, 10.f);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			//establecer el shader
			//glUseProgram(programID);
			//shade->USE();
			
			//glBindVertexArray(VAO);
			//pitar el VAO
			/*if (WIDEFRAME) {
				
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				//glBindVertexArray(0);
				
			}*/
			
			
			
			
			
			
			

			//glBindTexture(GL_TEXTURE_2D, texture);
			//glBindTexture(GL_TEXTURE_2D, texture2);
			shade->USE();
			glBindVertexArray(VAO); {

				//manual
				mat4 trans, totalRot, rotY ,rotX;
				trans = translate(trans, CubesPositionBuffer[0]);
				rotX = rotate(rotX, radians(angleX), vec3(1.f, 0.f, 0.f));
				rotY = rotate(rotY, radians(angleY), vec3(0.f, 1.f, 0.f));
				totalRot = rotX*rotY;
				model = trans * totalRot;
				glUniformMatrix4fv(glGetUniformLocation(shade->Program, "model"), 1, GL_FALSE, value_ptr(model));
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glDrawArrays(GL_TRIANGLES, 0, 36);

				//auto
				for (int i = 1; i < 10; i++)
				{
					mat4 trans, rot;
					trans = translate(trans, CubesPositionBuffer[i]);
					rot = rotate(rot, (float)glfwGetTime()*radians(30.f), vec3(1.f, 0.f, 0.f));
					model = trans*rot;
					
					glUniformMatrix4fv(glGetUniformLocation(shade->Program, "model"), 1, GL_FALSE, value_ptr(model));
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
				//model = GenerateModelMatrix(vec3(0.f), vec3(rotation, rotation*0.5f, 0), CubesPositionBuffer[i]);
				

			}
				
			
			

			//glDrawElements(GL_TRIANGLES,0,GL_UNSIGNED_INT,0);
			//glBindVertexArray(0);

			
			
			glBindVertexArray(0);
			// Swap the screen buffers
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	// liberar la memoria de los VAO, EBO y VBO
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		WIDEFRAME = !WIDEFRAME;
		
	}
	//rotacion
	if (key == GLFW_KEY_UP) {
	
		angleX -= 1;
	}
	else if (key == GLFW_KEY_DOWN) {
	
		angleX += 1;
	}
	if (key == GLFW_KEY_RIGHT) {
		
		angleY += 1;
		
	}
	else if (key == GLFW_KEY_LEFT) {
		
		angleY -= 1;
		
	}
	//cambio textura
	if (key == GLFW_KEY_1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shade->Program, "ourTexture"), 0);
	}
	else if (key == GLFW_KEY_2) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shade->Program, "ourTexture"), 0);
	}
}


