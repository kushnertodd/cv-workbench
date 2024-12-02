cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
project(cv-workbench LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed")
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/module/")


include(UseDoxygenDoc)


## link libs

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
message("FOUND: ${Threads}")

# OpenSSL::SSL
# https://cmake.org/cmake/help/v3.6/module/FindOpenSSL.html
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

# https://github.com/cloudshark/cshark/blob/master/build/modules/FindJSON-C.cmake
find_package(JSON-C REQUIRED)

# https://github.com/Kitware/CMake/blob/master/Modules/FindJPEG.cmake
find_package(JPEG REQUIRED)

# https://github.com/sum01/FindBerkeleyDB
find_package(BerkeleyDB REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/FindBerkeleyDB")

find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)

# https://cmake.org/cmake/help/latest/module/SelectLibraryConfigurations.html
# https://github.com/Kitware/CMake/blob/master/Modules/FindPackageHandleStandardArgs.cmake
# https://github.com/Kitware/CMake/blob/master/Modules/FindPackageMessage.cmake

#
# examples

#add_executable(excxx_example_database_load apps/excxx_example_database_load.cpp)
#
#target_link_libraries(excxx_example_database_load
#        PRIVATE example-lib bdb-lib
#        PUBLIC Oracle::BerkeleyDB
#        PUBLIC ${JSON-C_LIBRARIES}
#        )
#
#add_executable(excxx_example_database_read apps/excxx_example_database_read.cpp)
#
#target_link_libraries(excxx_example_database_read
#        PRIVATE example-lib bdb-lib
#        PUBLIC Oracle::BerkeleyDB
#        PUBLIC ${JSON-C_LIBRARIES}
#        PUBLIC OpenSSL::SSL
#        PUBLIC OpenSSL::Crypto
#        PUBLIC Threads::Threads
#        )
#
add_doxygen_doc(
        BUILD_DIR
        ${CMAKE_CURRENT_BINARY_DIR}/_build
        DOXY_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
        TARGET_NAME
        docs
        COMMENT
        "HTML documentation"
)
add_subdirectory(cv-lib)
add_executable(cv-workbench
src/cv-workbench.cpp
)
target_link_libraries(cv-workbench
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
        )
target_include_directories(cv-workbench PUBLIC cv-lib)
