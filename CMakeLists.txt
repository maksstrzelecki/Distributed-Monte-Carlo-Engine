cmake_minimum_required(VERSION 3.10)
project(DistributedMonteCarloEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(app main.cpp
    src/Instrument.cpp
    src/Stock.cpp
    src/Portfolio.cpp
    src/MarketScenario.cpp
    src/Task.cpp
    src/JobQueue.cpp
)

target_include_directories(app PRIVATE include)
