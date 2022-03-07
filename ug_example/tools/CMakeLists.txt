cmake_minimum_required(VERSION 2.9) 

set(TARGET_NAME "xtdc4_ugex")
set(CRONO_DEP_PKG_WIN_REF "xtdc4_driver-bin/[~0.0.1]")
set(CRONO_DEP_PKG_LINUX_REF "xtdc4_driver/[~0.0.1]")

project(${TARGET_NAME})

# _____________________________________________________________________________
# Build Windows(x86/x86_64)/Linux(x86_64) `xtdc4_ugex.exe/Linux` executable, 
# for (Debug/Release) configurations.
# Publish conan package to local cache as per `CRONO_PUBLISH_LOCAL_PKG` 
# argument.
# `conan install` is used to fetch, build, and deploy the dependency.
#
# Dependencies: 
# - `xtdc4_driver-bin` for Winodws.
# - `xtdc4_driver` for Linux.
# 
# Prequisites: 
# - conan remote server(s) that have the traversal dependencies are added 
#   and authenticated.
# - Conan recipe is on the same folder.
# 
# Arguments:
# `CRONO_PUBLISH_LOCAL_PKG`: Publish project packages to conan local cache
# - Passed as `-DCRONO_PUBLISH_LOCAL_PKG=N`
# - Values:
#        `N` : Do not publish.
#    Default : Publish
# _____________________________________________________________________________

# _____________________________________________________________________________
# General Validations and Configurations
#
# Check supported architecture, and set `CRONO_GEN_ARCH` to `x86_64` for all
# variations of `x64` platforms, and to `x86` for all variations of `x86` 
# platforms.
# Set `CRONO_GEN_PLATFORM` to either `windows` or `linux`
# All names are in small letters.
IF(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
        set(CRONO_GEN_PLATFORM "windows")
        set(CRONO_GEN_ARCH "x86")
ELSEIF(CMAKE_GENERATOR_PLATFORM STREQUAL "Win64"
       OR CMAKE_GENERATOR_PLATFORM STREQUAL "x64")  # Fron conan on Windows 64 Bit
        set(CRONO_GEN_PLATFORM "windows")
        set(CRONO_GEN_ARCH "x86_64")
ELSEIF(NOT CMAKE_GENERATOR_PLATFORM)
        if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
                set(CRONO_GEN_PLATFORM "windows")
                if(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
                        set(CRONO_GEN_ARCH "x86_64")
                else()
                        set(CRONO_GEN_ARCH ${CMAKE_SYSTEM_PROCESSOR})
                endif()
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
                set(CRONO_GEN_ARCH ${CMAKE_SYSTEM_PROCESSOR})
                set(CRONO_GEN_PLATFORM "linux")
        endif()
        message(STATUS "Crono: generator platform is assumed "
                       "<${CRONO_GEN_PLATFORM}> as none was specified.")
ELSE()
        message(SEND_ERROR 
                "Crono: unsupported architecture <${CMAKE_GENERATOR_PLATFORM}>")
ENDIF()

# cd indirection from /tools to the project source code, "." if no shift
set(PROJ_SRC_INDIR ..)  

# Include directories paths
include_directories(${TARGET_NAME} PRIVATE ${PROJ_SRC_INDIR}/include)

# Source files settings
set(SOURCE 
        ${PROJ_SRC_INDIR}/src/xtdc4_user_guide_example.cpp
)
set(HEADERS
        ${PROJ_SRC_INDIR}/include/TDC4_interface.h
        ${PROJ_SRC_INDIR}/include/xTDC4_interface.h
        ${PROJ_SRC_INDIR}/include/crono_interface.h
)

# _____________________________________________________________________________
# Windows-specific Configurations
#
IF ( CRONO_GEN_PLATFORM  STREQUAL "windows")

        # Set the output directories __________________________________________
        
        # Set the build arch-oriented directory path
        set(CRONO_ARCH_BUILD_DIR 
                ${CMAKE_BINARY_DIR}/build/windows/${CRONO_GEN_ARCH})
        
        # Set the library build directory 
        set(LIB_OUTPUT_DIR ${CRONO_ARCH_BUILD_DIR}/$<LOWER_CASE:$<CONFIG>>/lib)

        # Create .exe file in /bin
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CRONO_ARCH_BUILD_DIR})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug/bin) 
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release/bin) 

        # Set the executable build directory, under /bin 
        set(BIN_OUTPUT_DIR 
                ${CRONO_ARCH_BUILD_DIR}/$<LOWER_CASE:$<CONFIG>>/bin)

        # Link to xtdc4_driver library ________________________________________
        add_library(xtdc4_driver SHARED IMPORTED GLOBAL)
        set_target_properties(xtdc4_driver PROPERTIES 
                IMPORTED_IMPLIB xtdc4_driver.lib)  
        link_directories(${LIB_OUTPUT_DIR})

        # Build the EXE  ______________________________________________________
        add_executable(${TARGET_NAME} "${SOURCE}" "${HEADERS}")
        target_link_libraries(${TARGET_NAME} xtdc4_driver)

        # Deploy `xtdc4_driver` library using conan ___________________________
        # `xtdc4_driver.lib/dll` path in the package is expected to be of the 
        # same pattern of CMAKE_RUNTIME_OUTPUT_DIRECTORY, to be copied to the
        # library output directory {LIB_OUTPUT_DIR}
        add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD 
                COMMAND "echo" Crono: Fetching xtdc4_driver library using 
                                conan package ${CRONO_DEP_PKG_WIN_REF}
                COMMAND "conan" install ${CRONO_DEP_PKG_WIN_REF}@ 
                                --install-folder \"${LIB_OUTPUT_DIR}\"
                                -s build_type=$<CONFIG> 
                                -s arch=${CRONO_GEN_ARCH})
        
        # Copy the `xtdc4_driver.lib/dll` files to tbe /bin for the executable
        # file to run
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD 
                COMMAND "echo"  "Crono: copying xtdc4_driver library"
                                " from <${LIB_OUTPUT_DIR}>"
                                " to <${BIN_OUTPUT_DIR}>"
                COMMAND "copy"  \"${LIB_OUTPUT_DIR}\" \"${BIN_OUTPUT_DIR}\")
                
        # Publish packages on conan local cache _______________________________ 
        IF (NOT CRONO_PUBLISH_LOCAL_PKG STREQUAL "N")
                add_custom_command(TARGET ${TARGET_NAME} POST_BUILD 
                        COMMAND "echo" Crono: building and publishing Main Package 
                                        to conan cache... 
                        COMMAND "conan" create ${CMAKE_SOURCE_DIR} 
                                        -s build_type=$<CONFIG> 
                                        -s arch=${CRONO_GEN_ARCH})
        ENDIF()
        
        # Messages ____________________________________________________________
        message(STATUS "Crono: output debug directory is "
                        "<${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}>")
        message(STATUS "Crono: output release directory is "
                        "<${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}>")

# _____________________________________________________________________________
# Linux-specific Configurations
#
ELSEIF (CRONO_GEN_PLATFORM STREQUAL "linux") 

        # Compilation options _________________________________________________ 
        add_compile_options(-Wall)
        if(NOT CMAKE_BUILD_TYPE)
                message(STATUS  "Crono: assuming build type is `Release` "
                                "as none was specified.")
                set(CMAKE_BUILD_TYPE Release)
        elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
                add_compile_definitions(
                        CRONO_DEBUG_ENABLED
                )
                add_compile_options(-g)
        endif()
        # All paths are in lower case
        string(TOLOWER ${CMAKE_BUILD_TYPE} CRONO_BUILD_TYPE)
        
        # Set the output directory ____________________________________________

        # Set the build configuration-oriented directory path
        set(CRONO_CONFIG_BUILD_DIR 
                ${CMAKE_BINARY_DIR}/build/linux/x86_64/${CRONO_BUILD_TYPE})

        # Set the executable build directory
        set(BIN_OUTPUT_DIR ${CRONO_CONFIG_BUILD_DIR}/bin)

        # Set the library build directory 
        set(LIB_OUTPUT_DIR ${CRONO_CONFIG_BUILD_DIR}/lib)

        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})

        # Link to xtdc4_driver library ________________________________________
        add_library(xtdc4_driver STATIC IMPORTED GLOBAL)
        set_target_properties(xtdc4_driver PROPERTIES 
                IMPORTED_IMPLIB xtdc4_driver.a)  
        link_directories(${LIB_OUTPUT_DIR})

        # Build the EXE  ______________________________________________________
        add_executable(${TARGET_NAME} "${SOURCE}" "${HEADERS}")
        target_link_libraries(${TARGET_NAME} xtdc4_driver.a)

        # Deploy `xtdc4_driver` library using conan ___________________________
        # `xtdc4_driver.a` path in the package is expected to be of the 
        # same pattern of LIB_OUTPUT_DIR, to be copied to the library output 
        # directory {LIB_OUTPUT_DIR}
        add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD 
                COMMAND "echo" Crono: Fetching and building xtdc4_driver library 
                                using conan package ${CRONO_DEP_PKG_LINUX_REF}
                COMMAND "conan" install ${CRONO_DEP_PKG_LINUX_REF}@ --build
                                --install-folder ${LIB_OUTPUT_DIR}
                                -s build_type=${CMAKE_BUILD_TYPE}
                                -s arch=${CRONO_GEN_ARCH}
                # Rename the library with prefix `lib` for the linker to find 
                # it
                COMMAND "cp"    ${LIB_OUTPUT_DIR}/xtdc4_driver.a 
                                ${LIB_OUTPUT_DIR}/libxtdc4_driver.a )
                        
        # Adjust .o files names  ______________________________________________
        # Remove .cpp from .o file name
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON) 
        
        # Publish packages on conan local cache _______________________________ 
        IF (NOT CRONO_PUBLISH_LOCAL_PKG STREQUAL "N")
                add_custom_command(TARGET ${TARGET_NAME} POST_BUILD 
                        COMMAND "echo" Crono: building and publishing Main Package 
                                        to conan cache... 
                        COMMAND "conan" create ${CMAKE_SOURCE_DIR} 
                                        -s build_type=${CMAKE_BUILD_TYPE}
                                        -s arch=x86_64)
        ENDIF()
        
        # Messages ____________________________________________________________
        message(STATUS "Crono: library output directory is "
                        "<${CMAKE_RUNTIME_OUTPUT_DIRECTORY}>")

ELSE()
        message(SEND_ERROR "Crono: unsupported system <${CMAKE_SYSTEM_NAME}> "
                "and arch <${CMAKE_SYSTEM_PROCESSOR}>" )
ENDIF()

# _____________________________________________________________________________
message(STATUS "Crono: architecture is <${CRONO_GEN_ARCH}> for <${CRONO_GEN_PLATFORM}>" )
