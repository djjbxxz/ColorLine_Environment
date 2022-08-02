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
	using namespace std;
	int lined_num = 3;
	float fill_ratio = 0.9;
	int times = 1;

	generate_data(times, lined_num, fill_ratio);
	std::vector< Data_pack*> results;
	results.reserve(times);
	FOR_RANGE(i, times)
		results.push_back(get_result(i));
	auto result = results[0];
	result->last->print();
	result->next->print();
	auto& mask = *result->last_mask;
	Move::from_densed(result->move).print();
	cout << mask[result->move-1] << mask[result->move] << mask[result->move+1] <<endl;
	cout << "Score : " << result->reward;
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

