#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "./include/open_gl_loader.h"
#include "./include/menu.h"
#include "./include/hyper_cube.h"

using namespace std;

float diameter = 0.1f;

OpenGlLoader OpenGL(SCR_WIDTH, SCR_HEIGHT);
Point center(0.0f, 0.0f, 0.0f);
HyperCube* myHyperCube;

int prime = 0;

// Render a warmed-up frame and dump it as a PPM image, then exit.
// Used by `--screenshot <path>` (CI smoke test + README capture).
static void dump_screenshot(const char* path)
{
	myHyperCube->enable();
	myHyperCube->set_expanding();

	// Pull the camera back so the scrambled cube fits comfortably in frame.
	delete camera;
	camera = new Camera(glm::vec3(0.0f, 0.0f, 6.0f));

	// Long warmup so the expansion animation settles before capture.
	const int frames_warmup = 240;
	for (int i = 0; i < frames_warmup; i++)
	{
		OpenGL.clearBuffers();
		myHyperCube->render();
		OpenGL.update();
	}

	int w = SCR_WIDTH, h = SCR_HEIGHT;
	std::vector<unsigned char> pixels(w * h * 3);
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

	FILE* f = std::fopen(path, "wb");
	if (!f) { std::fprintf(stderr, "screenshot: cannot open %s\n", path); return; }
	std::fprintf(f, "P6\n%d %d\n255\n", w, h);
	// Flip vertically (OpenGL origin is bottom-left, PPM is top-left)
	for (int y = h - 1; y >= 0; y--)
		std::fwrite(pixels.data() + y * w * 3, 1, w * 3, f);
	std::fclose(f);
	std::fprintf(stderr, "screenshot: wrote %s (%dx%d)\n", path, w, h);
}

int main(int argc, char** argv)
{
	myHyperCube = new HyperCube(center, diameter);

	if (argc >= 3 && std::strcmp(argv[1], "--screenshot") == 0)
	{
		dump_screenshot(argv[2]);
		return 0;
	}

	menu();

	while (OpenGL.isOpen())
	{
		OpenGL.clearBuffers();

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

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
		myHyperCube->enable();
		myHyperCube->set_expanding();
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		myHyperCube->scramble();
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
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);

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

	if (process_Camera)
	{
		camera->ProcessMouseMovement(xoffset, yoffset);
		//cout << "x: " << xoffset << " y: " << yoffset << '\n';
	}
	//else
		//camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(static_cast<float>(yoffset));
}