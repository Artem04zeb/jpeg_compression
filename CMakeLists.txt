cmake_minimum_required(VERSION 3.12)
project(JPEGCompressor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# �������� ���������� include � ���� ������ ����������
include_directories(include)

# ����� OpenCV
find_package(OpenCV REQUIRED)

# �������� ����������� ���� �� ���� .cpp ������ � src
file(GLOB SOURCES "src/*.cpp")
add_executable(jpeg_compressor ${SOURCES})

# �������� � OpenCV
target_link_libraries(jpeg_compressor ${OpenCV_LIBS})
