#include "my_func.h"


std::mt19937 myfunc::Random::mt = std::mt19937(std::random_device()());
std::uniform_int_distribution<int> myfunc::Random::_random = std::uniform_int_distribution<int>(0, INT32_MAX);
