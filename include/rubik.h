#ifndef __RUBIK_H__
#define __RUBIK_H__

#include <queue>
#include "./cube.h"

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
	void set_camera(Camera);
	void set_speed(const float&);
	void read_solution(const std::string&);
	void disable();
	bool in_movement();

	/* Variables */

	std::vector<Cube*> Cubes;
	std::vector<Cube**> Frontal_Litter, Back_Litter, Up_Litter, Down_Litter, Left_Litter, Right_Litter, Middle_Litter, E_Litter, S_Litter;
	std::queue<char> solution;
	bool f = false, fPrime = false, d = false, dPrime = false, u = false, uPrime = false, b = false, bPrime = false, r = false, rPrime = false;
	bool l = false, lPrime = false, m = false, mPrime = false, e = false, ePrime = false, s = false, sPrime = false;

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

	/* External Movements */

	void M();
	void E();
	void S();

	void MPrime();
	void EPrime();
	void SPrime();
	
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
		Middle_Litter.push_back(&Cubes[middle_litter_idx[i]]);
		E_Litter.push_back(&Cubes[e_litter_idx[i]]);
		S_Litter.push_back(&Cubes[s_litter_idx[i]]);
	}
}

Rubik::~Rubik()
{
}

void Rubik::read_solution(const std::string& sol)
{
	for (int i = 0; i < sol.size(); i++)
	{
		solution.push(sol[i]);
	}
}

void Rubik::set_speed(const float& _chunk)
{
	chunk = _chunk;
}

void Rubik::set_next_movement(char cur_movement)
{
	timer = (int)((90.0f / chunk) - 2);
	start_new_movement = false;
	//n_moves = 0;
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
		case M_MOVEMENT:
			m = true;
			break;
		case M_PRIME_MOVEMENT:
			mPrime = true;
			break;
		case E_MOVEMENT:
			e = true;
			break;
		case E_PRIME_MOVEMENT:
			ePrime = true;
			break;
		case S_MOVEMENT:
			s = true;
			break;
		case S_PRIME_MOVEMENT:
			sPrime = true;
			break;
		default:
			break;
	}
}

void Rubik::disable()
{
	enable_movement = start_new_movement = true;
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

void Rubik::stop_current_movement()
{
	if (f) {
		reassign_pointers(Frontal_Litter, non_prime_pattern);
		std::cout << "Swapped F " << std::endl;
	}
	else if (fPrime)
	{
		reassign_pointers(Frontal_Litter, prime_pattern);
		std::cout << "Swapped F Prime " << std::endl;
	}
	else if (d)
	{
		reassign_pointers(Down_Litter, non_prime_pattern);
		std::cout << "Swapped D" << std::endl;
	}
	else if (dPrime)
	{
		reassign_pointers(Down_Litter, prime_pattern);
		std::cout << "Swapped D Prime " << std::endl;
	}
	else if (u)
	{
		reassign_pointers(Up_Litter, non_prime_pattern);
		std::cout << "Swapped U " << std::endl;
	}
	else if (uPrime)
	{
		reassign_pointers(Up_Litter, prime_pattern);
		std::cout << "Swapped U Prime " << std::endl;
	}
	else if (b)
	{
		reassign_pointers(Back_Litter, non_prime_pattern);
		std::cout << "Swapped B " << std::endl;
	}
	else if (bPrime)
	{
		reassign_pointers(Back_Litter, prime_pattern);
		std::cout << "Swapped B Prime" << std::endl;
	}
	else if (r)
	{
		reassign_pointers(Right_Litter, non_prime_pattern);
		std::cout << "Swapped R " << std::endl;
	}
	else if (rPrime)
	{
		reassign_pointers(Right_Litter, prime_pattern);
		std::cout << "Swapped R Prime" << std::endl;
	}
	else if (l)
	{
		reassign_pointers(Left_Litter, non_prime_pattern);
		std::cout << "Swapped L " << std::endl;
	}
	else if (lPrime)
	{
		reassign_pointers(Left_Litter, prime_pattern);
		std::cout << "Swapped L Prime " << std::endl;
	}
	else if (m)
	{
		reassign_pointers(Middle_Litter, non_prime_pattern);
		std::cout << "Swapped M " << std::endl;

	}
	else if (mPrime)
	{
		reassign_pointers(Middle_Litter, prime_pattern);
		std::cout << "Swapped M Prime" << std::endl;
	}
	else if (e)
	{
		reassign_pointers(E_Litter, non_prime_pattern);
		std::cout << "Swapped E " << std::endl;
	}
	else if (ePrime)
	{
		reassign_pointers(E_Litter, prime_pattern);
		std::cout << "Swapped E Prime " << std::endl;
	}
	else if (s)
	{
		reassign_pointers(S_Litter, non_prime_pattern);
		std::cout << "Swapped S " << std::endl;
	}
	else if (sPrime)
	{
		reassign_pointers(S_Litter, prime_pattern);
		std::cout << "Swapped S Prime " << std::endl;
	}
	f =  fPrime = d = dPrime = u = uPrime = b = bPrime = r = rPrime = false;
	l =  lPrime = m = mPrime = e = ePrime = s = sPrime = false;
	if (solution.empty()) disable();
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

void Rubik::set_camera(Camera camera)
{
	for (int i = 0; i < Cubes.size(); i++)
		Cubes[i]->set_camera(camera);
}

void Rubik::look_for_movement()
{
	if (!enable_movement) return;

	if (this->timer-- < 0) {
		stop_current_movement();
		return;
	}

	if (!solution.empty() && start_new_movement)
	{
		char next_movement = this->solution.front();
		this->solution.pop();
		set_next_movement(next_movement);
	}
	if		(f)			F();
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

	else if (m)			M();
	else if (mPrime)	MPrime();

	else if (e)			E();
	else if (ePrime)	EPrime();

	else if (s)			S();
	else if (sPrime)	SPrime();

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

void Rubik::M()
{
	rotate_litter(Middle_Litter, X_AXIS, true);
}

void Rubik::MPrime()
{
	rotate_litter(Middle_Litter, X_AXIS, false);
}

void Rubik::E()
{
	rotate_litter(E_Litter, Y_AXIS, false);
}

void Rubik::EPrime()
{
	rotate_litter(E_Litter, Y_AXIS, true);
}

void Rubik::S()
{
	rotate_litter(S_Litter, Z_AXIS, true);
}

void Rubik::SPrime()
{
	rotate_litter(S_Litter, Z_AXIS, false);
}

#endif //!__RUBIK_H__