cmake_minimum_required(VERSION 2.8) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.
set(PROJECT_NAME lab7)
project("${PROJECT_NAME}" )

add_executable("${PROJECT_NAME}" main.cpp)		# Создает исполняемый файл с именем main
