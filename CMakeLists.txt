#
# Copyright 2016 WebAssembly Community Group participants
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.20)
project(WABT VERSION 1.0.23)

enable_testing()

include(GNUInstallDirs)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckCXXSourceCompiles)
include(CheckTypeSize)
include(CMakePackageConfigHelpers)

##
## Options
##

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(BUILD_LIBWASM "Build libwasm, which implements the wasm C API" ON)
option(BUILD_TESTING "Build testing for wabt" ON)
option(WABT_INCLUDE_PACKAGING "Include packaging rules for WABT" "${is_top_level}")
option(THREADS_PREFER_PTHREAD_FLAG "Use the -pthread flag when linking to Threads" ON)

set(WABT_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/WABT"
    CACHE STRING "Path to WABT CMake files")

if (EMSCRIPTEN)
  # Emscripten cannot build shared libraries, and libWasm is necessarily shared.
  set(BUILD_LIBWASM OFF)
endif ()

if (BUILD_TESTING)
  # Tests expect all binaries to be in the source directory... *facepalm*
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endif ()

##
## Generate compiler detection header
##

check_include_file("alloca.h" HAVE_ALLOCA_H)
check_include_file("unistd.h" HAVE_UNISTD_H)

check_symbol_exists(snprintf "stdio.h" HAVE_SNPRINTF)
check_symbol_exists(strcasecmp "strings.h" HAVE_STRCASECMP)
check_symbol_exists(ENABLE_VIRTUAL_TERMINAL_PROCESSING "windows.h" HAVE_WIN32_VT100)

check_type_size(ssize_t SSIZE_T)
check_type_size(size_t SIZEOF_SIZE_T)

string(COMPARE EQUAL "${CMAKE_CXX_BYTE_ORDER}" "BIG_ENDIAN" WABT_BIG_ENDIAN)

check_cxx_source_compiles([[int main() { try { return 0; } catch (...) { } }]] WITH_EXCEPTIONS)

# Helper function for setting a variable to 0 or 1 based on an if condition
function(condition VAR)
  if (${ARGN})
    set(${VAR} 1 PARENT_SCOPE)
  else ()
    set(${VAR} 0 PARENT_SCOPE)
  endif ()
endfunction()

condition(COMPILER_IS_CLANG
          NOT MSVC
          AND CMAKE_CXX_COMPILER_ID MATCHES "Clang"
          OR CMAKE_SYSTEM_NAME STREQUAL "Emscripten")

condition(COMPILER_IS_GNU
          CMAKE_C_COMPILER_ID STREQUAL "GNU")

condition(COMPILER_IS_MSVC MSVC)

configure_file(src/config.h.in config.h)

##
## WABT library
##

set(wabt_sources
    src/apply-names.h
    src/apply-names.cc
    src/binary.h
    src/binary.cc
    src/binary-reader.h
    src/binary-reader.cc
    src/binary-reader-ir.h
    src/binary-reader-ir.cc
    src/binary-reader-logging.h
    src/binary-reader-logging.cc
    src/binary-writer.h
    src/binary-writer.cc
    src/binary-writer-spec.h
    src/binary-writer-spec.cc
    src/binding-hash.h
    src/binding-hash.cc
    src/color.h
    src/color.cc
    src/common.h
    src/common.cc
    src/config.cc
    src/decompiler.h
    src/decompiler-ast.h
    src/decompiler-ls.h
    src/decompiler-naming.h
    src/decompiler.cc
    src/error-formatter.h
    src/error-formatter.cc
    src/expr-visitor.h
    src/expr-visitor.cc
    src/feature.h
    src/feature.cc
    src/filenames.h
    src/filenames.cc
    src/generate-names.h
    src/generate-names.cc
    src/hash-util.h
    src/hash-util.cc
    src/ir.h
    src/ir.cc
    src/ir-util.h
    src/ir-util.cc
    src/leb128.h
    src/leb128.cc
    src/lexer-source.h
    src/lexer-source.cc
    src/lexer-source-line-finder.h
    src/lexer-source-line-finder.cc
    src/literal.h
    src/literal.cc
    src/opcode.h
    src/opcode.cc
    src/opcode-code-table.h
    src/opcode-code-table.c
    src/option-parser.h
    src/option-parser.cc
    src/resolve-names.h
    src/resolve-names.cc
    src/shared-validator.h
    src/shared-validator.cc
    src/stream.h
    src/stream.cc
    src/string-view.h
    src/string-view.cc
    src/token.h
    src/token.cc
    src/tracing.h
    src/tracing.cc
    src/type.h
    src/type-checker.h
    src/type-checker.cc
    src/utf8.h
    src/utf8.cc
    src/validator.h
    src/validator.cc
    src/wast-lexer.h
    src/wast-lexer.cc
    src/wast-parser.h
    src/wast-parser.cc
    src/wat-writer.h
    src/wat-writer.cc

    ${CMAKE_CURRENT_BINARY_DIR}/config.h

    src/interp/binary-reader-interp.h
    src/interp/binary-reader-interp.cc
    src/interp/interp.h
    src/interp/interp.cc
    src/interp/interp-inl.h
    src/interp/interp-math.h
    src/interp/interp-util.h
    src/interp/interp-util.cc
    src/interp/istream.h
    src/interp/istream.cc
    )

add_library(wabt ${wabt_sources})
add_library(WABT::wabt ALIAS wabt)
target_include_directories(
  wabt
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
target_compile_features(wabt PUBLIC cxx_std_11)

##
## libwasm, which implements the wasm C API
##

# TODO: The code is written to prevent libwasm from being static. Can it be patched?
if (BUILD_LIBWASM)
  add_library(wasm SHARED ${wabt_sources} src/interp/interp-wasm-c-api.cc)
  add_library(WABT::wasm ALIAS wasm)
  target_include_directories(
    wasm
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/wasm-c-api/include>
  )
  target_compile_features(wasm PUBLIC cxx_std_11)
  set_property(TARGET wasm PROPERTY CXX_VISIBILITY_PRESET hidden)
  if (MSVC)
    target_compile_definitions(wasm PRIVATE "WASM_API_EXTERN=__declspec(dllexport)")
  else ()
    target_compile_definitions(wasm PRIVATE "WASM_API_EXTERN=__attribute__((visibility(\"default\")))")
  endif ()
endif ()

##
## wasm-rt-impl
##

if (NOT MSVC)
  # wasm2c/wasm-rt.h uses non-standard __attribute__((noreturn))
  add_library(wasm-rt-impl wasm2c/wasm-rt-impl.c wasm2c/wasm-rt-impl.h wasm2c/wasm-rt.h)
  add_library(WABT::wasm-rt-impl ALIAS wasm-rt-impl)
endif ()

##
## Tools
##

set(wabt_tools "")

macro(add_wabt_tool name)
  add_executable(${name} src/tools/${name}.cc)
  target_link_libraries(${name} PRIVATE WABT::wabt)
  list(APPEND wabt_tools "${name}")
endmacro()

add_wabt_tool(wat2wasm)
add_wabt_tool(wast2json)
add_wabt_tool(wasm2wat)
add_wabt_tool(wasm-interp)
add_wabt_tool(spectest-interp)
add_wabt_tool(wat-desugar)
add_wabt_tool(wasm-validate)
add_wabt_tool(wasm-strip)
add_wabt_tool(wasm-decompile)

add_wabt_tool(wasm2c)
target_sources(wasm2c PRIVATE src/c-writer.cc)

add_wabt_tool(wasm-opcodecnt)
target_sources(wasm-opcodecnt PRIVATE src/binary-reader-opcnt.cc)

add_wabt_tool(wasm-objdump)
target_sources(wasm-objdump PRIVATE src/binary-reader-objdump.cc)

##
## Tests
##

if (BUILD_TESTING)
  find_package(Python3 REQUIRED Interpreter)

  find_package(Threads REQUIRED)

  find_package(GTest REQUIRED)
  include(GoogleTest)

  # Test tools
  add_test(
    NAME run-tests
    COMMAND Python3::Interpreter ${WABT_SOURCE_DIR}/test/run-tests.py --bindir $<TARGET_FILE_DIR:wat2wasm>
    WORKING_DIRECTORY ${WABT_SOURCE_DIR}
  )

  # Test hexfloat
  add_executable(hexfloat_test src/literal.cc src/test-hexfloat.cc)
  target_link_libraries(hexfloat_test PRIVATE WABT::wabt GTest::gtest GTest::gtest_main)
  gtest_add_tests(TARGET hexfloat_test TEST_LIST hexfloat)
  set_tests_properties(${hexfloat} PROPERTIES LABELS "slow")

  # Unit tests
  add_executable(
    wabt-unittests
    src/test-binary-reader.cc
    src/test-circular-array.cc
    src/test-interp.cc
    src/test-intrusive-list.cc
    src/test-literal.cc
    src/test-option-parser.cc
    src/test-string-view.cc
    src/test-filenames.cc
    src/test-utf8.cc
    src/test-wast-parser.cc
  )
  target_link_libraries(wabt-unittests PRIVATE WABT::wabt GTest::gtest GTest::gtest_main)
  gtest_add_tests(TARGET wabt-unittests)

  # C API tests
  if (BUILD_LIBWASM)
    function(c_api_example NAME)
      set(exe "wasm-c-api-${NAME}")
      add_executable(${exe} third_party/wasm-c-api/example/${NAME}.c)
      target_link_libraries(${exe} PRIVATE WABT::wasm Threads::Threads)
      add_custom_command(
        TARGET ${exe} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${WABT_SOURCE_DIR}/third_party/wasm-c-api/example/${NAME}.wasm $<TARGET_FILE_DIR:${exe}>/
      )
    endfunction()

    c_api_example(callback)
    c_api_example(finalize)
    c_api_example(global)
    c_api_example(hello)
    c_api_example(hostref)
    c_api_example(multi)
    c_api_example(memory)
    c_api_example(reflect)
    c_api_example(serialize)
    c_api_example(start)
    c_api_example(table)
    c_api_example(trap)

    if (CMAKE_USE_PTHREADS_INIT)
      c_api_example(threads)
    endif ()

    add_test(
      NAME run-c-api-tests
      COMMAND Python3::Interpreter ${WABT_SOURCE_DIR}/test/run-c-api-examples.py --bindir $<TARGET_FILE_DIR:wat2wasm>
      WORKING_DIRECTORY ${WABT_SOURCE_DIR}
    )
  endif ()
endif ()

##
## Packaging
##

if (WABT_INCLUDE_PACKAGING)
  install(
    TARGETS ${wabt_tools}
    EXPORT WABT_Targets
    RUNTIME COMPONENT WABT_Runtime
  )

  set(libs "")
  foreach (lib IN ITEMS wabt wasm wasm-rt-impl)
    if (TARGET ${lib})
      list(APPEND libs "${lib}")
    endif ()
  endforeach ()

  install(
    TARGETS ${libs}
    EXPORT WABT_Targets
    RUNTIME COMPONENT WABT_Runtime
    LIBRARY COMPONENT WABT_Runtime
    NAMELINK_COMPONENT WABT_Development
    ARCHIVE COMPONENT WABT_Development
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  )

  install(
    DIRECTORY "${WABT_SOURCE_DIR}/src/" "${WABT_BINARY_DIR}/src/"
    TYPE INCLUDE
    COMPONENT WABT_Development
    FILES_MATCHING PATTERN "*.h"
  )

  install(
    EXPORT WABT_Targets
    DESTINATION "${WABT_INSTALL_CMAKEDIR}"
    NAMESPACE WABT::
    FILE WABTConfig.cmake
    COMPONENT WABT_Development
  )

  write_basic_package_version_file(
    WABTConfigVersion.cmake
    COMPATIBILITY SameMajorVersion
  )

  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/WABTConfigVersion.cmake"
    DESTINATION "${WABT_INSTALL_CMAKEDIR}"
    COMPONENT WABT_Development
  )

  if (UNIX)
    install(
      FILES
      man/spectest-interp.1
      man/wasm2c.1
      man/wasm2wat.1
      man/wasm-decompile.1
      man/wasm-interp.1
      man/wasm-objdump.1
      man/wasm-opcodecnt.1
      man/wasm-strip.1
      man/wasm-validate.1
      man/wast2json.1
      man/wat2wasm.1
      man/wat-desugar.1
      DESTINATION "${CMAKE_INSTALL_MANDIR}/man1"
    )
  endif ()
endif ()

##
## Emscripten
##

if (EMSCRIPTEN)
  add_executable(libwabt src/emscripten-helpers.cc)
  target_compile_options(libwabt PRIVATE -Wno-warn-absolute-paths)
  target_link_libraries(libwabt PRIVATE WABT::wabt)

  set(WABT_POST_JS "${WABT_SOURCE_DIR}/src/wabt.post.js")
  set(EMSCRIPTEN_EXPORTED_JSON "${WABT_SOURCE_DIR}/src/emscripten-exported.json")

  target_link_options(
    libwabt
    PRIVATE
    "SHELL:-s SINGLE_FILE"
    --post-js "${WABT_POST_JS}"
    "SHELL:-s EXPORTED_FUNCTIONS=@\"${EMSCRIPTEN_EXPORTED_JSON}\""
    "SHELL:-s RESERVED_FUNCTION_POINTERS=10"
    "SHELL:-s NO_EXIT_RUNTIME=1"
    "SHELL:-s ALLOW_MEMORY_GROWTH=1"
    "SHELL:-s MODULARIZE=1"
    "SHELL:-s EXPORT_NAME=WabtModule"
    "SHELL:-s WASM=0"
    -Oz
  )

  set_target_properties(libwabt PROPERTIES LINK_DEPENDS "${WABT_POST_JS};${EMSCRIPTEN_EXPORTED_JSON}")
endif ()
