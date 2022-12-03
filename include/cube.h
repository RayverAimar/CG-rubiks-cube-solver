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

	/* Getters */

	Point get_center();

	std::vector<Square*> squares;
	
private:
	Shader cube_colors;
};

Cube::Cube()
{
}

Cube::Cube(const Point& center, const float& separation)
{
	cube_colors = Shader(VERTEX_SHADER_PATH, CUBE_FRAGMENT_SHADER_PATH);
	
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

void Cube::render()
{
	cube_colors.use();
	cube_colors.classical_movement();

	cube_colors.setVec4Color("ourColor", GREEN_COLOR);

	this->squares[0]->render();
	
	cube_colors.setVec4Color("ourColor", BLUE_COLOR);
	
	this->squares[5]->render();

	cube_colors.setVec4Color("ourColor", YELLOW_COLOR);

	this->squares[1]->render();
	
	cube_colors.setVec4Color("ourColor", BLACK_COLOR);

	this->squares[4]->render();

	cube_colors.setVec4Color("ourColor", RED_COLOR);

	this->squares[2]->render();
	
	cube_colors.setVec4Color("ourColor", WHITE_COLOR);

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
