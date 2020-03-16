find_program(CLANG_FORMAT_EXECUTABLE
  NAMES clang-format
  DOC "Clang-format executable"
)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ClangFormat DEFAULT_MSG CLANG_FORMAT_EXECUTABLE)
mark_as_advanced(CLANG_FORMAT_EXECUTABLE)
