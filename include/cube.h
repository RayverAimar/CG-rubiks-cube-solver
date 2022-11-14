#ifndef __CUBE_H__
#define __CUBE_H__

#include "./square.h"
#include "./include/shader.h"

class Cube
{
public:

	/* Constructors & Destructors */

	Cube();
	Cube(const Point&, const float&);
	~Cube();

	/* Auxiliar Methods */

	void setUp();
	void render();
	void transform(const Matrix4D&);
	void set_camera(Camera);

	/* Getters */

	Point get_center();

	std::vector<Square*> squares;
	
private:
	Shader green_shader, red_shader, yellow_shader, white_shader, blue_shader, black_shader;
};

Cube::Cube()
{
}

Cube::Cube(const Point& center, const float& separation)
{
	green_shader	= Shader(VERTEX_SHADER_PATH, GREEN_FRAGMENT_SHADER_PATH);
	red_shader		= Shader(VERTEX_SHADER_PATH, RED_FRAGMENT_SHADER_PATH);
	yellow_shader	= Shader(VERTEX_SHADER_PATH, YELLOW_FRAGMENT_SHADER_PATH);
	white_shader	= Shader(VERTEX_SHADER_PATH, WHITE_FRAGMENT_SHADER_PATH);
	blue_shader		= Shader(VERTEX_SHADER_PATH, BLUE_FRAGMENT_SHADER_PATH);
	black_shader	= Shader(VERTEX_SHADER_PATH, BLACK_FRAGMENT_SHADER_PATH);
	
	std::vector<Point> centers(6);

	centers[0] = Point(center.x, center.y, center.z);								/*	Front Face	*/
	centers[5] = Point(center.x, center.y, center.z + (separation * 2));			/*	Back Face	*/

	centers[1] = Point(center.x, center.y + separation, center.z + separation);		/*	Top Face	*/
	centers[4] = Point(center.x, center.y - separation, center.z + separation);		/*	Bottom Face	*/

	centers[2] = Point(center.x + separation, center.y, center.z + separation);		/*	Right Face	*/
	centers[3] = Point(center.x - separation, center.y, center.z + separation);		/*	Left Face	*/

	squares = std::vector<Square*>(6);

	squares[0] = new Square(centers[0], separation, Z_AXIS);
	squares[5] = new Square(centers[5], separation, Z_AXIS);

	squares[1] = new Square(centers[1], separation, Y_AXIS);
	squares[4] = new Square(centers[4], separation, Y_AXIS);

	squares[2] = new Square(centers[2], separation, X_AXIS);
	squares[3] = new Square(centers[3], separation, X_AXIS);

	setUp();

}

Cube::~Cube()
{
	for (int i = 0; i < squares.size(); i++)
	{
		delete squares[i];
	}
}

void Cube::setUp()
{
	for (size_t i = 0; i < squares.size(); i++)
	{
		squares[i]->setUp();
	}
}

void Cube::set_camera(Camera camera)
{
	green_shader.use();
	green_shader.set_camera(camera);

	yellow_shader.use();
	yellow_shader.set_camera(camera);

	blue_shader.use();
	blue_shader.set_camera(camera);

	white_shader.use();
	white_shader.set_camera(camera);

	red_shader.use();
	red_shader.set_camera(camera);

	black_shader.use();
	black_shader.set_camera(camera);
}

void Cube::render()
{

	green_shader.use();
	green_shader.classical_movement();

	this->squares[0]->render();
	
	blue_shader.use();
	blue_shader.classical_movement();
	
	this->squares[5]->render();

	yellow_shader.use();
	yellow_shader.classical_movement();

	this->squares[1]->render();
	
	black_shader.use();
	black_shader.classical_movement();

	this->squares[4]->render();

	red_shader.use();
	red_shader.classical_movement();

	this->squares[2]->render();
	
	white_shader.use();
	white_shader.classical_movement();

	this->squares[3]->render();
}

void Cube::transform(const Matrix4D& transformation)
{
	for (size_t i = 0; i < squares.size(); i++)
	{
		squares[i]->transform(transformation);
	}
}

Point Cube::get_center()
{
	Point first_center = squares[0]->get_center();
	Point second_center = squares[5]->get_center();

	first_center /= 2, second_center /= 2;
	first_center += second_center;
	return first_center;
}

#endif // !__CUBE_H__
