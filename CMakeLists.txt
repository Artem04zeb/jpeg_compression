cmake_minimum_required(VERSION 3.12)
project(JPEGCompressor)

set(CMAKE_CXX_STANDARD 20)

# Найти OpenCV
find_package(OpenCV REQUIRED)

# Включить директорию include
include_directories(include)
include_directories(src)

# Добавить исполняемый файл
file(GLOB SOURCES "src/*.cpp")
add_executable(jpeg_compressor ${SOURCES} "src/utils.cpp")

# Линковка с OpenCV
target_link_libraries(jpeg_compressor ${OpenCV_LIBS})
