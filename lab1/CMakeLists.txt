cmake_minimum_required(VERSION 3.10)

# �������� �������
project(lab1)

# ��������� �������� C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ��������� �������� ���� ��� lab1_generator
# add_executable(lab1_generator ../src/code_generator.cpp)
add_executable(lab1_generator src/code_generator.cpp)

# ������� ��� ������� lab1_generator
add_custom_command(
    TARGET lab1_generator
    POST_BUILD
    COMMAND lab1_generator
    COMMENT "Running lab1_generator after build"
)

# ��������� �������� ����� ��� lab1_test
# add_executable(lab1_test ../src/test.cpp ../src/func.cpp)
add_executable(lab1_test src/test.cpp src/func.cpp)

# ��������� ����������� ������ lab1_test �� ���������� lab1_generator
add_dependencies(lab1_test lab1_generator)

# ������� ��� ������� lab1_test ����� ��� ������
add_custom_command(
    TARGET lab1_test
    POST_BUILD
    COMMAND lab1_test
    COMMENT "Running lab1_test after build"
)
