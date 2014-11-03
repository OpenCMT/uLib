#if(ULIB_MACROS_CMAKE)
# return()
#endif()
#set(ULIB_MACROS_CMAKE 1)


function(include_guard var)
 if(${var})
  return()
 endif()
 set(${var} 1)
endfunction()
