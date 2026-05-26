cmake_minimum_required(VERSION 3.10)
project(MyPaint)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Возвращаем оригинальное имя SFML, так как файлы конфигурации называются SFMLConfig.cmake
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

add_executable(paint src/paint_core.cpp src/main.cpp)

# Линковка для SFML 2.x (в нижнем регистре с дефисами)
target_link_libraries(paint PRIVATE sfml-graphics sfml-window sfml-system)
