#include <iostream>
#include "gen_data.h"

//void init(void)
//{
//	srand(time(NULL));
//	std::cout << "Dll initialized!" << std::endl;
//}
int main()
{
#ifdef _DEBUG
	std::cout << "DEBUG\n";
#else
	std::cout << "No DEBUG\n";
#endif



#ifdef _DEBUG
	auto result = Gen_data(4, 0.6).go();
	result.print();

	//int times = 3000;

	//for (int i = 0; i < times; i++)
	//	Gen_data(4, 0.6).go();
#else
	int times = 1000000;

	for (int i=0;i<times;i++)
		Gen_data(4, 0.6).go();
#endif
	//a.print();

}

