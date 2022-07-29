#ifdef _EXPORT
#include "Export.h"
#include <pybind11\pybind11.h>

namespace py = pybind11;
using namespace export_bind;

PYBIND11_MODULE(gen_colorline_data, m)
{
	m.doc() = "Generate ColorLine data";
	m.def("a", &generate_data, "123");
	m.def("b", &get_result, "123");



	pybind11::class_<Game_map>(m, "Game_map", pybind11::buffer_protocol())
		.def_buffer([](Game_map& m) -> pybind11::buffer_info {
		return pybind11::buffer_info(
			m.get__data_ptr(),								/* Pointer to buffer */
			sizeof(Color),									/* Size of one scalar */
			pybind11::format_descriptor<char>::format(),	/* Python struct-style format descriptor */
			2,												/* Number of dimensions */
			{ BOARD_SIZE,BOARD_SIZE },						/* Buffer dimensions */
			{ sizeof(Color) * BOARD_SIZE, sizeof(Color) }   /* Strides (in bytes) for each index */
		);

			});

	pybind11::class_<Moveable_mask>(m, "Moveable_mask", pybind11::buffer_protocol())
		.def_buffer([](Moveable_mask& m) -> pybind11::buffer_info {
		return pybind11::buffer_info(
			m.data(),								/* Pointer to buffer */
			sizeof(int),									/* Size of one scalar */
			pybind11::format_descriptor<int>::format(),	/* Python struct-style format descriptor */
			1,												/* Number of dimensions */
			{ POTENTIAL_MOVE_NUM },						/* Buffer dimensions */
			{  sizeof(int) }   /* Strides (in bytes) for each index */
		);
			});

	py::class_<Data_pack>(m, "Data_pack")
		.def(py::init<int,float>())
		.def_readonly("last",		&Data_pack::last)
		.def_readonly("last_mask",	&Data_pack::last_mask)
		.def_readonly("next",		&Data_pack::next)
		.def_readonly("next_mask",	&Data_pack::next_mask)
		.def_readonly("reward",		&Data_pack::reward)
		.def_readonly("move",		&Data_pack::move);
		// ... remainder ...

}
#endif // _EXPORT