# CMakeList.txt: проект CMake для Shell_sort; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Shell_sort "Shell_sort.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Shell_sort PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
