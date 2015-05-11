cmake_minimum_required(VERSION 2.8)
project( heatmap_mask )
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED )
find_package( GEOS REQUIRED )
find_package( Spatialindex REQUIRED )


include_directories(common ~/boost_1_55_0)
#include_directories(${Boost_INCLUDE_DIR})
add_executable( heatmapMask
	heatmap_mask.cpp
	BoundaryFixFunction.cpp
	BoundaryFixFunction2.cpp
	clipper.cpp
)
add_executable( heatmaps
	heatmaps.cpp
)

target_link_libraries( heatmaps ${OpenCV_LIBS} )
target_link_libraries( heatmapMask ${OpenCV_LIBS} ${GEOS_LIBRARY} ${SPATIALINDEX_LIBRARY})
