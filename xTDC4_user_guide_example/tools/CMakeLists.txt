cmake_minimum_required(VERSION 3.12) 
set(CRONO_TARGET_NAME "xtdc4_ugex")
project(${CRONO_TARGET_NAME})
# $$
# _____________________________________________________________________________
# Build Windows(x86/x86_64)/Linux(x86_64) `xtdc4_ugex.exe/Linux` executable, 
# for (Debug/Release) configurations.
# Publish conan package to local cache as per `CRONO_PUBLISH_LOCAL_PKG` 
# argument.
# `conan install` is used to fetch, build, and deploy the dependency.
#
# Dependencies: 
# - 'crono_project_tools'
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

# General Validations and Configurations ======================================

# cd indirection from /tools to the project source code, "." if no shift
set(PROJ_SRC_INDIR ..)  

# Get the platform and architecure ____________________________________________
# Check supported architecture, and set `CRONO_GEN_ARCH` to `x86_64` for all
# variations of `x64` platforms, and to `x86` for all variations of `x86` 
# platforms.
# Set `CRONO_GEN_PLATFORM` to either `windows` or `linux`
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

# Dependency directories ______________________________________________________
set(CRONO_DEP_PKG_DIR           
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/driver)
set(CRONO_DEP_PKG_INC_DIR       ${CRONO_DEP_PKG_DIR}/include)

# Include directories paths ___________________________________________________
include_directories(${CRONO_TARGET_NAME} PRIVATE 
        ${PROJ_SRC_INDIR}/include
        # Include dependency folder
        ${CRONO_DEP_PKG_INC_DIR}
)

# Link to xtdc4_driver library ________________________________________
IF(CRONO_GEN_ARCH STREQUAL "x86" AND CRONO_GEN_PLATFORM STREQUAL "windows")
        add_library(xtdc4_driver SHARED IMPORTED GLOBAL)
        set_target_properties(xtdc4_driver PROPERTIES IMPORTED_IMPLIB 
                xtdc4_driver.lib)  
        set(CRONO_DEP_PKG_LIB_DIR     ${CRONO_DEP_PKG_DIR}/x86)
        set(CRONO_XTDC4_LIB_NAME      xtdc4_driver.lib)
ELSEIF(CRONO_GEN_ARCH STREQUAL "x86_64" AND CRONO_GEN_PLATFORM STREQUAL "windows")
        add_library(xtdc4_driver_64 SHARED IMPORTED GLOBAL)
        set_target_properties(xtdc4_driver_64 PROPERTIES IMPORTED_IMPLIB 
                xtdc4_driver_64.lib)  
        set(CRONO_DEP_PKG_LIB_DIR     ${CRONO_DEP_PKG_DIR}/x64)
        set(CRONO_XTDC4_LIB_NAME      xtdc4_driver_64.lib)
ENDIF()
link_directories(${CRONO_DEP_PKG_LIB_DIR})

# Set output directory_________________________________________________________
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CRONO_DEP_PKG_LIB_DIR})

# Validate that directories exist _____________________________________________
IF(     NOT EXISTS "${CRONO_DEP_PKG_LIB_DIR}" 
     OR NOT EXISTS "${CRONO_DEP_PKG_INC_DIR}"
) 
        message(FATAL_ERROR 
                "Crono: Please copy driver installation folder <xTDC4\driver> to the project root.")
ENDIF()
        
# Add the EXE ytarget  ________________________________________________________
add_executable(${CRONO_TARGET_NAME} 
        ${PROJ_SRC_INDIR}/src/xtdc4_user_guide_example.cpp)

# Windows-specific Configurations _____________________________________________
IF ( CRONO_GEN_PLATFORM  STREQUAL "windows")
        IF(         CRONO_GEN_ARCH STREQUAL "x86" 
                AND CRONO_GEN_PLATFORM STREQUAL "windows")
                target_link_libraries(${CRONO_TARGET_NAME} xtdc4_driver)
        ELSEIF(     CRONO_GEN_ARCH STREQUAL "x86_64" 
                AND CRONO_GEN_PLATFORM STREQUAL "windows")
                target_link_libraries(${CRONO_TARGET_NAME} xtdc4_driver_64)
        ENDIF()
# Linux-specific Configurations _______________________________________________
ELSEIF (CRONO_GEN_PLATFORM STREQUAL "linux") 
        # Compilation options _________________________________________________ 
        add_compile_options(-Wall $<$<CONFIG:Debug>:-g>)
        add_compile_definitions($<$<CONFIG:Debug>:CRONO_DEBUG_ENABLED>)
        if (NOT CMAKE_BUILD_TYPE)
                message(STATUS  
                        "Crono: assuming build type is `Release` as none was specified.")
                set(CMAKE_BUILD_TYPE Release)
        endif()

        # Rename the library with prefix `lib` for the linker to find it
        add_custom_command(TARGET ${CRONO_TARGET_NAME} PRE_BUILD 
                COMMAND "cp" ${CRONO_DEP_PKG_LIB_DIR}/xtdc4_driver.a 
                        ${CRONO_DEP_PKG_LIB_DIR}/libxtdc4_driver.a)

        # Link to xtdc4_driver library ________________________________________
        add_library(xtdc4_driver STATIC IMPORTED GLOBAL)
        set_target_properties(xtdc4_driver PROPERTIES IMPORTED_IMPLIB xtdc4_driver.a)  
        target_link_libraries(${CRONO_TARGET_NAME} xtdc4_driver.a)

        # Adjust .o files names  ______________________________________________
        # Remove .cpp from .o file name
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON) 
ENDIF()