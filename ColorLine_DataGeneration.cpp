#include <iostream>
#include "head.h"

Random random_generator = Random();
//void init(void)
//{
//	srand(time(NULL));
//	std::cout << "Dll initialized!" << std::endl;
//}
int main()
{
    #ifdef DEBUG
	std::cout << "DEBUG\n";
#else
	std::cout << "No DEBUG\n";
#endif

	auto a = game_map(0.5);
	a.print();



}
