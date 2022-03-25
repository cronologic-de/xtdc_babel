cmake_minimum_required(VERSION 3.12) 
set(TARGET_NAME "xtdc4_ugex")
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

# General Validations and Configurations ______________________________________
# Check supported architecture, and set `CRONO_GEN_ARCH` to `x86_64` for all
# variations of `x64` platforms, and to `x86` for all variations of `x86` 
# platforms.
# Set `CRONO_GEN_PLATFORM` to either `windows` or `linux`
# All names are in small letters.
SET(CRONO_GEN_PLATFORM "windows")
IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CRONO_GEN_PLATFORM "linux")
ENDIF()

list(APPEND x64_archs Win64 AMD64 X86 x86_64)
IF(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
        set(CRONO_GEN_ARCH "x86")
ELSEIF(CMAKE_SYSTEM_PROCESSOR IN_LIST x64_archs)
        set(CRONO_GEN_ARCH "x86_64")
ENDIF()

# cd indirection from /tools to the project source code, "." if no shift
set(PROJ_SRC_INDIR ..)  

# Dependency directory
set(CRONO_DEP_PKG_DIR ${CMAKE_BINARY_DIR}/dep_pkg)
set(CRONO_DEP_PKG_LIB_DIR ${CRONO_DEP_PKG_DIR}/lib)

# Include and Link directories paths
include_directories(${TARGET_NAME} PRIVATE 
        ${PROJ_SRC_INDIR}/include
        # Include dependency folder
        ${CRONO_DEP_PKG_DIR}/include
)
link_directories(${CRONO_DEP_PKG_LIB_DIR})

# Set the output directory ____________________________________________________
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 
        ${CMAKE_BINARY_DIR}/build/${CRONO_GEN_PLATFORM}/${CRONO_GEN_ARCH}/$<IF:$<CONFIG:Debug>,debug,release>/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
        ${CMAKE_BINARY_DIR}/build/${CRONO_GEN_PLATFORM}/${CRONO_GEN_ARCH}/$<IF:$<CONFIG:Debug>,debug,release>/bin)
        
# Add the EXE ytarget  ________________________________________________________
add_executable(${TARGET_NAME} ${PROJ_SRC_INDIR}/src/xtdc4_user_guide_example.cpp)

# Deploy `xtdc4_driver` library using conan ___________________________________
# `xtdc4_driver.lib/dll/a` path in the package is expected to be copied to the
# library output directory {CRONO_DEP_PKG_DIR}
IF(CRONO_GEN_PLATFORM STREQUAL "windows")
        set(CRONO_DEP_PKG_REF "xtdc4_driver-bin/[~0.0.1]")
ELSE()
        set(CRONO_DEP_PKG_REF "xtdc4_driver/[~0.0.1]")
ENDIF()
add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD 
        COMMAND  "echo" Crono: Fetching and deploying ${CRONO_DEP_PKG_REF} library using conan.
        COMMAND "conan" install ${CRONO_DEP_PKG_REF}@  --install-folder \"${CRONO_DEP_PKG_DIR}\"
                -s build_type=$<CONFIG> -s arch=${CRONO_GEN_ARCH})

# Windows-specific Configurations _____________________________________________
IF ( CRONO_GEN_PLATFORM  STREQUAL "windows")
        # Link to xtdc4_driver library ________________________________________
        add_library(xtdc4_driver SHARED IMPORTED GLOBAL)
        set_target_properties(xtdc4_driver PROPERTIES IMPORTED_IMPLIB xtdc4_driver.lib)  
        target_link_libraries(${TARGET_NAME} xtdc4_driver)

        # Copy the `xtdc4_driver.lib/dll` files to the /bin for the executable
        # file to run
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD 
                COMMAND "echo"  "Crono: copying xtdc4_driver library from <${CRONO_DEP_PKG_LIB_DIR}>"
                                " to <${CMAKE_RUNTIME_OUTPUT_DIRECTORY}>"
                COMMAND "copy"  \"${CRONO_DEP_PKG_LIB_DIR}\" \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\")

# Linux-specific Configurations _______________________________________________
ELSEIF (CRONO_GEN_PLATFORM STREQUAL "linux") 
        # Compilation options _________________________________________________ 
        add_compile_options(-Wall $<$<CONFIG:Debug>:-g>)
        add_compile_definitions($<$<CONFIG:Debug>:CRONO_DEBUG_ENABLED>)
        if (NOT CMAKE_BUILD_TYPE)
                message(STATUS  "Crono: assuming build type is `Release` as none was specified.")
                set(CMAKE_BUILD_TYPE Release)
        endif()

        # Rename the library with prefix `lib` for the linker to find it
        add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD 
                COMMAND "cp" ${CRONO_DEP_PKG_LIB_DIR}/xtdc4_driver.a 
                        ${CRONO_DEP_PKG_LIB_DIR}/libxtdc4_driver.a)

        # Link to xtdc4_driver library ________________________________________
        add_library(xtdc4_driver STATIC IMPORTED GLOBAL)
        set_target_properties(xtdc4_driver PROPERTIES IMPORTED_IMPLIB xtdc4_driver.a)  
        target_link_libraries(${TARGET_NAME} xtdc4_driver.a)

        # Adjust .o files names  ______________________________________________
        # Remove .cpp from .o file name
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON) 
ENDIF()

# Publish packages on conan local cache _______________________________________ 
IF (NOT CRONO_PUBLISH_LOCAL_PKG STREQUAL "N")
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD 
                COMMAND  "echo" Crono: exporting Main Package to conan local cache, from current/build directory
                COMMAND "conan" export-pkg ${CMAKE_SOURCE_DIR} --force -sf ../..
                                -s build_type=$<CONFIG> -s arch=${CRONO_GEN_ARCH})
ENDIF()

# _____________________________________________________________________________
message(STATUS "Crono: architecture is <${CRONO_GEN_ARCH}> for <${CRONO_GEN_PLATFORM}>" )