#pragma once
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define PRINT_MACRO_NAME_VALUE(name) #name ": " TOSTRING(name)
