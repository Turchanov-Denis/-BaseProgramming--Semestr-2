cmake_minimum_required(VERSION 2.8) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.
set(PROJECT_NAME lab2)
project("${PROJECT_NAME}" )
include_directories("inc/")
add_executable("${PROJECT_NAME}" main.cpp
                inc/String.hpp
                src/String.cpp        )		# Создает исполняемый файл с именем main
									# из исходника main.cpp