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
add_executable(image-copy
        src/image-copy.cpp
)
target_link_libraries(image-copy
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
)
#target_include_directories(cv-workbench PUBLIC cv-lib)
add_executable(image-corr
        src/image-corr.cpp
)
target_link_libraries(image-corr
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
)
add_executable(image-dump
        src/image-dump.cpp
)
target_link_libraries(image-dump
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
)
add_executable(image-info
        src/image-info.cpp
)
target_link_libraries(image-info
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
)
add_executable(image-map
        src/image-map.cpp
)
target_link_libraries(image-map
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
)
add_executable(image-mean
        src/image-mean.cpp
)
target_link_libraries(image-mean
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
)
add_executable(image-morph
        src/image-morph.cpp
)
target_link_libraries(image-morph
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
)
add_executable(image-read
        src/image-read.cpp
)
target_link_libraries(image-read
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
)
add_executable(image-trig
        src/image-trig.cpp
)
target_link_libraries(image-trig
        PRIVATE cv-lib
        PUBLIC Oracle::BerkeleyDB
        PUBLIC ${JSON-C_LIBRARIES}
        PUBLIC ${JPEG_LIBRARIES}
)
