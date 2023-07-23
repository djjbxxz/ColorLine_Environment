#ifdef _EXPORT
#include "Export.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace export_bind;

PYBIND11_MODULE(gen_colorline_data_pytorch, m)
{
	m.doc() = "Generate ColorLine data";
	m.def("get_random_start", &generate_data, "123");
	m.def("get_valid_mask", &get_valid_mask, "123");
	m.def("_994_to_9928", &_994_to_9928, "123");
	m.def("rule", &rule, "123");

	py::class_<Game_map>(m, "Game_map", pybind11::buffer_protocol())
		//.def(py::init<>())
		.def_readwrite("game_map", &Game_map::_data)
		.def_readwrite("coming_chess", &Game_map::coming_chess);
			
		//.def_property("v1", [](Game_map& self) {
		//return py::array<char>(self._data.size(), self._data.data());
		//	}, [](Game_map& self, py::array_t<char> new_val) {
		//		std::copy_n(new_val.data(), self.v1.size(), self.v1.data());
		//	})
		//.def_property("v2", [](Game_map& self) {
		//		return py::array_t<char>(self.v2.size(), self.v2.data());
		//	}, [](Game_map& self, py::array_t<char> new_val) {
		//		std::copy_n(new_val.data(), self.v2.size(), self.v2.data());
		//	});

	pybind11::class_<Game_map>(m, "Game_map", pybind11::buffer_protocol())
		.def_buffer([](Game_map& m) -> pybind11::buffer_info {
		return pybind11::buffer_info(
			m.get__data_ptr(),								/* Pointer to buffer */
			sizeof(char),									/* Size of one scalar */
			pybind11::format_descriptor<char>::format(),	/* Python struct-style format descriptor */
			1,												/* Number of dimensions */
			{ BOARD_SIZE* BOARD_SIZE + COMING_CHESS_NUM },						/* Buffer dimensions */
			{ sizeof(char)}   /* Strides (in bytes) for each index */
		);

			}).def_readwrite("board", &Game_map::_data)
				.def_readwrite("coming_chess", &Game_map::coming_chess);

	pybind11::class_<Moveable_mask>(m, "Moveable_mask", pybind11::buffer_protocol())
		.def_buffer([](Moveable_mask& m) -> pybind11::buffer_info {
		return pybind11::buffer_info(
			m.data(),								/* Pointer to buffer */
			sizeof(int),									/* Size of one scalar */
			pybind11::format_descriptor<int>::format(),	/* Python struct-style format descriptor */
			1,												/* Number of dimensions */
			{ POTENTIAL_MOVE_NUM },						/* Buffer dimensions */
			{ sizeof(int) }   /* Strides (in bytes) for each index */
		);
			});

	//pybind11::class_<Color>(m, "Color", pybind11::buffer_protocol())
	//	.def_buffer([](Color& m) -> pybind11::buffer_info {
	//	return pybind11::buffer_info(
	//		&m.value,								/* Pointer to buffer */
	//		sizeof(char),									/* Size of one scalar */
	//		pybind11::format_descriptor<char>::format(),	/* Python struct-style format descriptor */
	//		1,												/* Number of dimensions */
	//		{ 1 },						/* Buffer dimensions */
	//		{ sizeof(char) }   /* Strides (in bytes) for each index */
	//	);

	//		});

	pybind11::class_<game_statu_9928>(m, "game_statu_9928", pybind11::buffer_protocol())
		.def_buffer([](game_statu_9928& m) -> pybind11::buffer_info {
		return pybind11::buffer_info(
			&m.value,								/* Pointer to buffer */
			sizeof(int),									/* Size of one scalar */
			pybind11::format_descriptor<int>::format(),	/* Python struct-style format descriptor */
			3,												/* Number of dimensions */
			{ INPUT_CHANNEL_SIZE,BOARD_SIZE,BOARD_SIZE },						/* Buffer dimensions */
			{ sizeof(int) * BOARD_SIZE * BOARD_SIZE,sizeof(int) * BOARD_SIZE, sizeof(int) }   /* Strides (in bytes) for each index */
		);

			});

}
#endif // _EXPORT