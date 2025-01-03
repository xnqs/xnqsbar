cmake_minimum_required(VERSION 3.10)

project("xnqsbar")
link_libraries("X11")
add_executable("xnqsbar" "src/main.cxx" "src/module_loader.cxx" "src/utils.cxx")
install(TARGETS xnqsbar DESTINATION ${CMAKE_INSTALL_PREFIX}/bin PERMISSIONS ${permissions})
