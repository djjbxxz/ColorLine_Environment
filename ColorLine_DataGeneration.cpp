#ifndef _EXPORT



#include <iostream>
#include "gen_data.h"
#include "Export.h"

using namespace export_bind;
int main()
{
#ifdef _DEBUG
	std::cout << "DEBUG\n";
#endif



#ifdef _DEBUG
	int lined_num = 3;
	float fill_ratio = 0.99;
	//auto result = Gen_data(lined_num, fill_ratio).go();
	//result.print();

	//int times = 3000;

	//for (int i = 0; i < times; i++)
	//	Gen_data(4, 0.6).go();
#else

	int lined_num = 3;
	float fill_ratio = 0.99;
	int times = 100000;

	generate_data(times, lined_num, fill_ratio);
	std::vector< Data_pack*> result;
	result.reserve(times);
	FOR_RANGE(i,times)
		result.push_back(get_result(i));

#endif

}
#endif

