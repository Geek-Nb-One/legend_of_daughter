cmake_minimum_required(VERSION 3.5.0)
project(legend_of_daughter VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}

    "D:\\Libs\\SDL2-2.28.4\\x86_64-w64-mingw32\\include"
    "D:\\Libs\\SDL2-2.28.4\\x86_64-w64-mingw32\\include\\SDL2"
    "D:\\Libs\\SDL2_ttf-2.20.2\\x86_64-w64-mingw32\\include"
    "D:\\Libs\\SDL2_mixer-2.6.3\\x86_64-w64-mingw32\\include"
    "D:\\Libs\\SDL2_image-2.8.1\\x86_64-w64-mingw32\\include"
)

link_directories( 
    "D:\\Libs\\SDL2-2.28.4\\x86_64-w64-mingw32\\lib" 
    "D:\\Libs\\SDL2_ttf-2.20.2\\x86_64-w64-mingw32\\lib"
    "D:\\Libs\\SDL2_mixer-2.6.3\\x86_64-w64-mingw32\\lib"
    "D:\\Libs\\SDL2_image-2.8.1\\x86_64-w64-mingw32\\lib"
)

link_libraries(SDL2_mixer SDL2_ttf SDL2 SDL2main SDL2_image)

add_subdirectory(src)

add_executable(legend_of_daughter main.cpp)

target_include_directories(legend_of_daughter PUBLIC src)
target_link_libraries(legend_of_daughter PUBLIC game)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_target(copy_graphics ALL  
COMMAND ${CMAKE_COMMAND} -E copy_directory 
${PROJECT_SOURCE_DIR}/graphics 
${PROJECT_BINARY_DIR}/graphics 
COMMENT "Copying graphics folder")

add_custom_target(copy_sound ALL  
COMMAND ${CMAKE_COMMAND} -E copy_directory 
${PROJECT_SOURCE_DIR}/sound
${PROJECT_BINARY_DIR}/sound 
COMMENT "Copying sounds folder")

add_custom_target(copy_font ALL  
COMMAND ${CMAKE_COMMAND} -E copy_directory 
${PROJECT_SOURCE_DIR}/font
${PROJECT_BINARY_DIR}/font 
COMMENT "Copying font folder")


add_dependencies(legend_of_daughter copy_graphics )
add_dependencies(legend_of_daughter copy_sound )