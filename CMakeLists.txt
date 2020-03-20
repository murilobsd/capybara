cmake_minimum_required(VERSION 3.5)
project(capybara VERSION 0.0.1 LANGUAGES C)

### Add Cmake module to CMAKE_MODULE_PATH. ###
if(NOT CMAKE_MODULE_PATH)
  set(CMAKE_MODULE_PATH)
endif(NOT CMAKE_MODULE_PATH)
if(EXISTS ${CMAKE_SOURCE_DIR}/cmake)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
endif(EXISTS ${CMAKE_SOURCE_DIR}/cmake)
include(GNUInstallDirs)

### Add directories to the project. ###
add_subdirectory(src)

#if(EXISTS ${CMAKE_SOURCE_DIR}/prg)
#  add_subdirectory(prg)
#endif(EXISTS ${CMAKE_SOURCE_DIR}/prg)

if(EXISTS ${CMAKE_SOURCE_DIR}/test)
  ### Set Valgrind with leak-check=full. ###
  set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full -v")
  enable_testing()
  include(CTest)
  add_subdirectory(test)
endif(EXISTS ${CMAKE_SOURCE_DIR}/test)

if(EXISTS ${CMAKE_SOURCE_DIR}/docs)
  add_subdirectory(docs)
endif(EXISTS ${CMAKE_SOURCE_DIR}/docs)

### Create a TGZ package of the library. ###
set(CPACK_GENERATOR TGZ)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_VERBATIM_VARIABLES    YES)
if(EXISTS ${CMAKE_SOURCE_DIR}/LICENSE)
  set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
endif(EXISTS ${CMAKE_SOURCE_DIR}/LICENSE)
if(EXISTS ${CMAKE_SOURCE_DIR}/README.md)
  set(CPACK_RESOURCE_FILE_README  ${CMAKE_SOURCE_DIR}/README.md)
endif(EXISTS ${CMAKE_SOURCE_DIR}/README.md)
include(CPack)

### Indentation with clang-format. ###
option(CLANGFORMAT OFF)
set(EXCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/cmake
  ${CMAKE_SOURCE_DIR}/docs
  ${CMAKE_SOURCE_DIR}/test/unity
  ${CMAKE_BINARY_DIR}
)
if(CLANGFORMAT)
  find_package(ClangFormat)
  if(ClangFormat_FOUND)
    file(GLOB_RECURSE ALL_SRC *.c *.h *.h.in)
    foreach(ISRC ${ALL_SRC})
      foreach(IDIR ${EXCLUDE_DIR})
        string(FIND ${ISRC} ${IDIR} EXCLUDE_DIR_FOUND)
        if(NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
          list(REMOVE_ITEM ALL_SRC ${ISRC})
        endif(NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
      endforeach(IDIR ${EXCLUDE_DIR})
    endforeach(ISRC ${ALL_SRC})

    foreach(ISRC ${ALL_SRC})
      message(STATUS ${ISRC})
    endforeach(ISRC ${ALL_SRC})

    add_custom_target(
      clangformat
      COMMAND ${CLANG_FORMAT_EXECUTABLE} -style=file -i ${ALL_SRC}
      COMMENT "Indenting all source files"
    )
  else(ClangFormat_FOUND)
    message(STATUS "Clang-format need to be installed to indent source files")
  endif(ClangFormat_FOUND)
endif(CLANGFORMAT)
