#ifndef _EXPORT



#include <iostream>
#include "gen_data.h"
#include "Export.h"

using namespace export_bind;
using namespace myfunc;
int main(int argc, char* argv[])
{
#ifdef _DEBUG
	std::cout << "DEBUG\n";
#endif

#ifdef _PERFTEST
	int lined_num = 3;
	float fill_ratio = 0.99;
	int times = 100000;

	generate_data(times, lined_num, fill_ratio);
	std::vector< Data_pack*> result;
	result.reserve(times);
	FOR_RANGE(i, times)
		result.push_back(get_result(i));

#endif

	}
#endif

