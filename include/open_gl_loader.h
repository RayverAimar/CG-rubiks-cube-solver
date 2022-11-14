#ifndef __OPEN_GL_LOADER_H__
#define __OPEN_GL_LOADER_H__

#include <iostream>

#include "./directories.h"
#include "./utils.h"
#include "./camera.h"

void framebuffer_size_callback(GLFWwindow*, int, int);
void key_callback(GLFWwindow*, int, int, int, int);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

class OpenGlLoader
{
public:

	GLFWwindow* window;
	Camera camera;

	/* Constructor & Destructor */
	OpenGlLoader();
	OpenGlLoader(const unsigned int&, const unsigned int&);
	~OpenGlLoader();

	/* Getters */
	bool isOpen();

	/* Auxiliar Functions */

	void clearBuffers();
	void update();

private:
	
	/*Auxiliar Methods*/

	void glfwCallbacksSetter();
	void glfwContextInit();
	void glfwGladLoader();
	void glfwWindowInit();

	unsigned int width, height;
};

OpenGlLoader::OpenGlLoader() : width(SCR_WIDTH), height(SCR_HEIGHT)
{
	glfwInit();
	glfwContextInit();
	glfwWindowInit();
	glfwCallbacksSetter();
	glfwGladLoader();
	glEnable(GL_DEPTH_TEST);
}

OpenGlLoader::OpenGlLoader(const unsigned int& _width, const unsigned int& _height) : width(_width), height(_height), camera(Camera(glm::vec3(0.0f, 0.0f, 3.0f)))

{
	glfwInit();
	glfwContextInit();
	glfwWindowInit();
	glfwCallbacksSetter();
	glfwGladLoader();
	//glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
}

OpenGlLoader::~OpenGlLoader()
{
	glfwTerminate();
}

void OpenGlLoader::glfwCallbacksSetter()
{
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
	glfwSetKeyCallback(this->window, key_callback);
	glfwSetCursorPosCallback(this->window, mouse_callback);
	glfwSetScrollCallback(this->window, scroll_callback);
}

void OpenGlLoader::glfwContextInit()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void OpenGlLoader::glfwGladLoader()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}
}

void OpenGlLoader::glfwWindowInit()
{
	this->window = glfwCreateWindow(this->width, this->height, SCR_TITLE, NULL, NULL);

	if (this->window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(this->window);
}

bool OpenGlLoader::isOpen()
{
	return !glfwWindowShouldClose(this->window);
}

void OpenGlLoader::clearBuffers()
{
	glClearColor(0.501f, 0.501f, 0.501f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGlLoader::update()
{
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

#endif // !__OPEN_GL_LOADER_H__
