#ifndef __RUBIK_H__
#define __RUBIK_H__

#include <queue>
#include <stdlib.h>
#include <time.h>
#include "./cube.h"
#include "./solver/solve.h"
#include "./solver/random.h"

class Rubik
{
public:
	
	/* Constructors & Destructors */

	Rubik();
	Rubik(const Point&, const float&);
	~Rubik();

	/* Auxiliar Methods */

	void render();
	void move(const Matrix4D&);
	void enable();
	void set_timer(const int&);
	void set_speed(const float&);
	void read_moves(const std::string&);
	void disable();
	void append(const char&);
	void append(const std::string&);
	bool in_movement();
	bool is_solved();
	void solve();
	void scramble();
	void transform(const Matrix4D&);

	void rotation_reassign(const std::vector<Cube**>&, const unsigned int*);

	/* Getters */

	Point get_center();
	
	/* Variables */

	std::vector<Cube*> Cubes;
	std::vector<Cube**> Frontal_Litter, Back_Litter, Up_Litter, Down_Litter, Left_Litter, Right_Litter, x_view, y_view, z_view;
	std::queue<char> moves;
	std::string to_scramble, to_solve;
	bool f = false, fPrime = false, d = false, dPrime = false, u = false, uPrime = false, b = false, bPrime = false;
	bool r = false, rPrime = false, l = false, lPrime = false, retreating = false, solved = true, stopped = true;
	bool solution_entered = false, scrambling = false, scrambled = false;

	Matrix4D to_retreat;
private:
	int timer, n_moves = 0;
	bool enable_movement, start_new_movement;
	float chunk;
	
	/* Movements Methods */

	void set_next_movement(char);
	void look_for_movement();
	void stop_current_movement();
	void rotate_litter(const std::vector<Cube**>&, const unsigned int&, const bool&);
	void reassign_pointers(const std::vector<Cube**>&, const unsigned int*);

	/* Classic Movements */

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
	
	void retreat();

};

Rubik::Rubik() : timer(0), enable_movement(false), start_new_movement(false), chunk(0.75f)
{
}

Rubik::Rubik(const Point& center, const float& separation) : timer(0), enable_movement(false), start_new_movement(false), chunk(0.75f)
{
	Point frontal_litter_center_1(center.x - separation,	center.y - separation,		center.z);						/* Bottom Litter 0 */		/* Left Litter 0  */	
	Point frontal_litter_center_2(center.x,					center.y - separation,		center.z);						/* Bottom Litter 1 */														/* M Litter 1  */
	Point frontal_litter_center_3(center.x + separation,	center.y - separation,		center.z);						/* Bottom Litter 2 */								/* Right Litter 02 */	
	Point frontal_litter_center_4(center.x - separation,	center.y,					center.z);													/* Left Litter 3  */												/* E Litter 3  */
	Point frontal_litter_center_5(center.x,					center.y,					center.z);																									/* M Litter 4  */	/* E Litter 4  */
	Point frontal_litter_center_6(center.x + separation,	center.y,					center.z);																			/* Right Litter 05 */						/* E Litter 5  */
	Point frontal_litter_center_7(center.x - separation,	center.y + separation,		center.z);						/* Upper Litter 6 */		/* Left Litter 6  */								
	Point frontal_litter_center_8(center.x,					center.y + separation,		center.z);						/* Upper Litter 7 */														/* M Litter 7  */
	Point frontal_litter_center_9(center.x + separation,	center.y + separation,		center.z);						/* Upper Litter 8 */								/* Right Litter 08 */

	Point middle_litter_center_1(center.x - separation,		center.y - separation,		center.z + separation);			/* Bottom Litter 9 */		/* Left Litter 9  */
	Point middle_litter_center_2(center.x,					center.y - separation,		center.z + separation);			/* Bottom Litter 10 */														/* M Litter 10 */
	Point middle_litter_center_3(center.x + separation,		center.y - separation,		center.z + separation);			/* Bottom Litter 11 */								/* Right Litter 11 */
	Point middle_litter_center_4(center.x - separation,		center.y,					center.z + separation);										/* Left Litter 12 */												/* E Litter 12 */
	Point middle_litter_center_5(center.x,					center.y,					center.z + separation);																						/* M Litter 13 */	/* E Litter 13 */
	Point middle_litter_center_6(center.x + separation,		center.y,					center.z + separation);																/* Right Litter 14 */						/* E Litter 14 */
	Point middle_litter_center_7(center.x - separation,		center.y + separation,		center.z + separation);			/* Upper Litter 15 */		/* Left Litter 15 */
	Point middle_litter_center_8(center.x,					center.y + separation,		center.z + separation);			/* Upper Litter 16 */														/* M Litter 16 */
	Point middle_litter_center_9(center.x + separation,		center.y + separation,		center.z + separation);			/* Upper Litter 17 */								/* Right Litter 17 */

	Point back_litter_center_1	(center.x - separation,		center.y - separation,		center.z + (separation * 2));	/* Bottom Litter 18 */		/* Left Litter 18 */
	Point back_litter_center_2	(center.x,					center.y - separation,		center.z + (separation * 2));	/* Bottom Litter 19 */														/* M Litter 19 */
	Point back_litter_center_3	(center.x + separation,		center.y - separation,		center.z + (separation * 2));	/* Bottom Litter 20 */								/* Right Litter 20 */
	Point back_litter_center_4	(center.x - separation,		center.y,					center.z + (separation * 2));								/* Left Litter 21 */												/* E Litter 21 */
	Point back_litter_center_5	(center.x,					center.y,					center.z + (separation * 2));																				/* M Litter 22 */	/* E Litter 22 */
	Point back_litter_center_6	(center.x + separation,		center.y,					center.z + (separation * 2));														/* Right Litter 23 */						/* E Litter 23 */
	Point back_litter_center_7	(center.x - separation,		center.y + separation,		center.z + (separation * 2));	/* Upper Litter 24 */		/* Left Litter 24 */
	Point back_litter_center_8	(center.x,					center.y + separation,		center.z + (separation * 2));	/* Upper Litter 25 */														/* M Litter 25 */
	Point back_litter_center_9	(center.x + separation,		center.y + separation,		center.z + (separation * 2));	/* Upper Litter 26 */								/* Right Litter 26 */

	std::vector<Point> centers = { frontal_litter_center_1, frontal_litter_center_2, frontal_litter_center_3, frontal_litter_center_4, frontal_litter_center_5, frontal_litter_center_6, frontal_litter_center_7, frontal_litter_center_8, frontal_litter_center_9,
									middle_litter_center_1, middle_litter_center_2, middle_litter_center_3, middle_litter_center_4, middle_litter_center_5, middle_litter_center_6, middle_litter_center_7, middle_litter_center_8, middle_litter_center_9,
									back_litter_center_1, back_litter_center_2, back_litter_center_3, back_litter_center_4, back_litter_center_5, back_litter_center_6, back_litter_center_7, back_litter_center_8, back_litter_center_9
	};

	for (int i = 0; i < centers.size(); i++)
	{
		Cube* temporal_cube = new Cube(centers[i], (separation / 2) - (separation / 20));
		Cubes.push_back(temporal_cube);
	}

	for (int i = 0; i < 9; i++)
	{
		Frontal_Litter.push_back(&Cubes[frontal_litter_idx[i]]);
		Back_Litter.push_back(&Cubes[back_litter_idx[i]]);
		Up_Litter.push_back(&Cubes[up_litter_idx[i]]);
		Down_Litter.push_back(&Cubes[down_litter_idx[i]]);
		Left_Litter.push_back(&Cubes[left_litter_idx[i]]);
		Right_Litter.push_back(&Cubes[right_litter_idx[i]]);
	}

	for (int i = 0; i < 27; i++)
	{
		x_view.push_back(&Cubes[x_view_idx[i]]);
		y_view.push_back(&Cubes[y_view_idx[i]]);
		z_view.push_back(&Cubes[z_view_idx[i]]);
	}

}

Rubik::~Rubik()
{
}

bool Rubik::is_solved()
{
	return this->solved;
}

void Rubik::rotation_reassign(const std::vector<Cube**>& cur_view, const unsigned int* pattern)
{
	std::vector<Cube*> new_cubes;

	for (int i = 0; i < cur_view.size(); i++)
	{
		new_cubes.push_back(*cur_view[i]);
	}

	for (int i = 0; i < cur_view.size(); i++)
	{
		*cur_view[i] = new_cubes[pattern[i]];
	}
}

void Rubik::solve()
{
	if (this->to_scramble.empty()) return;
	this->to_solve = format_solution(get_solution(to_cube_not(string_to_vector(this->to_scramble))));
	this->read_moves(this->to_solve);
	this->enable();
	solution_entered = true;
}

void Rubik::retreat()
{
	for (int i = 0; i < Cubes.size(); i++)
	{
		Cubes[i]->transform(to_retreat);
	}
}

void Rubik::transform(const Matrix4D& transformation)
{
	for (size_t i = 0; i < Cubes.size(); i++)
	{
		Cubes[i]->transform(transformation);
	}
}

void Rubik::scramble()
{
	int n_moves = rand() % 30 + 10;
	for (int i = 0; i < n_moves; i++)
	{
		int movement_idx = rand() % 6;
		this->to_scramble.push_back(valid_moves[movement_idx]);
	}
	std::cout << this->to_scramble << std::endl;
	this->scrambling = true;
	this->read_moves(this->to_scramble);
	this->set_speed(6.0f);
	this->enable();
}

void Rubik::read_moves(const std::string &to_read)
{
	for (int i = 0; i < to_read.size(); i++)
	{
		moves.push(to_read[i]);
	}
}

void Rubik::append(const char &movement)
{
	this->to_scramble.push_back(movement);
	std::cout << this->to_scramble << std::endl;
}

void Rubik::append(const std::string &movements)
{
	this->to_scramble.append(movements);
}

void Rubik::set_speed(const float& _chunk)
{
	chunk = _chunk;
}

void Rubik::set_next_movement(char cur_movement)
{
	timer = (int)((90.0f / chunk) - 2);
	start_new_movement = solved = false;
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

void Rubik::disable()
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

void Rubik::set_timer(const int& _timer)
{
	this->timer = _timer;
}

void Rubik::enable()
{
	enable_movement = start_new_movement = true;
	timer = (int)((90.0f / chunk) - 2);
}

void Rubik::render()
{

	look_for_movement();

	for (size_t i = 0; i < Cubes.size(); i++)
	{
		Cubes[i]->render();
	}
}

void Rubik::reassign_pointers(const std::vector<Cube**>& cur_litter, const unsigned int* pattern)
{
	std::vector<Cube*> new_litter;

	for (int i = 0; i < cur_litter.size(); i++)
	{
		new_litter.push_back(*cur_litter[i]);
	}

	for (int i = 0; i < cur_litter.size(); i++)
	{
		*cur_litter[i] = new_litter[pattern[i]];
	}
}

Point Rubik::get_center()
{
	return Cubes[13]->get_center();
}

void Rubik::stop_current_movement()
{
	if (f) {
		reassign_pointers(Frontal_Litter, non_prime_pattern);
	}
	else if (fPrime)
	{
		reassign_pointers(Frontal_Litter, prime_pattern);
	}
	else if (d)
	{
		reassign_pointers(Down_Litter, non_prime_pattern);
	}
	else if (dPrime)
	{
		reassign_pointers(Down_Litter, prime_pattern);
	}
	else if (u)
	{
		reassign_pointers(Up_Litter, non_prime_pattern);
	}
	else if (uPrime)
	{
		reassign_pointers(Up_Litter, prime_pattern);
	}
	else if (b)
	{
		reassign_pointers(Back_Litter, non_prime_pattern);
	}
	else if (bPrime)
	{
		reassign_pointers(Back_Litter, prime_pattern);
	}
	else if (r)
	{
		reassign_pointers(Right_Litter, non_prime_pattern);
	}
	else if (rPrime)
	{
		reassign_pointers(Right_Litter, prime_pattern);
	}
	else if (l)
	{
		reassign_pointers(Left_Litter, non_prime_pattern);
	}
	else if (lPrime)
	{
		reassign_pointers(Left_Litter, prime_pattern);
	}
	f =  fPrime = d = dPrime = u = uPrime = b = bPrime = r = rPrime = l = lPrime = false;
	if (moves.empty()) disable();
	else enable();
}

void Rubik::rotate_litter(const std::vector<Cube**>& cur_litter, const unsigned int &axis, const bool &clockwise)
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

bool Rubik::in_movement()
{
	return enable_movement;
}

void Rubik::move(const Matrix4D& transform)
{
	for (size_t i = 0; i < Cubes.size(); i++)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::look_for_movement()
{
	if (!enable_movement) return;

	if (this->timer-- < 0) {
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

	else if (retreating) retreat();
}

void Rubik::F()
{
	rotate_litter(Frontal_Litter, Z_AXIS, true);
}

void Rubik::FPrime()
{
	rotate_litter(Frontal_Litter, Z_AXIS, false);
}

void Rubik::D()
{
	rotate_litter(Down_Litter, Y_AXIS, true);
}

void Rubik::DPrime()
{
	rotate_litter(Down_Litter, Y_AXIS, false);
}

void Rubik::B()
{
	rotate_litter(Back_Litter, Z_AXIS, false);
}

void Rubik::BPrime()
{
	rotate_litter(Back_Litter, Z_AXIS, true);
}

void Rubik::U()
{
	rotate_litter(Up_Litter, Y_AXIS, false);
}

void Rubik::UPrime()
{
	rotate_litter(Up_Litter, Y_AXIS, true);
}

void Rubik::L()
{
	rotate_litter(Left_Litter, X_AXIS, false);
}

void Rubik::LPrime()
{
	rotate_litter(Left_Litter, X_AXIS, true);
}

void Rubik::R()
{
	rotate_litter(Right_Litter, X_AXIS, true);
}

void Rubik::RPrime()
{
	rotate_litter(Right_Litter, X_AXIS, false);
}

#endif //!__RUBIK_H__