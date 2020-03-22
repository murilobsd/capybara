set(TEST_SRC
  test_serie_int8.c
  test_serie_int32.c
  test_error.c
)


### Build unity. ###
add_library(unity STATIC unity/src/unity.c)
target_include_directories(unity PUBLIC unity/src)
add_compile_definitions(UNITY_INCLUDE_DOUBLE)
add_compile_definitions(UNITY_DOUBLE_PRECISION=0.001f)

### Build each test. ###
foreach(ISRC ${TEST_SRC})
  get_filename_component(TEST_PRG ${ISRC} NAME_WE)
  add_executable(${TEST_PRG}_app ${ISRC})
  target_link_libraries(${TEST_PRG}_app ${PROJECT_NAME} unity)
  target_link_libraries(${TEST_PRG}_app ${PROJECT_NAME} m)
  add_test(NAME ${TEST_PRG} COMMAND ${TEST_PRG}_app)
endforeach(ISRC ${TEST_SRC})
