#include "./include/open_gl_loader.h"
#include "./include/shader.h"
#include "./include/square.h"

using namespace std;

float separation = 0.19f;

Point center(0.0f, 0.0f, 0.0f);
Point center2(0.4f, 0.0f, 0.0f);
Point center3(-0.4f, 0.0f, 0.0f);

Point center4(0.0f, 0.4f, 0.0f);
Point center5(0.4f, 0.4f, 0.0f);
Point center6(-0.4f, 0.4f, 0.0f);

Point center7(0.0f, -0.4f, 0.0f);
Point center8(0.4f, -0.4f, 0.0f);
Point center9(-0.4f, -0.4f, 0.0f);


#define Z_ANGLE 180.0f

std::vector<std::vector<float>> transformation_matrix = {	{1.01f, 0.00f, 0.00f, 0.00f },
															{0.00f, 1.01f, 0.00f, 0.00f },
															{0.00f, 0.00f, 1.00f, 0.00f },
															{0.00f, 0.00f, 0.00f, 1.00f } };

int main()
{
	OpenGlLoader OpenGL(SCR_WIDTH, SCR_HEIGHT);
	Shader current_shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

	std::vector<Square*> mySquares(9);

	mySquares[0] = new Square(center, separation);
	mySquares[1] = new Square(center2, separation);
	mySquares[2] = new Square(center3, separation);

	mySquares[3] = new Square(center4, separation);
	mySquares[4] = new Square(center5, separation);
	mySquares[5] = new Square(center6, separation);

	mySquares[6] = new Square(center7, separation);
	mySquares[7] = new Square(center8, separation);
	mySquares[8] = new Square(center9, separation);

	Matrix4D transformation(1.0f);
	//transformation.rotate(0.09f, Z_AXIS);
	transformation.translate(0.01f, 0.01f, 0.0f);

	mySquares[0]->print();
	std::cout << "*********TRANSFORMATION**********" << std::endl;
	mySquares[0]->transform(transformation);
	mySquares[0]->print();

	while (OpenGL.isOpen())
	{
		OpenGL.clearBuffers();

		current_shader.use();

		mySquares[0]->transform(transformation);
		mySquares[0]->render();

		OpenGL.update();
	}

	return 0;
}