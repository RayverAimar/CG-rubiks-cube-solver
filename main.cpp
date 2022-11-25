#include "./include/open_gl_loader.h"
#include "./include/menu.h"
#include "./include/hyper_cube.h"

//#define __EXTERNAL_MOVEMENTS__

using namespace std;

float diameter = 0.1f;

OpenGlLoader OpenGL(SCR_WIDTH, SCR_HEIGHT);
Point center(0.0f, 0.0f, 0.0f);
HyperCube* myHyperCube;

int prime = 0;

int main()
{
	myHyperCube = new HyperCube(center, diameter);
	
	menu();
	
	while (OpenGL.isOpen())
	{

		OpenGL.clearBuffers();
		
		myHyperCube->render();

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

	if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
	{
		prime++;
		prime %= 2;
		if (prime) std::cout << "Prime Movements activated!" << std::endl;
		else std::cout << "Prime Movements desactivated!" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		srand(time(NULL));
		for (int i = 0; i < myHyperCube->Rubiks.size(); i++)
		{
			myHyperCube->Rubiks[i]->scramble();
		}
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		//(*myHyperCube->cur_cube)->solve();
		std::cout << "Looking for best solution" << std::endl;
		for (int i = 0; i < myHyperCube->Rubiks.size(); i++)
		{
			myHyperCube->Rubiks[i]->solve();
		}
	}
	if (prime)
	{
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(F_PRIME_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(B_PRIME_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(U_PRIME_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(D_PRIME_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(R_PRIME_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(L_PRIME_MOVEMENT);
		}
#ifdef __EXTERNAL_MOVEMENTS__
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		{
			moves.push_back(M_PRIME_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			moves.push_back(E_PRIME_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			moves.push_back(S_PRIME_MOVEMENT);
			std::cout << moves << std::endl;
		}
#endif // __EXTERNAL_MOVEMENTS__
	
	}
	else
	{
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(F_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(B_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(U_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(D_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(R_MOVEMENT);
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			(*myHyperCube->cur_cube)->append(L_MOVEMENT);
		}
#ifdef __EXTERNAL_MOVEMENTS__

		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		{
			moves.push_back(M_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			moves.push_back(E_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			moves.push_back(S_MOVEMENT);
			std::cout << moves << std::endl;
		}
#endif // __EXTERNAL_MOVEMENTS__
	}
}