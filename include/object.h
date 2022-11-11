#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>

#include "math.h"

class Object
{
public:
	
	/* Constructors */
	Object();
	~Object();

	/* Getters */

	std::vector<Point> get_vertices();
	size_t size();
	Point& front();

	/* Auxiliar methods */
	void print();
	void push(const Point&);
	void move(const Vector3D&);
	void transform(const Matrix4D&);

	std::vector<unsigned int> indices;
	std::vector<float> textureCoords;

private:

	std::vector<Point> vertices;

};

Object::Object()
{
}

Object::~Object()
{
}

std::vector<Point> Object::get_vertices()
{
	return this->vertices;
}

size_t Object::size()
{
	return this->vertices.size();
}

Point& Object::front()
{
	return this->vertices.front();
}

void Object::print()
{
	for (size_t i = 0; i < this->size(); i++)
	{
		this->vertices[i].print();
	}
}

void Object::push(const Point& to_push)
{
	this->vertices.emplace_back(to_push);
}

void Object::move(const Vector3D& direction)
{
	for (size_t i = 0; i < this->size(); i++)
	{
		vertices[i] += direction;
	}
}

void Object::transform(const Matrix4D& transformation)
{
	for (int i = 0; i < size(); i++)
	{
		vertices[i] = transformation * vertices[i];
	}
}

#endif // !__OBJECT_H__
