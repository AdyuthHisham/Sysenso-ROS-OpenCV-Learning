cmake_minimum_required(VERSION 2.8)
project( doubleCam )
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( doubleCam doubleCam.cpp )
target_link_libraries(doubleCam PRIVATE Threads::Threads)
target_link_libraries( doubleCam ${OpenCV_LIBS} )
