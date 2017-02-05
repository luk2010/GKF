# CMake file to build GKF Project library.
# Library is outputted in directory ./lib .

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(GKF VERSION 1)

# Add project specific cmake modules.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Define the global output path of binaries.
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

# Add the project include directory as additional include path.
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Enable C++11.
set(CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")

set(HEADERS
    ./inc/Base.h
    ./inc/Exceptions.h
    ./inc/LocaleFile.h
    ./inc/Locales.h
    ./inc/Translation.h
)

set(SOURCE_FILES
    ./src/Exceptions.cpp
    ./src/LocaleFile.cpp
    ./src/Translation.cpp
    ./src/Locales.cpp
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Mac OS X Specific Code.

    set(SOURCE_FILES
        ${SOURCE_FILES}
        ./src/Darwin/DarwinLocales.mm
    )

    add_library(
        gkf SHARED 
        ${SOURCE_FILES} ${HEADERS}
    )

    set(CMAKE_SHARED_LINKER_FLAGS "-framework CoreFoundation ${CMAKE_SHARED_LINKER_FLAGS}")

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if(${CMAKE_GENERATOR} MATCHES "Xcode")

    macro (set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
        set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY}
                      ${XCODE_VALUE})
    endmacro (set_xcode_property)

    set_xcode_property(gkf CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set_xcode_property(gkf CLANG_CXX_LIBRARY "libc++")

    set_property(TARGET gkf PROPERTY CXX_STANDARD 11)
    set_property(TARGET gkf PROPERTY CXX_STANDARD_REQUIRED ON)

else()

    set_property(TARGET gkf PROPERTY CXX_STANDARD 11)
    set_property(TARGET gkf PROPERTY CXX_STANDARD_REQUIRED ON)

endif(${CMAKE_GENERATOR} MATCHES "Xcode")