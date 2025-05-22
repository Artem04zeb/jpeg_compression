cmake_minimum_required(VERSION 3.12)
project(JPEGCompressor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавить директорию include в пути поиска заголовков
include_directories(include)

# Найти OpenCV
find_package(OpenCV REQUIRED)

# Добавить исполняемый файл из всех .cpp файлов в src
file(GLOB SOURCES "src/*.cpp")
add_executable(jpeg_compressor ${SOURCES})

# Линковка с OpenCV
target_link_libraries(jpeg_compressor ${OpenCV_LIBS})
