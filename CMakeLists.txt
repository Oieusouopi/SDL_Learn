cmake_minimum_required(VERSION 3.31)
project(Learn_SDL C)

set(CMAKE_C_STANDARD 23)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Learn_SDL main.c)
target_link_libraries(Learn_SDL ${SDL2_LIBRARIES})

include_directories(/usr/include/SDL2)
link_directories(/usr/lib/x86_64-linux-gnu)

add_executable(02_getting_an_image_on_the_screen 02_getting_an_image_on_the_screen/main.c)
target_link_libraries(02_getting_an_image_on_the_screen ${SDL2_LIBRARIES})

add_executable(03_Event_Driven_Programming 03_Event_Driven_Programming/main.c)
target_link_libraries(03_Event_Driven_Programming ${SDL2_LIBRARIES})

add_executable(04-optimized_surface_loading_and_soft_streching 04-optimized_surface_loading_and_soft_streching/main.c)
target_link_libraries(04-optimized_surface_loading_and_soft_streching ${SDL2_LIBRARIES})

add_executable(05_extension_libraries_and_loading_other_image_formats 05_extension_libraries_and_loading_other_image_formats/main.c)
target_link_libraries(05_extension_libraries_and_loading_other_image_formats ${SDL2_LIBRARIES})
target_link_libraries(05_extension_libraries_and_loading_other_image_formats SDL2 SDL2_image)


add_executable(06_geometry_rendering 06_Geometry_rendering/main.c)
target_link_libraries(06_geometry_rendering ${SDL2_LIBRARIES})
target_link_libraries(06_geometry_rendering SDL2 SDL2_image)

add_executable(07_ViewPort 07_ViewPort/main.c)
target_link_libraries(07_ViewPort ${SDL2_LIBRARIES})
target_link_libraries(07_ViewPort SDL2 SDL2_image)
