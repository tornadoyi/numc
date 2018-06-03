


include_directories(${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE all_files ${CMAKE_CURRENT_LIST_DIR}/*.h ${CMAKE_CURRENT_LIST_DIR}/*.cc)


set(SOURCES "${SOURCES};${all_files}")