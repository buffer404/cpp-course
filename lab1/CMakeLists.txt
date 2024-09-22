cmake_minimum_required(VERSION 3.10)

# Название проекта
project(lab1)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Добавляем исходный файл для lab1_generator
# add_executable(lab1_generator ../src/code_generator.cpp)
add_executable(lab1_generator src/code_generator.cpp)

# Команда для запуска lab1_generator
add_custom_command(
    TARGET lab1_generator
    POST_BUILD
    COMMAND lab1_generator
    COMMENT "Running lab1_generator after build"
)

# Добавляем исходные файлы для lab1_test
# add_executable(lab1_test ../src/test.cpp ../src/func.cpp)
add_executable(lab1_test src/test.cpp src/func.cpp)

# Указываем зависимость сборки lab1_test от выполнения lab1_generator
add_dependencies(lab1_test lab1_generator)

# Команда для запуска lab1_test после его сборки
add_custom_command(
    TARGET lab1_test
    POST_BUILD
    COMMAND lab1_test
    COMMENT "Running lab1_test after build"
)
