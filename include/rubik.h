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
	void read_solution(std::string);
	void start_solving();
	bool in_movement();

	std::vector<Cube*> Cubes;
	std::queue<char> solution;
	bool f = false, fPrime = false, d = false, dPrime = false, u = false, uPrime = false, b = false, bPrime = false, r = false, rPrime = false;
	bool l = false, lPrime = false, m = false, mPrime = false, e = false, ePrime = false, s = false, sPrime = false;

private:
	int timer;
	bool enable_movement, solving;
	int i = 0;
	
	/* Movements Methods */

	void set_next_movement(char);
	void look_for_movement();
	void no_movement();

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

Rubik::Rubik() : timer(0), enable_movement(false), solving(false)
{
}

Rubik::Rubik(const Point& center, const float& separation) : timer(0), enable_movement(false), solving(false)
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

void Rubik::read_solution(std::string sol)
{
	for (int i = 0; i < sol.size(); i++)
	{
		solution.push(sol[i]);
	}
}

void Rubik::set_next_movement(char cur_movement)
{
	enable_movement = true;
	timer = 118;
	solving = false;

	switch(cur_movement)
	{
		case F_MOVEMENT:
			f = true;
			break;
		case D_MOVEMENT:
			d = true;
			break;
		case U_MOVEMENT:
			u = true;
			break;
		case B_MOVEMENT:
			b = true;
			break;
		case R_MOVEMENT:
			r = true;
			break;
		case L_MOVEMENT:
			l = true;
			break;
		case M_MOVEMENT:
			m = true;
			break;
		case E_MOVEMENT:
			e = true;
			break;
		case S_MOVEMENT:
			s = true;
			break;
		default:
			break;
	}
}

void Rubik::start_solving()
{
	solving = true;
}

void Rubik::set_timer(const int& _timer)
{
	this->timer = _timer;
}

void Rubik::enable()
{
	enable_movement = true;
	timer = 119;
}

void Rubik::render()
{

	look_for_movement();

	for (size_t i = 0; i < Cubes.size(); i++)
	{
		Cubes[i]->render();
	}
}

void Rubik::no_movement()
{
	f =  fPrime = d = dPrime = u = uPrime = b = bPrime = r = rPrime = false;
	l =  lPrime = m = mPrime = e = ePrime = s = sPrime = enable_movement = false;
	solving = true;
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
	if (!enable_movement && !solving) {
		std::cout << i++ << std::endl;
		return;
	}

	if (this->timer-- < 0 && !solving ) {
		no_movement();
		return;
	}

	if (!solution.empty() && solving)
	{
		char cur_movement = solution.front();
		solution.pop();
		set_next_movement(cur_movement);
		if (solution.empty()) solving = false;
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
	transform.rotate(0.75f, Z_AXIS);
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
	transform.rotate(-0.75f, Z_AXIS);
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
	transform.rotate(-0.75f, Y_AXIS);
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
	transform.rotate(0.75f, Y_AXIS);
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
	transform.rotate(0.75f, Z_AXIS);
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
	transform.rotate(-0.75f, Z_AXIS);
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
	transform.rotate(0.75f, Y_AXIS);
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
	transform.rotate(-0.75f, Y_AXIS);
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
	Point cur_center = Cubes[12]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(0.75f, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::LPrime()
{
	Point cur_center = Cubes[12]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-0.75f, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 0; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::R()
{
	Point cur_center = Cubes[14]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(-0.75f, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 2; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::RPrime()
{
	Point cur_center = Cubes[14]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(0.75f, X_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 2; i < Cubes.size(); i += 3)
	{
		Cubes[i]->transform(transform);
	}
}

void Rubik::M()
{
	Point cur_center = Cubes[13]->get_center();

	Matrix4D transform(1.0f);
	transform.translate(cur_center.x, cur_center.y, cur_center.z);
	transform.rotate(0.75f, X_AXIS);
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
	transform.rotate(-0.75f, X_AXIS);
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
	transform.rotate(-0.75f, Y_AXIS);
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
	transform.rotate(0.75f, Y_AXIS);
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
	transform.rotate(0.75f, Z_AXIS);
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
	transform.rotate(-0.75f, Z_AXIS);
	transform.translate(-cur_center.x, -cur_center.y, -cur_center.z);

	for (int i = 9; i < 18; i++)
	{
		Cubes[i]->transform(transform);
	}
}

#endif //!__RUBIK_H__