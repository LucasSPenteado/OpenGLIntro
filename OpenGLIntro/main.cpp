#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_s.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//------------Old way to program vertex and fragment shaders-----------//
//const char *vertexShaderSource = "#version 330 core \n"
//"layout (location = 0) in vec3 aPos; \n"
//"layout (location = 1) in vec3 aColor;"
//"out vec3 ourColor;\n"
//"void main() \n"
//"{ \n"
//"	gl_Position = vec4(aPos, 1.0); \n"
////"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); \n" color was set directly in the vertex shader
//"	ourColor = aColor; \n"
//"} \0";

//const char *fragmentShaderSource = "#version 330 core \n"
//"out vec4 FragColor; \n"
////"in vec4 vertexColor; \n"
////"uniform vec4 ourColor;" uniform that was used to set the color of the triangle in the fragment shader
//"in vec3 ourColor; \n"
//"void main() \n"
//"{ \n"
////"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
////"	FragColor = vertexColor; \n"
//"	FragColor = vec4(ourColor, 1.0); \n"
//"} \0";
//-----------------------------------------------------------------------//


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_HEIGHT, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//----------Old method of using the vertex shader code directly in the main----------//
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//Old way to link vertex and fragment shader and link
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	//----------------------------------------------------------------------------------------//

	//Coordinates for two tringles to form a rectangle
	//float vertices[] = {
	//	0.5f,  0.5f, 0.0f,  // top right
	//	0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//	-0.5f,  0.5f, 0.0f   // top left 
	//};

	//Single triangle
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f,  0.5f, 0.0f
	//};

	Shader ourShader("3.3.shader.vs", "3.3.shader.fs");

	//Single triangle with color data
	float vertices[] = {
		//First Triangle
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    // top
	};

	//---------Vertices for the second triangle used in the exercise---------------//
	//float vertices2[] = {
	//	//Second Triangle
	//	 //positions		   //colors	
	//	 0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	//	 0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	//	 0.45f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  //top
	//};
	//----------------------------------------------------------------------------//

	//to draw both triangles to form a rectangle without passing at the same point twice
	//unsigned int indices[] = {
	//	0, 1, 3,
	//	1, 2, 3
	//};

	//---------------Exercise to draw two triangles using different VAO and VBO's---------------//
	//unsigned int VBOs[2], VAOs[2];
	//glGenVertexArrays(2, VAOs);
	//glGenBuffers(2, VBOs);

	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAOs[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(1);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(0);

	////Second VAO and VBO
	//glBindVertexArray(VAOs[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(1);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(0);
	//------------------------------------------------------------------------------------------//

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);

	//To only show the outline of the vertices
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//-------To make the triangle blink green and black--------//
		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		//---------------------------------------------------------//

		ourShader.use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//--------Binded multiple VAOs and VBOs----------//
		//glBindVertexArray(VAOs[0]);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//glBindVertexArray(VAOs[1]);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//----------------------------------------------//
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); To draw both tirangles to form a rectangle

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//glDeleteVertexArrays(2, VAOs); used when created both VAOs and VBOs
	//glDeleteBuffers(2, VBOs);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}