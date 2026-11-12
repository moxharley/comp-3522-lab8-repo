cmake_minimum_required(VERSION 3.20)
project(lab8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab8 main.cpp auction.cpp auction.hpp auctioneer.cpp auctioneer.hpp bidder.cpp bidder.hpp)
