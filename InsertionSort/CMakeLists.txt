﻿# CMakeList.txt: проект CMake для InsertionSort; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (InsertionSort "InsertionSort.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET InsertionSort PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
