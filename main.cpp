#include "./include/open_gl_loader.h"
#include "./include/shader.h"
#include "./include/square.h"

using namespace std;

Point center(0.0f, 0.0f, 0.0f);

int main()
{
	OpenGlLoader OpenGL(SCR_WIDTH, SCR_HEIGHT);
	Shader current_shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

	Square mySquare(center, 0.2f);

	mySquare.print();

	while (OpenGL.isOpen())
	{
		OpenGL.clearBuffers();

		current_shader.use();

		glBindVertexArray(mySquare.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		OpenGL.update();
	}

	return 0;
}