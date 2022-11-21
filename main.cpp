#include "./include/open_gl_loader.h"
#include "./include/rubik.h"
#include "./include/solver/solve.h"
#include "./include/solver/random.h"
#include "./include/menu.h"

//#define __EXTERNAL_MOVEMENTS__

using namespace std;

float separation = 0.2f;

int timer = 900;

Point center(0.2f, 0.2f, 0.0f);
Rubik *myRubik;

void processInput(GLFWwindow*);
std::string get_reversed(std::string);

OpenGlLoader OpenGL(SCR_WIDTH, SCR_HEIGHT);
std::string history;
std::string moves, reverse_solution;

int prime = 0;
int write = 0;

int main()
{

	myRubik = new Rubik(center, separation);
	moves = "LU";
	std::vector<std::string> a = get_solution(to_cube_not(string_to_vector(moves)));
	std::string b = format_solution(a);
	menu();

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

	if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
	{
		prime++;
		prime %= 2;
		if (prime) std::cout << "Prime Movements activated!" << std::endl;
		else std::cout << "Prime Movements desactivated!" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		std::cout << moves << std::endl;
		reverse_solution.append(moves);
		myRubik->read_solution(moves);
		myRubik->set_speed(1.5f);
		myRubik->enable();
		history.append(moves);
		moves.clear();
	}
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (!history.empty())
		{
			std::vector<std::string> a = get_solution(to_cube_not(string_to_vector(history)));
			std::string b = format_solution(a);
			for (auto e : a)
			{
				std::cout << e << std::endl;
			}
			std::cout << b << std::endl;

			myRubik->read_solution(b);
			reverse_solution.clear();
			history.clear();
		}
	}

	if (prime)
	{
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			moves.push_back(F_PRIME_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			moves.push_back(B_PRIME_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			moves.push_back(U_PRIME_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			moves.push_back(D_PRIME_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			moves.push_back(R_PRIME_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			moves.push_back(L_PRIME_MOVEMENT);
			std::cout << moves << std::endl;
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
			moves.push_back(F_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			moves.push_back(B_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			moves.push_back(U_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			moves.push_back(D_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			moves.push_back(R_MOVEMENT);
			std::cout << moves << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			moves.push_back(L_MOVEMENT);
			std::cout << moves << std::endl;
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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
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

std::string get_reversed(std::string all_moves)
{
	std::string ans;
	for (size_t i = all_moves.size() - 1; ~i; i--)
	{
		switch (all_moves[i])
		{
			case F_MOVEMENT:
				ans.push_back(F_PRIME_MOVEMENT);
				break;
			case F_PRIME_MOVEMENT:
				ans.push_back(F_MOVEMENT);
				break;
			case D_MOVEMENT:
				ans.push_back(D_PRIME_MOVEMENT);
				break;
			case D_PRIME_MOVEMENT:
				ans.push_back(D_MOVEMENT);
				break;
			case U_MOVEMENT:
				ans.push_back(U_PRIME_MOVEMENT);
				break;
			case U_PRIME_MOVEMENT:
				ans.push_back(U_MOVEMENT);
				break;
			case B_MOVEMENT:
				ans.push_back(B_PRIME_MOVEMENT);
				break;
			case B_PRIME_MOVEMENT:
				ans.push_back(B_MOVEMENT);
				break;
			case R_MOVEMENT:
				ans.push_back(R_PRIME_MOVEMENT);
				break;
			case R_PRIME_MOVEMENT:
				ans.push_back(R_MOVEMENT);
				break;
			case L_MOVEMENT:
				ans.push_back(L_PRIME_MOVEMENT);
				break;
			case L_PRIME_MOVEMENT:
				ans.push_back(L_MOVEMENT);
				break;
			case M_MOVEMENT:
				ans.push_back(M_PRIME_MOVEMENT);
				break;
			case M_PRIME_MOVEMENT:
				ans.push_back(M_MOVEMENT);
				break;
			case E_MOVEMENT:
				ans.push_back(E_PRIME_MOVEMENT);
				break;
			case E_PRIME_MOVEMENT:
				ans.push_back(E_MOVEMENT);
				break;
			case S_MOVEMENT:
				ans.push_back(S_PRIME_MOVEMENT);
				break;
			case S_PRIME_MOVEMENT:
				ans.push_back(S_MOVEMENT);
				break;
			default:
				break;
		}
	}
	return ans;
}