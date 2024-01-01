# Install script for directory: C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/MorskiSmetar")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/mingw64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Jakob/Documents/CPP/MorskiSmetar/build/src/HenigmaEngine/src/fmt/libfmt.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/fmt" TYPE FILE FILES
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/args.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/chrono.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/color.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/compile.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/core.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/format.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/format-inl.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/os.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/ostream.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/printf.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/ranges.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/std.h"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/src/HenigmaEngine/src/fmt/include/fmt/xchar.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt" TYPE FILE FILES
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/build/src/HenigmaEngine/src/fmt/fmt-config.cmake"
    "C:/Users/Jakob/Documents/CPP/MorskiSmetar/build/src/HenigmaEngine/src/fmt/fmt-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets.cmake"
         "C:/Users/Jakob/Documents/CPP/MorskiSmetar/build/src/HenigmaEngine/src/fmt/CMakeFiles/Export/b834597d9b1628ff12ae4314c3a2e4b8/fmt-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt" TYPE FILE FILES "C:/Users/Jakob/Documents/CPP/MorskiSmetar/build/src/HenigmaEngine/src/fmt/CMakeFiles/Export/b834597d9b1628ff12ae4314c3a2e4b8/fmt-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt" TYPE FILE FILES "C:/Users/Jakob/Documents/CPP/MorskiSmetar/build/src/HenigmaEngine/src/fmt/CMakeFiles/Export/b834597d9b1628ff12ae4314c3a2e4b8/fmt-targets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Jakob/Documents/CPP/MorskiSmetar/build/src/HenigmaEngine/src/fmt/fmt.pc")
endif()

