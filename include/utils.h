#ifndef __UTILS_H__
#define __UTILS_H__

#define SCR_TITLE							"Rayver - OpenGL Project"
#define SCR_WIDTH							800
#define SCR_HEIGHT							600

#define X_AXIS								0
#define Y_AXIS								1
#define Z_AXIS								2

#define PI									3.14159265359
#define to_radians(x)						(x * (float) PI ) / 180.0f

#define GREEN_FRAGMENT_SHADER_PATH			"..\\..\\..\\..\\..\\src\\Tutorial_Rubik\\shaders\\green.fs"
#define WHITE_FRAGMENT_SHADER_PATH			"..\\..\\..\\..\\..\\src\\Tutorial_Rubik\\shaders\\white.fs"
#define BLACK_FRAGMENT_SHADER_PATH			"..\\..\\..\\..\\..\\src\\Tutorial_Rubik\\shaders\\black.fs"
#define BLUE_FRAGMENT_SHADER_PATH			"..\\..\\..\\..\\..\\src\\Tutorial_Rubik\\shaders\\blue.fs"
#define YELLOW_FRAGMENT_SHADER_PATH			"..\\..\\..\\..\\..\\src\\Tutorial_Rubik\\shaders\\yellow.fs"
#define RED_FRAGMENT_SHADER_PATH			"..\\..\\..\\..\\..\\src\\Tutorial_Rubik\\shaders\\red.fs"
#define FRAGMENT_SHADER_PATH				"..\\..\\..\\..\\..\\src\\Tutorial_Rubik\\shaders\\fragment_shader.fs"
#define VERTEX_SHADER_PATH					"..\\..\\..\\..\\..\\src\\Tutorial_Rubik\\shaders\\vertex_shader.vs"


#define F_MOVEMENT							'F'
#define D_MOVEMENT							'D'
#define U_MOVEMENT							'U'
#define B_MOVEMENT							'B'
#define R_MOVEMENT							'R'
#define L_MOVEMENT							'L'
#define M_MOVEMENT							'M'
#define E_MOVEMENT							'E'
#define S_MOVEMENT							'S'

#define F_PRIME_MOVEMENT					'f'
#define D_PRIME_MOVEMENT					'd'
#define U_PRIME_MOVEMENT					'u'
#define B_PRIME_MOVEMENT					'b'
#define R_PRIME_MOVEMENT					'r'
#define L_PRIME_MOVEMENT					'l'
#define M_PRIME_MOVEMENT					'm'
#define E_PRIME_MOVEMENT					'e'
#define S_PRIME_MOVEMENT					's'


const char valid_moves[] = { F_MOVEMENT, D_MOVEMENT, U_MOVEMENT, B_MOVEMENT, R_MOVEMENT, L_MOVEMENT,
F_PRIME_MOVEMENT, D_PRIME_MOVEMENT, U_PRIME_MOVEMENT, B_PRIME_MOVEMENT, R_PRIME_MOVEMENT, L_PRIME_MOVEMENT };
const unsigned int prime_pattern[] = {2, 5, 8, 1, 4, 7, 0, 3, 6};
const unsigned int non_prime_pattern[] = {6, 3, 0 , 7, 4, 1, 8, 5, 2};

const unsigned int frontal_litter_idx[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
const unsigned int back_litter_idx[]	= { 20, 19, 18, 23, 22, 21, 26, 25, 24 };
const unsigned int up_litter_idx[]		= { 6, 7, 8, 15, 16, 17, 24, 25, 26 };
const unsigned int down_litter_idx[]	= { 18, 19, 20, 9, 10, 11, 0, 1, 2 };
const unsigned int left_litter_idx[]	= { 2, 11, 20, 5, 14, 23, 8, 17, 26 };
const unsigned int right_litter_idx[]	= { 0, 3, 6, 9, 12, 15, 18, 21, 24 };
const unsigned int middle_litter_idx[]	= { 1, 4, 7, 10, 13, 16, 19, 22, 25 };
const unsigned int e_litter_idx[]		= { 3, 4, 5, 12, 13, 14, 21, 22, 23 };
const unsigned int s_litter_idx[]		= { 9, 10, 11, 12, 13, 14, 15, 16, 17 };


#endif // __UTILS_H__
