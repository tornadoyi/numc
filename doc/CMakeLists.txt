project(numc_doc)

find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Can not find doxygen to generate document, download from https://www.stack.nl/~dimitri/doxygen/index.html")
endif()


# set doxygen config file
set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in)
set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

# Set some doxygen flags
set(NC_DOXY_PROJECT_NAME            "numc")
set(NC_VERSION                      "0.1")
set(NC_BINARY_DIR                   "${CMAKE_CURRENT_BINARY_DIR}")
set(NC_DOXY_INTERNAL                "YES")
set(NC_DOXY_INPUT                   "${CMAKE_CURRENT_SOURCE_DIR}/../numc")

configure_file(${doxyfile_in} ${doxyfile})

add_custom_target(${PROJECT_NAME}
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)