cmake_minimum_required (VERSION 3.8)
project("gen_colorline_data")
#option(DBG_PATHFINDING "" OFF)
#option(DBG_GAMECONTROLER "" OFF)
#option(DBG_GAMECONTROLER "" OFF)
AUX_SOURCE_DIRECTORY(. SRC_LIST)

#if(DBG_PATHFINDING)
#	add_definitions(-DDBG_PATHFINDING)
#	add_executable (debugger_pathfinding ${SRC_LIST} Dbg/pathfinding.cpp)
#elseif(DBG_GAMECONTROLER)
#	add_definitions(-DDBG_GAMECONTROLER)
#	add_executable (debugger_gamecontroler ${SRC_LIST} Dbg/gamecontroler.cpp)
#else()
#	add_library(env SHARED ${SRC_LIST})	
#endif()



add_definitions(-D_EXPORT)

include_directories("~/pybind11/include/")

add_library(gen_colorline_data SHARED ${SRC_LIST})	
