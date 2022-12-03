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
	void solve_Rubiks();

	void set_expanding();
	void set_solving();
	void set_timer(const int&);
	void scramble();
	void set_speed(const float&);
	void disable();
	void read_moves(const std::string&);

	Rubik** cur_cube = nullptr;
	std::vector<Rubik*> Rubiks;
	std::vector<Rubik**> Frontal_Litter, Back_Litter, Up_Litter, Down_Litter, Left_Litter, Right_Litter;
	std::queue<char> moves;
	std::string to_scramble, to_solve;
	bool f = false, fPrime = false, d = false, dPrime = false, u = false, uPrime = false, b = false, bPrime = false;
	bool r = false, rPrime = false, l = false, lPrime = false;

	bool solving = false;

private:
	int timer = 0;
	float chunk = 0;
	bool start_new_movement;


	Point get_center();

	void look_for_movement();
	void stop_current_movement();
	void expand();
	void retreat();
	void solve();

	void rotate_litter(const std::vector<Rubik**>&, const unsigned int&, const bool&);
	void reassign_pointers(const std::vector<Rubik**>&, const unsigned int*);
	void set_next_movement(char);

	void F();
	void D();
	void U();
	void B();
	void R();
	void L();
	
	void FPrime();
	void DPrime();
	void UPrime();
	void BPrime();
	void RPrime();
	void LPrime();

	void correct_orientation(const std::vector<Rubik**>&, const unsigned int&, const unsigned int*);

	int cur_cube_index;
	bool enable_movement = false, expanding = false, retreating = false, totally_scrambled = true;
	bool scrambling = false, scrambled = false, solved = true, solution_entered = false;
};

HyperCube::HyperCube() : cur_cube(nullptr), cur_cube_index(0), timer(0)
{
}

HyperCube::HyperCube(const Point& center, float diameter) : cur_cube(nullptr), cur_cube_index(0), timer(0)
{
	float separation = 0.19f;
	float chunk = (diameter / 2) - (diameter / 20);

	Point center1(center.x - (diameter * 3),	center.y - (diameter * 3),	center.z);
	Point center2(center.x,						center.y - (diameter * 3),	center.z);
	Point center3(center.x + (diameter * 3),	center.y - (diameter * 3),	center.z);
	Point center4(center.x - (diameter * 3),	center.y,					center.z);
	Point center5(center.x,						center.y,					center.z);
	Point center6(center.x + (diameter * 3),	center.y,					center.z);
	Point center7(center.x - (diameter * 3),	center.y + (diameter * 3),	center.z);
	Point center8(center.x,						center.y + (diameter * 3),	center.z);
	Point center9(center.x + (diameter * 3),	center.y + (diameter * 3),	center.z);

	Point center10(center.x - (diameter * 3),	center.y - (diameter * 3),	center.z + (diameter * 3));
	Point center11(center.x,					center.y - (diameter * 3),	center.z + (diameter * 3));
	Point center12(center.x + (diameter * 3),	center.y - (diameter * 3),	center.z + (diameter * 3));
	Point center13(center.x - (diameter * 3),	center.y,					center.z + (diameter * 3));
	Point center14(center.x,					center.y,					center.z + (diameter * 3));
	Point center15(center.x + (diameter * 3),	center.y,					center.z + (diameter * 3));
	Point center16(center.x - (diameter * 3),	center.y + (diameter * 3),	center.z + (diameter * 3));
	Point center17(center.x,					center.y + (diameter * 3),	center.z + (diameter * 3));
	Point center18(center.x + (diameter * 3),	center.y + (diameter * 3),	center.z + (diameter * 3));

	Point center19(center.x - (diameter * 3),	center.y - (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center20(center.x,					center.y - (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center21(center.x + (diameter * 3),	center.y - (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center22(center.x - (diameter * 3),	center.y,					center.z + (diameter * 3 * 2));
	Point center23(center.x,					center.y,					center.z + (diameter * 3 * 2));
	Point center24(center.x + (diameter * 3),	center.y,					center.z + (diameter * 3 * 2));
	Point center25(center.x - (diameter * 3),	center.y + (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center26(center.x,					center.y + (diameter * 3),	center.z + (diameter * 3 * 2));
	Point center27(center.x + (diameter * 3),	center.y + (diameter * 3),	center.z + (diameter * 3 * 2));

	std::vector<Point> centers = { center1, center2, center3, center4, center5, center6, center7, center8, center9,
									center10, center11, center12, center13, center14, center15, center16, center17, center18,
									center19, center20, center21, center22, center23, center24, center25, center26, center27
	};

	for (int i = 0; i < centers.size(); i++)
	{
		Rubik* temp_rubik = new Rubik(centers[i], diameter - (diameter/20));
		Rubiks.push_back(temp_rubik);
	}

	for (int i = 0; i < 9; i++)
	{
		Frontal_Litter.push_back(&Rubiks[frontal_litter_idx[i]]);
		Back_Litter.push_back(&Rubiks[back_litter_idx[i]]);
		Up_Litter.push_back(&Rubiks[up_litter_idx[i]]);
		Down_Litter.push_back(&Rubiks[down_litter_idx[i]]);
		Left_Litter.push_back(&Rubiks[left_litter_idx[i]]);
		Right_Litter.push_back(&Rubiks[right_litter_idx[i]]);
	}


	cur_cube = &Rubiks[14];

}

HyperCube::~HyperCube()
{

}

void HyperCube::scramble()
{
	int n_moves = rand() % 30 + 10;
	for (int i = 0; i < n_moves; i++)
	{
		int movement_idx = rand() % 6;
		this->to_scramble.push_back(valid_moves[movement_idx]);
	}
	//this->to_scramble = "DL";
	std::cout << this->to_scramble << std::endl;
	this->scrambling = true;
	this->read_moves(this->to_scramble);
	this->set_speed(3.0f);
	this->enable();
}

void HyperCube::solve()
{
	if (this->to_scramble.empty()) return;
	this->to_solve	= format_solution(get_solution(to_cube_not(string_to_vector(this->to_scramble))));
	this->read_moves(this->to_solve);
	this->enable();
	solution_entered = true;
}

void HyperCube::set_speed(const float& _chunk)
{
	this->chunk = _chunk;
}

void HyperCube::disable()
{
	enable_movement = start_new_movement = false;
	if (scrambling)
	{
		this->scrambled = true;
		this->scrambling = false;
	}
	if (solution_entered)
	{
		this->solved = true;
		this->solution_entered = false;
		this->scrambled = false;
	}
}

void HyperCube::set_expanding()
{
	expanding = true;
	this->enable_movement = true;
	this->timer = 50;
}

void HyperCube::read_moves(const std::string& to_read)
{
	for (int i = 0; i < to_read.size(); i++)
	{
		moves.push(to_read[i]);
	}
}

void HyperCube::set_next_movement(char cur_movement)
{
	timer = (int)((90.0f / chunk) - 2);
	start_new_movement = false;
	switch(cur_movement)
	{
		case F_MOVEMENT:
			f = true;
			break;
		case F_PRIME_MOVEMENT:
			fPrime = true;
			break;
		case D_MOVEMENT:
			d = true;
			break;
		case D_PRIME_MOVEMENT:
			dPrime = true;
			break;
		case U_MOVEMENT:
			u = true;
			break;
		case U_PRIME_MOVEMENT:
			uPrime = true;
			break;
		case B_MOVEMENT:
			b = true;
			break;
		case B_PRIME_MOVEMENT:
			bPrime = true;
			break;
		case R_MOVEMENT:
			r = true;
			break;
		case R_PRIME_MOVEMENT:
			rPrime = true;
			break;
		case L_MOVEMENT:
			l = true;
			break;
		case L_PRIME_MOVEMENT:
			lPrime = true;
			break;
		default:
			break;
	}
}

void HyperCube::set_solving()
{
	solving = true;
}

void HyperCube::correct_orientation(const std::vector<Rubik**> &cur_litter, const unsigned int &axis, const unsigned int* pattern)
{
	for (int i = 0; i < cur_litter.size(); i++)
	{
		if (axis == X_AXIS)
		{
			(*cur_litter[i])->rotation_reassign((*cur_litter[i])->x_view, pattern);
		}
		else if (axis == Y_AXIS)
		{
			(*cur_litter[i])->rotation_reassign((*cur_litter[i])->y_view, pattern);
		}
		else
		{
			(*cur_litter[i])->rotation_reassign((*cur_litter[i])->z_view, pattern);
		}
	}
}

void HyperCube::stop_current_movement()
{
	if (f) {
		correct_orientation(Frontal_Litter, X_AXIS, non_clockwise_rotation_idx);
		reassign_pointers(Frontal_Litter, non_prime_pattern);
	}
	else if (fPrime)
	{
		correct_orientation(Frontal_Litter, X_AXIS, clockwise_rotation_idx);
		reassign_pointers(Frontal_Litter, prime_pattern);
	}
	else if (d)
	{
		correct_orientation(Down_Litter, Y_AXIS, non_clockwise_rotation_idx);
		reassign_pointers(Down_Litter, non_prime_pattern);
	}
	else if (dPrime)
	{
		correct_orientation(Down_Litter, Y_AXIS, clockwise_rotation_idx);
		reassign_pointers(Down_Litter, prime_pattern);
	}
	else if (u)
	{
		correct_orientation(Up_Litter, Y_AXIS, clockwise_rotation_idx);
		reassign_pointers(Up_Litter, non_prime_pattern);
	}
	else if (uPrime)
	{
		correct_orientation(Up_Litter, Y_AXIS, non_clockwise_rotation_idx);
		reassign_pointers(Up_Litter, prime_pattern);
	}
	else if (b)
	{
		correct_orientation(Back_Litter, X_AXIS, clockwise_rotation_idx);
		reassign_pointers(Back_Litter, non_prime_pattern);
	}
	else if (bPrime)
	{
		correct_orientation(Back_Litter, X_AXIS, non_clockwise_rotation_idx);
		reassign_pointers(Back_Litter, prime_pattern);
	}
	else if (r)
	{
		correct_orientation(Right_Litter, Z_AXIS, clockwise_rotation_idx);
		reassign_pointers(Right_Litter, non_prime_pattern);
	}
	else if (rPrime)
	{
		correct_orientation(Right_Litter, Z_AXIS, non_clockwise_rotation_idx);
		reassign_pointers(Right_Litter, prime_pattern);
	}
	else if (l)
	{
		correct_orientation(Left_Litter, Z_AXIS, non_clockwise_rotation_idx);
		reassign_pointers(Left_Litter, non_prime_pattern);
	}
	else if (lPrime)
	{
		correct_orientation(Left_Litter, Z_AXIS, clockwise_rotation_idx);
		reassign_pointers(Left_Litter, prime_pattern);
	}
	else if (expanding)
	{
		expanding = retreating = enable_movement = false;
		for (int i = 0; i < Rubiks.size(); i++)
		{
			Rubiks[i]->scramble();
		}
		totally_scrambled = false;
	}
	f = fPrime = d = dPrime = u = uPrime = b = bPrime = r = rPrime = l = lPrime = false;
	if (moves.empty()) disable();
	else enable();
}

void HyperCube::set_timer(const int& _timer)
{
	this->timer = _timer;
}

void HyperCube::solve_Rubiks()
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
	if (!moves.empty() && start_new_movement)
	{
		char next_movement = this->moves.front();
		this->moves.pop();
		this->set_next_movement(next_movement);
	}
	if (f)				F();
	else if (fPrime)	FPrime();
	else if (b)			B();
	else if (bPrime)	BPrime();

	else if (u)			U();
	else if (uPrime)	UPrime();

	else if (d)			D();
	else if (dPrime)	DPrime();

	else if (l)			L();
	else if (lPrime)	LPrime();

	else if (r)			R();
	else if (rPrime)	RPrime();
	else if (expanding) expand();

}

void HyperCube::enable()
{
	enable_movement = start_new_movement = true;
	this->timer = (int)((90.0f/chunk) - 2);
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
	if (all_solved)
	{
		solving = false;
		this->solve();
	}
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
			this->solve_Rubiks();
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

void HyperCube::rotate_litter(const std::vector<Rubik**>& cur_litter, const unsigned int& axis, const bool& clockwise)
{
	int direction = clockwise ? 1 : -1;
	Point cur_center = (*cur_litter[4])->get_center();
	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk * direction, axis);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < cur_litter.size(); i++)
	{
		(*cur_litter[i])->transform(transform);
	}
}

void HyperCube::reassign_pointers(const std::vector<Rubik**>& cur_litter, const unsigned int* pattern)
{
	std::vector<Rubik*> new_litter;
	for (int i = 0; i < cur_litter.size(); i++)
	{
		new_litter.push_back(*cur_litter[i]);
	}
	for (int i = 0; i < cur_litter.size(); i++)
	{
		*cur_litter[i] = new_litter[pattern[i]];
	}
}

void HyperCube::F()
{
	rotate_litter(Frontal_Litter, Z_AXIS, true);
}

void HyperCube::FPrime()
{
	rotate_litter(Frontal_Litter, Z_AXIS, false);
}

void HyperCube::D()
{
	rotate_litter(Down_Litter, Y_AXIS, true);
}

void HyperCube::DPrime()
{
	rotate_litter(Down_Litter, Y_AXIS, false);
}

void HyperCube::B()
{
	rotate_litter(Back_Litter, Z_AXIS, false);
}

void HyperCube::BPrime()
{
	rotate_litter(Back_Litter, Z_AXIS, true);
}

void HyperCube::U()
{
	rotate_litter(Up_Litter, Y_AXIS, false);
}

void HyperCube::UPrime()
{
	rotate_litter(Up_Litter, Y_AXIS, true);
}

void HyperCube::L()
{
	rotate_litter(Left_Litter, X_AXIS, false);
}

void HyperCube::LPrime()
{
	rotate_litter(Left_Litter, X_AXIS, true);
}

void HyperCube::R()
{
	rotate_litter(Right_Litter, X_AXIS, true);
}

void HyperCube::RPrime()
{
	rotate_litter(Right_Litter, X_AXIS, false);
}




#endif // !__HYPER_CUBE_H__
