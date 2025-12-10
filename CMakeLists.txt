cmake_minimum_required(VERSION 3.15)

project(TrialClient)

add_executable(TrialClient client.cpp)

target_link_libraries(TrialClient PRIVATE pthread)
