##############################################################
## taken from NVIDIA's OptiX CMake/Macros.cmake
##############################################################
# Appends VAL to the string contained in STR
MACRO(APPEND_TO_STRING STR VAL)
  if (NOT "${ARGN}" STREQUAL "")
    message(SEND_ERROR "APPEND_TO_STRING takes only a single argument to append.  Offending args: ${ARGN}")
  endif()
  # You need to double ${} STR to get the value.  The first one gets
  # the variable, the second one gets the value.
  if (${STR})
    set(${STR} "${${STR}} ${VAL}")
  else()
    set(${STR} "${VAL}")
  endif()
ENDMACRO(APPEND_TO_STRING)
