#ifndef __HYPER_CUBE_H__

#include "rubik.h"

class HyperCube
{
public:
	HyperCube();
	HyperCube(const Point&, float);
	~HyperCube();

	void render();
	void enable();
	void next();
	void solve();

	void set_expanding();
	void set_solving();

	Rubik** cur_cube = nullptr;
	std::vector<Rubik*> Rubiks;

	bool solving = false;

private:
	
	Point get_center();

	void look_for_movement();
	void stop_current_movement();
	void disable();
	void expand();
	void retreat();

	int cur_cube_index, timer;
	bool enable_movement = false, expanding = false, retreating = false, totally_scrambled = true;
};

HyperCube::HyperCube() : cur_cube(nullptr), cur_cube_index(0), timer(0)
{
}

HyperCube::HyperCube(const Point& center, float diameter) : cur_cube(nullptr), cur_cube_index(0), timer(0)
{
	float separation = 0.19f;
	float chunk = (diameter / 2) - (diameter / 20);

	Point center1(center.x + (diameter * 3),	center.y - (diameter * 3),	center.z);
	Point center2(center.x,						center.y - (diameter * 3),	center.z);
	Point center3(center.x - (diameter * 3),	center.y - (diameter * 3),	center.z);
	Point center4(center.x + (diameter * 3),	center.y,					center.z);
	Point center5(center.x,						center.y,					center.z);
	Point center6(center.x - (diameter * 3),	center.y,					center.z);
	Point center7(center.x + (diameter * 3),	center.y + (diameter * 3),	center.z);
	Point center8(center.x,						center.y + (diameter * 3),	center.z);
	Point center9(center.x - (diameter * 3),	center.y + (diameter * 3),	center.z);

	Point center10(center.x + (diameter * 3),	center.y - (diameter * 3),	center.z + (diameter * 3));
	Point center11(center.x,					center.y - (diameter * 3),	center.z + (diameter * 3));
	Point center12(center.x - (diameter * 3),	center.y - (diameter * 3),	center.z + (diameter * 3));
	Point center13(center.x + (diameter * 3),	center.y,					center.z + (diameter * 3));
	Point center14(center.x,					center.y,					center.z + (diameter * 3));
	Point center15(center.x - (diameter * 3),	center.y,					center.z + (diameter * 3));
	Point center16(center.x + (diameter * 3),	center.y + (diameter * 3),	center.z + (diameter * 3));
	Point center17(center.x,					center.y + (diameter * 3),	center.z + (diameter * 3));
	Point center18(center.x - (diameter * 3),	center.y + (diameter * 3),	center.z + (diameter * 3));

	Point center19(center.x + (diameter * 3),	center.y - (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center20(center.x,					center.y - (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center21(center.x - (diameter * 3),	center.y - (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center22(center.x + (diameter * 3),	center.y,					center.z + (diameter * 3 * 2));
	Point center23(center.x,					center.y,					center.z + (diameter * 3 * 2));
	Point center24(center.x - (diameter * 3),	center.y,					center.z + (diameter * 3 * 2));
	Point center25(center.x + (diameter * 3),	center.y + (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center26(center.x,					center.y + (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center27(center.x - (diameter * 3),	center.y + (diameter * 3),	center.z + (diameter * 3 * 2));

	std::vector<Point> centers = { center1, center2, center3, center4, center5, center6, center7, center8, center9,
									center10, center11, center12, center13, center14, center15, center16, center17, center18,
									center19, center20, center21, center22, center23, center24, center25, center26, center27
	};

	for (int i = 0; i < centers.size(); i++)
	{
		Rubik* temp_rubik = new Rubik(centers[i], diameter - (diameter/20));
		Rubiks.push_back(temp_rubik);
	}

	cur_cube = &Rubiks[14];

}

HyperCube::~HyperCube()
{

}

void HyperCube::disable()
{

}

void HyperCube::set_expanding()
{
	expanding = true;
}

void HyperCube::set_solving()
{
	solving = true;
}

void HyperCube::stop_current_movement()
{
	if (expanding)
	{
		expanding = retreating = enable_movement = false;
		for (int i = 0; i < Rubiks.size(); i++)
		{
			Rubiks[i]->scramble();
		}
		totally_scrambled = false;
	}
}

void HyperCube::solve()
{
	this->solving = true;
	for (int i = 0; i < Rubiks.size(); i++)
	{
		Rubiks[i]->solved = false;
		Rubiks[i]->solve();
	}
}

void HyperCube::look_for_movement()
{
	if (!enable_movement) return;
	if (this->timer-- < 0)
	{
		stop_current_movement();
		return;
	}
	if (expanding) expand();
}

void HyperCube::enable()
{
	enable_movement = true;
	this->timer = 50;
}

void HyperCube::expand()
{
	for (int i = 0; i < Rubiks.size(); i++)
	{
		Matrix4D transform(1.0f);
		Vector3D dir = Rubiks[i]->get_center() - this->get_center();
		dir.direction /= 100;
		transform.translate(dir.direction);
		Rubiks[i]->move(transform);
	}
}

void HyperCube::retreat()
{
	bool all_solved = true;
	for (int i = 0; i < Rubiks.size(); i++)
	{
		if (!Rubiks[i]->is_solved())
		{
			all_solved = false;
			continue;
		}
		if (Rubiks[i]->stopped)
		{
			std::cout << "Rubiks[" << i << "] started retreating" << std::endl;
			Matrix4D transform(1.0f);
			Vector3D dir = this->get_center() - Rubiks[i]->get_center();
			dir.direction /= 100;
			transform.translate(dir.direction);
			Rubiks[i]->to_retreat = transform;
			Rubiks[i]->retreating = true;
			Rubiks[i]->enable();
			Rubiks[i]->set_timer(35);
			Rubiks[i]->stopped = false;
		}
	}
	if (all_solved) solving = false;
}

void HyperCube::render()
{
	look_for_movement();
	if (solving) retreat();

	
	for (int i = 0; i < Rubiks.size(); i++)
	{
		Rubiks[i]->render();
	}

	if (!totally_scrambled)
	{
		bool all_scrambled = true;

		for (int i = 0; i < Rubiks.size(); i++)
		{
			if (!Rubiks[i]->scrambled)
			{
				all_scrambled = false;
			}
		}
		if (all_scrambled)
		{
			std::cout << "All Scrambled!" << std::endl;
			totally_scrambled = true;
			this->solve();
		}
	}
}

void HyperCube::next()
{
	this->cur_cube_index++;
	cur_cube_index %= Rubiks.size();
	cur_cube = &Rubiks[cur_cube_index];
}

Point HyperCube::get_center()
{
	return Rubiks[13]->get_center();
}

#endif // !__HYPER_CUBE_H__
