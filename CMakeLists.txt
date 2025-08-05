cmake_minimum_required(VERSION 3.10)
project(MatrixOperations)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем каталог с заголовками
include_directories(include)

# Создаем исполняемый файл
add_executable(matrix_operations src/main.cpp)

# Настройки для отладки
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
