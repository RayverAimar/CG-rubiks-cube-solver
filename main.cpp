#include "./include/open_gl_loader.h"
#include "./include/rubik.h"

using namespace std;

float separation = 0.2f;

int timer = 900;

Point center(0.2f, 0.2f, 0.0f);
Rubik *myRubik;

void processInput(GLFWwindow*);

OpenGlLoader OpenGL(SCR_WIDTH, SCR_HEIGHT);

int prime = 0;
int write = 0;

int main()
{

	myRubik = new Rubik(center, separation);
	std::string solution = "FFFFDDDDRRLLRRLL";
	myRubik->read_solution(solution);
	while (OpenGL.isOpen())
	{

		OpenGL.clearBuffers();
		
		myRubik->render();

		OpenGL.update();
	}

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		prime++;
		prime %= 2;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		write++;
		write %= 2;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		myRubik->enable();
		myRubik->set_timer(118);
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		myRubik->enable();
		myRubik->set_timer(118);
		myRubik->start_solving();
	}

	if (write)
	{
		std::cout << " Writer mode! " << std::endl;
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			myRubik->solution.push(F_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			myRubik->solution.push(F_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			myRubik->solution.push(F_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			myRubik->solution.push(F_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			myRubik->solution.push(F_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			myRubik->solution.push(F_MOVEMENT);
		}
	}

	else
	{
		if (!myRubik->in_movement())
		{
			if (prime)
			{
				if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->fPrime = true;
				}
				if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->bPrime = true;
				}
				if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->uPrime = true;
				}
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->dPrime = true;
				}
				if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->lPrime = true;
				}
				if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->rPrime = true;
				}
				if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->mPrime = true;
				}
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->ePrime = true;
				}
				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->sPrime = true;
				}
			}
			else
			{
				if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->f = true;
				}
				if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->b = true;
				}
				if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->u = true;
				}
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->d = true;
				}
				if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->l = true;
				}
				if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->r = true;
				}
				if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->m = true;
				}
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->e = true;
				}
				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				{
					myRubik->enable();
					myRubik->s = true;
				}
			}
		}
	}
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		std::cout << "W" << std::endl;
		OpenGL.camera.ProcessKeyboard(FORWARD, deltaTime);
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		OpenGL.camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		OpenGL.camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		OpenGL.camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	OpenGL.camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	OpenGL.camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
