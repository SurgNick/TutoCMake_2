
#ifndef MYLIB_HPP
#define MYLIB_HPP

#if defined(_WIN32)
#  if defined(TUTO_EXPORTING_MYLIB)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

__declspec(noinline) int insaneMath(int);

#endif
