cmake_minimum_required(VERSION 3.13)
project(tictactoe)

# 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
    
# 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available 
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

find_package(SDL2_image REQUIRED)

# Begin: GDK
add_library(gdk "")

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
# End: GDK

# Create your game executable target as usual 
add_executable(tictactoe WIN32 main.c board.h board.c manager.h manager.c resources.h resources.c)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications  
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(tictactoe PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(tictactoe PRIVATE SDL2::SDL2-static SDL2_image::SDL2_image-static)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/board.png ${CMAKE_CURRENT_BINARY_DIR}/assets/board.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/nought.png ${CMAKE_CURRENT_BINARY_DIR}/assets/nought.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/cross.png ${CMAKE_CURRENT_BINARY_DIR}/assets/cross.png COPYONLY)
