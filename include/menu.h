#ifndef __MENU__
#define __MENU__

#include <iostream>

void menu()
{
	std::cout << "Press: " << std::endl;
	std::cout << "F -> Frontal Litter" << std::endl;
	std::cout << "B -> Back Litter" << std::endl;

	std::cout << "D -> Down Litter" << std::endl;

	std::cout << "U -> Up Litter" << std::endl;
	std::cout << "L -> Left Litter" << std::endl;
	std::cout << "R -> Right Litter " << std::endl;

	std::cout << "Once you type all movements you want to do press ENTER to apply it to the cube" << std::endl;
	std::cout << "Once the cube is scrambled press SPACE to solve it " << std::endl;

}

#endif // !
