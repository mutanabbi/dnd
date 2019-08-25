#[=======================================================================[.rst:
FindReadline
------------

Try to find readline include dirs and libraries. The module provides
the following components:

- ``readline`` the main library
- ``histroy`` history library

Usage example:

.. code-block::cmake

    find_package(Readline COMPONENTS readline history)

    ...

    target_link_libraries(
        blah
        PUBLIC
            Readline::readline
            Readline::history
      )

Variables to Tune the Finder
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cmake:variable:: Readline_ROOT_DIR

    Specify alternative install prefix

.. cmake:variable:: Readline_INCLUDE_DIR

    Specify alternative headers install path

.. cmake:variable:: Readline_LIB_DIR

    Specify alternative librararies install path

#]=======================================================================]

if(NOT "readline" IN_LIST Readline_FIND_COMPONENTS)
    list(APPEND Readline_FIND_COMPONENTS readline)
endif()

function(_readline_find_component COMP INCLUDE_DIR_VAR LIB_VAR)
    find_path(
        _readline_includes
        NAMES readline/${COMP}.h
        ${_arg_INCLUDE_DIR_HINTS}
        PATHS
            ${Readline_INCLUDE_DIR}
            ${Readline_ROOT_DIR}/include
    )
    set(${INCLUDE_DIR_VAR} "${_readline_includes}" PARENT_SCOPE)
    find_library(
        _readline_lib
        NAMES ${COMP}
        ${_arg_LIB_DIR_HINTS}
        PATHS
            ${Readline_LIB_DIR}
            ${Readline_ROOT_DIR}/lib
    )
    set(${LIB_VAR} "${_readline_lib}" PARENT_SCOPE)
endfunction()

set(Readline_FOUND TRUE)
foreach(_comp IN LISTS Readline_FIND_COMPONENTS)
    if(_comp STREQUAL "readline" OR _comp STREQUAL "history")
        _readline_find_component(${_comp} _${_comp}_includes _${_comp}_lib)
        if(_${_comp}_includes AND _${_comp}_lib)
            set(Readline_${_comp}_FOUND TRUE)
            add_library(
                Readline::${_comp} IMPORTED UNKNOWN
              )
            set_target_properties(
                Readline::${_comp}
                PROPERTIES
                    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
                    INTERFACE_INCLUDE_DIRECTORIES ${_${_comp}_includes}
                    IMPORTED_LOCATION ${_${_comp}_lib}
              )
        else()
            set(Readline_${_comp}_FOUND FALSE)
            set(Readline_FOUND FALSE)
        endif()
    else()
        message(SEND_ERROR "Unknown component `${_comp}`")
    endif()
endforeach()

if(Readline_FOUND)
    try_run(
        _vcheck_result _compile_result
        "${CMAKE_BINARY_DIR}"
        "${CMAKE_CURRENT_LIST_DIR}/realine_version.c"
        LINK_LIBRARIES Readline::readline
        COMPILE_OUTPUT_VARIABLE zz
        RUN_OUTPUT_VARIABLE Readline_VERSION
      )
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    Readline
    FOUND_VAR Readline_FOUND
    VERSION_VAR Readline_VERSION
    REQUIRED_VARS Readline_FOUND
    HANDLE_COMPONENTS
  )
