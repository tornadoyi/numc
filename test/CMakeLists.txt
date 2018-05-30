

function (build_target arg)
    message(STATUS "============================= BUILD ${ARGV0} START =============================")
    add_subdirectory(${ARGV0})
    message(STATUS "============================= BUILD ${ARGV0} END =============================\n\n\n")
endfunction ()


build_target("temp_test")
build_target("arch_test")