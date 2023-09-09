cmake_minimum_required(VERSION 3.10)

project("xnqsbar")
add_executable("xnqsbar" "src/main.cxx" "src/module_loader.cxx")
install(TARGETS xnqsbar DESTINATION ${CMAKE_INSTALL_PREFIX}/bin PERMISSIONS ${permissions})
