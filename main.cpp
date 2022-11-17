#include "./include/open_gl_loader.h"
#include "./include/rubik.h"
#include "./solver/solver.h"

using namespace std;

float separation = 0.2f;

int timer = 900;

Point center(0.2f, 0.2f, 0.0f);
Rubik *myRubik;

void processInput(GLFWwindow*);
std::string get_solution(std::string);

OpenGlLoader OpenGL(SCR_WIDTH, SCR_HEIGHT);
std::string history;
std::string solution, reverse_solution;

int prime = 0;
int write = 0;

int main()
{

	myRubik = new Rubik(center, separation);
	solution = "BDUDLUF";
	std::cout << solver::format_movements(solution) << std::endl;

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
		std::cout << solution << std::endl;
		reverse_solution.append(solution);
		myRubik->read_solution(solution);
		myRubik->set_speed(1.5f);
		myRubik->enable();
		history.append(solution);
		solution.clear();
	}
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		std::string perfect_solution = solver::solve(solver::format_movements(history));
		std::cout << "perfect solution: " << perfect_solution << std::endl;
		std::cout << "format solution: " << solver::format_solution(perfect_solution) << std::endl;
		//solution = get_solution(reverse_solution);
		myRubik->read_solution(solver::format_solution(perfect_solution));
		reverse_solution.clear();
		history.clear();
	}

	if (prime)
	{
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			solution.push_back(F_PRIME_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			solution.push_back(B_PRIME_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			solution.push_back(U_PRIME_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			solution.push_back(D_PRIME_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			solution.push_back(R_PRIME_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			solution.push_back(L_PRIME_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		{
			solution.push_back(M_PRIME_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			solution.push_back(E_PRIME_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			solution.push_back(S_PRIME_MOVEMENT);
			std::cout << solution << std::endl;
		}
	}
	else
	{
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			solution.push_back(F_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			solution.push_back(B_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			solution.push_back(U_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			solution.push_back(D_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			solution.push_back(R_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			solution.push_back(L_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		{
			solution.push_back(M_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			solution.push_back(E_MOVEMENT);
			std::cout << solution << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			solution.push_back(S_MOVEMENT);
			std::cout << solution << std::endl;
		}
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

std::string get_solution(std::string all_moves)
{
	std::string ans;
	for (int i = all_moves.size() - 1; ~i; i--)
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