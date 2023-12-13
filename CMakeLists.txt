cmake_minimum_required(VERSION 3.24)
project(TS)

set(CMAKE_CXX_STANDARD 17)

add_executable(TS main.cpp structures/Graph.cpp structures/Graph.h utils/Timer.cpp utils/Timer.h algorithm/TabuSearch.cpp algorithm/TabuSearch.h structures/Move.cpp structures/Move.h structures/TabuList.cpp structures/TabuList.h Tester/AutoTest.cpp Tester/AutoTest.h)
