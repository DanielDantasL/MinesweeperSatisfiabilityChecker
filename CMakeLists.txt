cmake_minimum_required(VERSION 3.14)
project(MinesweeperSatisfiabilityChecker)

set(CMAKE_CXX_STANDARD 14)

add_executable(MinesweeperSatisfiabilityChecker
        main.cpp MinesweeperBot.cpp MinesweeperBot.h MinesweeperInstance.cpp MinesweeperInstance.h)
