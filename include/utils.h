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

#define CUBE_FRAGMENT_SHADER_PATH			"..\\..\\..\\..\\..\\src\\Tutorial_Rubik\\shaders\\fShader.fs"
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

#define BLUE_COLOR							glm::vec4(0.1882f, 0.6588f, 0.9568f, 1.0f)
#define RED_COLOR							glm::vec4(0.9960f, 0.3529f, 0.3490f, 1.0f)
#define YELLOW_COLOR						glm::vec4(1.0000f, 0.9921f, 0.3254f, 1.0f)
#define ORANGE_COLOR						glm::vec4(1.0000f, 0.4862f, 0.2745f, 1.0f)
#define GREEN_COLOR							glm::vec4(0.5372f, 0.9490f, 0.4431f, 1.0f)
#define WHITE_COLOR							glm::vec4(0.9411f, 0.9254f, 0.9529f, 1.0f)
#define BLACK_COLOR							glm::vec4(0.1215f, 0.1254f, 0.1254f, 1.0f)

const char valid_moves[] = { F_MOVEMENT, D_MOVEMENT, U_MOVEMENT, B_MOVEMENT, R_MOVEMENT, L_MOVEMENT,
							 F_PRIME_MOVEMENT, D_PRIME_MOVEMENT, U_PRIME_MOVEMENT, B_PRIME_MOVEMENT, R_PRIME_MOVEMENT, L_PRIME_MOVEMENT };

const unsigned int prime_pattern[]		= { 2, 5, 8, 1, 4, 7, 0, 3, 6};
const unsigned int non_prime_pattern[]	= { 6, 3, 0 , 7, 4, 1, 8, 5, 2};

const unsigned int frontal_litter_idx[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
const unsigned int back_litter_idx[]	= { 20, 19, 18, 23, 22, 21, 26, 25, 24 };
const unsigned int up_litter_idx[]		= { 6, 7, 8, 15, 16, 17, 24, 25, 26 };
const unsigned int down_litter_idx[]	= { 18, 19, 20, 9, 10, 11, 0, 1, 2 };
const unsigned int left_litter_idx[]	= { 2, 11, 20, 5, 14, 23, 8, 17, 26 };
const unsigned int right_litter_idx[]	= { 0, 3, 6, 9, 12, 15, 18, 21, 24 };

const unsigned int clockwise_rotation_idx[] = { 18, 19, 20, 9, 10, 11, 0, 1, 2, 21, 22, 23, 12, 13, 14, 3, 4, 5, 24, 25, 26, 15, 16, 17, 6, 7, 8 };
const unsigned int non_clockwise_rotation_idx[] = { 6, 7, 8, 15, 16, 17, 24, 25, 26, 3, 4, 5, 12, 13, 14, 21, 22, 23, 0, 1, 2, 9, 10, 11, 18, 19, 20 };
const unsigned int x_view_idx[] = { 18, 9, 0, 21, 12, 3, 24, 15, 6, 19, 10, 1, 22, 13, 4, 25, 16, 7, 20, 11, 2, 23, 14, 5, 26, 17 ,8 };
const unsigned int y_view_idx[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2, 15, 12, 9, 16, 13, 10, 17, 14, 11, 24, 21, 18, 25, 22, 19, 26, 23, 20 };
const unsigned int z_view_idx[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };


#endif // __UTILS_H__
