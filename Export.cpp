#include "Export.h"
#include <pybind11\pybind11.h>
namespace py = pybind11;

PYBIND11_MODULE(gen_colorline_data, m)
{
	m.doc() = "Generate ColorLine data";
	m.def("get_data", &generate_data,"123");
}