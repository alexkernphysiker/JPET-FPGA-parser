add_subdirectory(dumpwrap)
add_library(generatedump SHARED queue.cpp detectionsystem.cpp tdc.cpp)
target_link_libraries(generatedump dumpwrap)
