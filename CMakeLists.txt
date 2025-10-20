cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Matplot++
add_subdirectory(libs/matplotplusplus)

# Add your source files
add_executable(my_app
    main.cpp
    Commodity.cpp
    Harvest.cpp
    Gems.cpp
    Game.cpp
)

# Link Matplot++
target_link_libraries(my_app PRIVATE matplot)