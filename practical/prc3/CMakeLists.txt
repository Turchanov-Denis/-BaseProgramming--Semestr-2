
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.
set(PROJECT_NAME prc3)
project("${PROJECT_NAME}" )

set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
add_definitions(-DSFML_STATIC)


include_directories("C:/Users/turch/Desktop/study/Study programming/-BaseProgramming--Semestr-2/practical/prc3/SFML/include")	# добавляем директории
link_directories("C:/Users/turch/Desktop/study/Study programming/-BaseProgramming--Semestr-2/practical/prc3/SFML/lib/")
add_executable("${PROJECT_NAME}" main.cpp)		# Создает исполняемый файл с именем main
target_link_libraries("${PROJECT_NAME}" sfml-graphics-s-d
        sfml-window-s-d
        sfml-system-s-d
        opengl32
        freetype
        winmm
        gdi32
        sfml-audio-s-d
        openal32
        flac
        vorbisenc
        vorbisfile
        vorbis
        ogg)