#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "./object.h"
#include "./utils.h"
#include "./directories.h"

class Square : public Object
{
public:
	
	/* Constructors & Destructors */
	Square();
	Square(const Point&, float, const unsigned int& = Z_AXIS);
	~Square();

	/* Auxiliar Methods */

	void setUp();
	void render();
	void update();
	
	/* Getters */
	
	Point get_center();

	unsigned int VAO, VBO[2], EBO; /* (VBO[0]->vertices) | (VBO[1]->textures) */ 

private:

};

Square::Square()
{
	VAO = EBO = VBO[0] = VBO[1] = 0;
}

Square::Square(const Point& center, float separation, const unsigned int& axis)
{

	Point top_right(center), top_left(center), down_right(center), down_left(center);
	Vector3D top_right_direction, top_left_direction, down_right_direction, down_left_direction;

	if (axis == X_AXIS)
	{
		top_right_direction = Vector3D(0.0f, separation, separation), top_left_direction = Vector3D(0.0f, -separation, separation),
		down_right_direction = Vector3D(0.0f, separation, -separation), down_left_direction = Vector3D(0.0f, -separation, -separation);
	}

	else if (axis == Y_AXIS)
	{
		top_right_direction = Vector3D(separation, 0.0f, separation), top_left_direction = Vector3D(-separation, 0.0f, separation),
		down_right_direction = Vector3D(separation, 0.0f, -separation), down_left_direction = Vector3D(-separation, 0.0f, -separation);
	}

	else if (axis == Z_AXIS)
	{
		top_right_direction = Vector3D(separation, separation, 0.0f), top_left_direction = Vector3D(-separation, separation, 0.0f),
		down_right_direction = Vector3D(separation, -separation, 0.0f), down_left_direction = Vector3D(-separation, -separation, 0.0f);
	}

	top_right += top_right_direction;
	top_left += top_left_direction;
	down_right += down_right_direction;
	down_left += down_left_direction;

	push(top_left);
	push(top_right);
	push(down_right);
	push(down_left);

	this->indices = { 0, 1, 2, 2, 3, 0 };
	this->textureCoords = { 0.0f, 1.0f,
							1.0f, 1.0f,
							1.0f, 0.0f,
							1.0f, 0.0f,
							0.0f, 0.0f,
							0.0f, 1.0f	};

	setUp();
}

Square::~Square()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(2, this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void Square::setUp()
{
	/* Buffer Generators */
	
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO[0]);
	glGenBuffers(1, &this->EBO);

	/* Setting Up Buffers*/

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]); /* Vertices */
	glBufferData(GL_ARRAY_BUFFER, this->size() * sizeof(this->front()), &this->front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
	glEnableVertexAttribArray(0);

	/* Bind Texture (missing) */
	
	/* Binding Element Buffer Object */

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(this->indices.front()), &this->indices.front(), GL_STATIC_DRAW);

	/* Unbinding Buffers */

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Square::render()
{
	this->update();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Square::update()
{
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, this->size() * sizeof(this->front()), &this->front(), GL_STATIC_DRAW);
}

Point Square::get_center()
{
	Point one = vertices[0] + vertices[1];
	Point two = vertices[2] + vertices[3];
	one /= 4, two /= 4;
	one += two;
	return one;
}

#endif // !__SQUARE_H__
