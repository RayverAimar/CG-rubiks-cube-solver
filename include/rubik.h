#ifndef __RUBIK_H__
#define __RUBIK_H__

#include <queue>

#include "./cube.h"

void swap(Cube*, Cube*);

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

	std::vector<Cube*> Cubes;
	std::queue<char> solution;
	bool f = false, fPrime = false, d = false, dPrime = false, u = false, uPrime = false, b = false, bPrime = false, r = false, rPrime = false;
	bool l = false, lPrime = false, m = false, mPrime = false, e = false, ePrime = false, s = false, sPrime = false;

private:
	int timer;
	bool enable_movement, start_new_movement;
	float chunk;
	
	/* Movements Methods */

	void set_next_movement(char);
	void look_for_movement();
	void stop_current_movement();

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

void Rubik::stop_current_movement()
{
	if (f) {
		std::vector<Cube*> frontal_litter;
		for (int i = 0; i < 9; i++)
		{
			frontal_litter.push_back(Cubes[i]);
		}
		Cubes[0] = frontal_litter[6];
		Cubes[1] = frontal_litter[3];
		Cubes[2] = frontal_litter[0];
		Cubes[3] = frontal_litter[7];
		Cubes[4] = frontal_litter[4];
		Cubes[5] = frontal_litter[1];
		Cubes[6] = frontal_litter[8];
		Cubes[7] = frontal_litter[5];
		Cubes[8] = frontal_litter[2];

		std::cout << "Swapped F " << std::endl;
	}
	else if (fPrime)
	{
		std::vector<Cube*> frontal_litter;
		for (int i = 0; i < 9; i++)
		{
			frontal_litter.push_back(Cubes[i]);
		}

		Cubes[0] = frontal_litter[2];
		Cubes[1] = frontal_litter[5];
		Cubes[2] = frontal_litter[8];
		Cubes[3] = frontal_litter[1];
		Cubes[4] = frontal_litter[4];
		Cubes[5] = frontal_litter[7];
		Cubes[6] = frontal_litter[0];
		Cubes[7] = frontal_litter[3];
		Cubes[8] = frontal_litter[6];

		std::cout << "Swapped F Prime " << std::endl;
	}
	else if (d)
	{
		std::vector<Cube*> down_litter;
		for (int i = 0; i < Cubes.size(); i += 9)
		{
			down_litter.push_back(Cubes[i]);
			down_litter.push_back(Cubes[i + 1]);
			down_litter.push_back(Cubes[i + 2]);
		}

		Cubes[0] = down_litter[6];
		Cubes[1] = down_litter[3];
		Cubes[2] = down_litter[0];
		Cubes[9] = down_litter[7];
		Cubes[10] = down_litter[4];
		Cubes[11] = down_litter[1];
		Cubes[18] = down_litter[8];
		Cubes[19] = down_litter[5];
		Cubes[20] = down_litter[2];

		std::cout << "Swapped D " << std::endl;
	}
	else if (dPrime)
	{
		std::vector<Cube*> down_litter;
		for (int i = 0; i < Cubes.size(); i += 9)
		{
			down_litter.push_back(Cubes[i]);
			down_litter.push_back(Cubes[i + 1]);
			down_litter.push_back(Cubes[i + 2]);
		}

		Cubes[0] = down_litter[2];
		Cubes[1] = down_litter[5];
		Cubes[2] = down_litter[8];
		Cubes[9] = down_litter[1];
		Cubes[10] = down_litter[4];
		Cubes[11] = down_litter[7];
		Cubes[18] = down_litter[0];
		Cubes[19] = down_litter[3];
		Cubes[20] = down_litter[6];

		std::cout << "Swapped D Prime " << std::endl;
	}
	else if (u)
	{
		std::vector<Cube*> upper_litter;
		for (int i = 0; i < Cubes.size(); i += 9)
		{
			upper_litter.push_back(Cubes[i + 6]);
			upper_litter.push_back(Cubes[i + 7]);
			upper_litter.push_back(Cubes[i + 8]);
		}

		Cubes[6] = upper_litter[2];
		Cubes[7] = upper_litter[5];
		Cubes[8] = upper_litter[8];
		Cubes[15] = upper_litter[1];
		Cubes[16] = upper_litter[4];
		Cubes[17] = upper_litter[7];
		Cubes[24] = upper_litter[0];
		Cubes[25] = upper_litter[3];
		Cubes[26] = upper_litter[6];

		std::cout << "Swapped U " << std::endl;
	}
	else if (uPrime)
	{
		std::vector<Cube*> upper_litter;
		for (int i = 0; i < Cubes.size(); i += 9)
		{
			upper_litter.push_back(Cubes[i + 6]);
			upper_litter.push_back(Cubes[i + 7]);
			upper_litter.push_back(Cubes[i + 8]);
		}

		Cubes[6] = upper_litter[6];
		Cubes[7] = upper_litter[3];
		Cubes[8] = upper_litter[0];
		Cubes[15] = upper_litter[7];
		Cubes[16] = upper_litter[4];
		Cubes[17] = upper_litter[1];
		Cubes[24] = upper_litter[8];
		Cubes[25] = upper_litter[5];
		Cubes[26] = upper_litter[2];

		std::cout << "Swapped U Prime " << std::endl;
	}
	else if (b)
	{
		std::vector<Cube*> back_litter;

		for (int i = 18; i < Cubes.size(); i++)
		{
			back_litter.push_back(Cubes[i]);
		}

		Cubes[18] = back_litter[6];
		Cubes[19] = back_litter[3];
		Cubes[20] = back_litter[0];
		Cubes[21] = back_litter[7];
		Cubes[22] = back_litter[4];
		Cubes[23] = back_litter[1];
		Cubes[24] = back_litter[8];
		Cubes[25] = back_litter[5];
		Cubes[26] = back_litter[2];

		std::cout << "Swapped B " << std::endl;
	}
	else if (bPrime)
	{
		std::vector<Cube*> back_litter;

		for (int i = 18; i < Cubes.size(); i++)
		{
			back_litter.push_back(Cubes[i]);
		}

		Cubes[18] = back_litter[2];
		Cubes[19] = back_litter[5];
		Cubes[20] = back_litter[8];
		Cubes[21] = back_litter[1];
		Cubes[22] = back_litter[4];
		Cubes[23] = back_litter[7];
		Cubes[24] = back_litter[0];
		Cubes[25] = back_litter[3];
		Cubes[26] = back_litter[6];

		std::cout << "Swapped B Prime" << std::endl;

	}
	else if (r)
	{
		std::vector<Cube*> right_litter;

		for (int i = 0; i < Cubes.size(); i += 3)
		{
			right_litter.push_back(Cubes[i]);
		}

		Cubes[0] = right_litter[6];
		Cubes[3] = right_litter[3];
		Cubes[6] = right_litter[0];
		Cubes[9] = right_litter[7];
		Cubes[12] = right_litter[4];
		Cubes[15] = right_litter[1];
		Cubes[18] = right_litter[8];
		Cubes[21] = right_litter[5];
		Cubes[24] = right_litter[2];

		std::cout << "Swapped R " << std::endl;

	}
	else if (rPrime)
	{
		std::vector<Cube*> right_litter;

		for (int i = 0; i < Cubes.size(); i += 3)
		{
			right_litter.push_back(Cubes[i]);
		}

		Cubes[0] = right_litter[2];
		Cubes[3] = right_litter[5];
		Cubes[6] = right_litter[8];
		Cubes[9] = right_litter[1];
		Cubes[12] = right_litter[4];
		Cubes[15] = right_litter[7];
		Cubes[18] = right_litter[0];
		Cubes[21] = right_litter[3];
		Cubes[24] = right_litter[6];

		std::cout << "Swapped R Prime" << std::endl;

	}
	else if (l)
	{
		std::vector<Cube*> left_litter;
		for (int i = 2; i < Cubes.size(); i += 3)
		{
			left_litter.push_back(Cubes[i]);
		}
		Cubes[2] = left_litter[2];
		Cubes[5] = left_litter[5];
		Cubes[8] = left_litter[8];
		Cubes[11] = left_litter[1];
		Cubes[14] = left_litter[4];
		Cubes[17] = left_litter[7];
		Cubes[20] = left_litter[0];
		Cubes[23] = left_litter[3];
		Cubes[26] = left_litter[6];

		std::cout << "Swapped L " << std::endl;

	}
	else if (lPrime)
	{
		std::vector<Cube*> left_litter;
		for (int i = 2; i < Cubes.size(); i += 3)
		{
			left_litter.push_back(Cubes[i]);
		}
		Cubes[2] = left_litter[6];
		Cubes[5] = left_litter[3];
		Cubes[8] = left_litter[0];
		Cubes[11] = left_litter[7];
		Cubes[14] = left_litter[4];
		Cubes[17] = left_litter[1];
		Cubes[20] = left_litter[8];
		Cubes[23] = left_litter[5];
		Cubes[26] = left_litter[2];

		std::cout << "Swapped L Prime " << std::endl;
	}
	else if (m)
	{
		std::vector<Cube*> mid_litter;

		for (int i = 1; i < Cubes.size(); i += 3)
		{
			mid_litter.push_back(Cubes[i]);
		}

		Cubes[1] = mid_litter[2];
		Cubes[4] = mid_litter[5];
		Cubes[7] = mid_litter[8];
		Cubes[10] = mid_litter[1];
		Cubes[13] = mid_litter[4];
		Cubes[16] = mid_litter[7];
		Cubes[19] = mid_litter[0];
		Cubes[22] = mid_litter[3];
		Cubes[25] = mid_litter[6];

		std::cout << "Swapped M " << std::endl;

	}
	else if (mPrime)
	{
		std::vector<Cube*> mid_litter;

		for (int i = 1; i < Cubes.size(); i += 3)
		{
			mid_litter.push_back(Cubes[i]);
		}

		Cubes[1] = mid_litter[6];
		Cubes[4] = mid_litter[3];
		Cubes[7] = mid_litter[0];
		Cubes[10] = mid_litter[7];
		Cubes[13] = mid_litter[4];
		Cubes[16] = mid_litter[1];
		Cubes[19] = mid_litter[8];
		Cubes[22] = mid_litter[5];
		Cubes[25] = mid_litter[2];

		std::cout << "Swapped M Prime" << std::endl;
	}
	else if (e)
	{
		std::vector<Cube*> e_litter;
		for (int i = 3; i < Cubes.size(); i += 9)
		{
			e_litter.push_back(Cubes[i]);
			e_litter.push_back(Cubes[i + 1]);
			e_litter.push_back(Cubes[i + 2]);
		}

		Cubes[3] = e_litter[2];
		Cubes[4] = e_litter[5];
		Cubes[5] = e_litter[8];
		Cubes[12] = e_litter[1];
		Cubes[13] = e_litter[4];
		Cubes[14] = e_litter[7];
		Cubes[21] = e_litter[0];
		Cubes[22] = e_litter[3];
		Cubes[23] = e_litter[6];

		std::cout << "Swapped E " << std::endl;
	}
	else if (ePrime)
	{
		std::vector<Cube*> e_litter;
		for (int i = 3; i < Cubes.size(); i += 9)
		{
			e_litter.push_back(Cubes[i]);
			e_litter.push_back(Cubes[i + 1]);
			e_litter.push_back(Cubes[i + 2]);
		}

		Cubes[3] = e_litter[6];
		Cubes[4] = e_litter[3];
		Cubes[5] = e_litter[0];
		Cubes[12] = e_litter[7];
		Cubes[13] = e_litter[4];
		Cubes[14] = e_litter[1];
		Cubes[21] = e_litter[8];
		Cubes[22] = e_litter[5];
		Cubes[23] = e_litter[2];

		std::cout << "Swapped E Prime " << std::endl;
	}
	else if (s)
	{
		std::vector<Cube*> s_litter;

		for (int i = 9; i < 18; i++)
		{
			s_litter.push_back(Cubes[i]);
		}

		Cubes[9] = s_litter[6];
		Cubes[10] = s_litter[3];
		Cubes[11] = s_litter[0];
		Cubes[12] = s_litter[7];
		Cubes[13] = s_litter[4];
		Cubes[14] = s_litter[1];
		Cubes[15] = s_litter[8];
		Cubes[16] = s_litter[5];
		Cubes[17] = s_litter[2];

		std::cout << "Swapped S " << std::endl;
	}
	else if (sPrime)
	{
		std::vector<Cube*> s_litter;

		for (int i = 9; i < 18; i++)
		{
			s_litter.push_back(Cubes[i]);
		}

		Cubes[9] = s_litter[2];
		Cubes[10] = s_litter[5];
		Cubes[11] = s_litter[8];
		Cubes[12] = s_litter[1];
		Cubes[13] = s_litter[4];
		Cubes[14] = s_litter[7];
		Cubes[15] = s_litter[0];
		Cubes[16] = s_litter[3];
		Cubes[17] = s_litter[6];

		std::cout << "Swapped S Prime " << std::endl;
	}

	f =  fPrime = d = dPrime = u = uPrime = b = bPrime = r = rPrime = false;
	l =  lPrime = m = mPrime = e = ePrime = s = sPrime = false;
	if (solution.empty()) disable();
	else enable();
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
	Point cur_center = Cubes[4]->get_center();
	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk, Z_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);
	
	for (int i = 0; i < 9; i++)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::FPrime()
{
	Point cur_center = Cubes[4]->get_center();
	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-chunk, Z_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < 9; i++)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::D()
{
	Point cur_center = Cubes[10]->get_center();
	
	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-chunk, Y_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < Cubes.size(); i+=9)
	{
		Cubes[i]->transform(transform);
		Cubes[i + 1]->transform(transform);
		Cubes[i + 2]->transform(transform);
	}
}

void Rubik::DPrime()
{
	Point cur_center = Cubes[10]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk, Y_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < Cubes.size(); i += 9)
	{
		Cubes[i]->transform(transform);
		Cubes[i + 1]->transform(transform);
		Cubes[i + 2]->transform(transform);
	}
}

void Rubik::B()
{
	Point cur_center = Cubes[22]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk, Z_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 18; i < Cubes.size(); i ++)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::BPrime()
{
	Point cur_center = Cubes[22]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-chunk, Z_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 18; i < Cubes.size(); i++)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::U()
{
	Point cur_center = Cubes[16]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk, Y_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < Cubes.size(); i += 9)
	{
		Cubes[i + 6]->transform(transform);
		Cubes[i + 7]->transform(transform);
		Cubes[i + 8]->transform(transform);
	}
}

void Rubik::UPrime()
{
	Point cur_center = Cubes[10]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-chunk, Y_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < Cubes.size(); i += 9)
	{
		Cubes[i + 6]->transform(transform);
		Cubes[i + 7]->transform(transform);
		Cubes[i + 8]->transform(transform);
	}
}

void Rubik::L()
{
	Point cur_center = Cubes[14]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-chunk, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 2; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::LPrime()
{
	Point cur_center = Cubes[14]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 2; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::R()
{
	Point cur_center = Cubes[12]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::RPrime()
{
	Point cur_center = Cubes[12]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-chunk, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::M()
{
	Point cur_center = Cubes[13]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-chunk, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 1; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::MPrime()
{
	Point cur_center = Cubes[13]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 1; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::E()
{
	Point cur_center = Cubes[13]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk, Y_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 3; i < Cubes.size(); i += 9)
	{
		Cubes[i]->transform(transform);
		Cubes[i + 1]->transform(transform);
		Cubes[i + 2]->transform(transform);
	}
}

void Rubik::EPrime()
{
	Point cur_center = Cubes[13]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-chunk, Y_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 3; i < Cubes.size(); i += 9)
	{
		Cubes[i]->transform(transform);
		Cubes[i + 1]->transform(transform);
		Cubes[i + 2]->transform(transform);
	}
}

void Rubik::S()
{
	Point cur_center = Cubes[13]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(chunk, Z_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 9; i < 18; i++)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::SPrime()
{
	Point cur_center = Cubes[13]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-chunk, Z_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 9; i < 18; i++)
	{
		Cubes[i]->transform(transform);
	}
}

void swap(Cube* one, Cube* two)
{
	Cube* temp = one;
	one = two;
	two = temp;
}

#endif //!__RUBIK_H__