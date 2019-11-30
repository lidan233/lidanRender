cmake_minimum_required(VERSION 3.1)
project(tinyrender)

include_directories(/usr/local/include /usr/local/Cellar/eigen/3.3.7/include)
include_directories(/Users/lidan/Desktop/软光栅/tinyrender/headers)
link_directories(/usr/local/lib /usr/local/)

add_executable(tinyrender   main.cpp module/tgaimage.cpp geom/Point.cpp geom/Point.h geom/Line.cpp geom/Line.h util/calculate.h util/data.h module/ModelAndView.cpp module/ModelAndView.h util/common.h geom/triangle.cpp geom/triangle.h util/data.cpp util/manipulation.cpp util/manipulation.h)
