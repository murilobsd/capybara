### Add the source/headers of your library. ###
set(LIB_SRC
  serie_int32.c
  utils.c
  error.c
)


### Get the current working branch. ###
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

### Get the latest abbreviated commit hash of the working branch. ###
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

### Version configuration. ###
configure_file(${CMAKE_SOURCE_DIR}/src/version.h.in
  ${PROJECT_BINARY_DIR}/version.h
)

#### Add source to the library. ####
add_library(${PROJECT_NAME} ${LIB_SRC})

#### Include the headers. ####
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
)

### Add compile options to the target of the library. ###
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
target_compile_options(${PROJECT_NAME} PRIVATE -Wextra)
target_compile_options(${PROJECT_NAME} PRIVATE -pedantic)
set_property(TARGET    ${PROJECT_NAME} PROPERTY C_STANDARD 90)

#### Define version for the library name. ####
set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION   ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

#### Install the library. ####
install(TARGETS ${PROJECT_NAME} EXPORT "${PROJECT_NAME}-targets"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#### Install the headers and other stuffs. ###
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
if(EXISTS ${CMAKE_SOURCE_DIR}/README.md)
  install(FILES ${CMAKE_SOURCE_DIR}/README.md
    DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif()
if(EXISTS ${CMAKE_SOURCE_DIR}/LICENSE)
  install(FILES ${CMAKE_SOURCE_DIR}/LICENSE
    DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif()

### Install the library targets to be usable by other projects. ###
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
install(
  EXPORT      "${PROJECT_NAME}-targets"
  FILE        "${PROJECT_NAME}-targets.cmake"
  DESTINATION ${INSTALL_CONFIGDIR}
)
include(CMakePackageConfigHelpers)
file(WRITE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  "include(\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-targets.cmake)
  set(${PROJECT_NAME}_FOUND TRUE)"
)
write_basic_package_version_file(
   "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
   VERSION ${PROJECT_VERSION}
   COMPATIBILITY SameMajorVersion
)
install(FILES
   "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
   "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
   DESTINATION ${INSTALL_CONFIGDIR})
