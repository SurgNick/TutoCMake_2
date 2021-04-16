
#pragma once

// #include "TutoCMakeLib_export.h"

#ifdef TUTOCMAKELIB_STATIC_DEFINE
#  define TUTO_MYLIB_EXPORT
#  define TUTOCMAKELIB_NO_EXPORT
#else
#  ifndef TUTO_MYLIB_EXPORT
#    ifdef TutoCMakeLib_EXPORTS
        /* We are building this library */
#      define TUTO_MYLIB_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define TUTO_MYLIB_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef TUTOCMAKELIB_NO_EXPORT
#    define TUTOCMAKELIB_NO_EXPORT 
#  endif
#endif

#ifndef TUTOCMAKELIB_DEPRECATED
#  define TUTOCMAKELIB_DEPRECATED __declspec(deprecated)
#endif

#ifndef TUTOCMAKELIB_DEPRECATED_EXPORT
#  define TUTOCMAKELIB_DEPRECATED_EXPORT TUTO_MYLIB_EXPORT TUTOCMAKELIB_DEPRECATED
#endif

#ifndef TUTOCMAKELIB_DEPRECATED_NO_EXPORT
#  define TUTOCMAKELIB_DEPRECATED_NO_EXPORT TUTOCMAKELIB_NO_EXPORT TUTOCMAKELIB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TUTOCMAKELIB_NO_DEPRECATED
#    define TUTOCMAKELIB_NO_DEPRECATED
#  endif
#endif

/*TUTO_MYLIB_EXPORT */int insaneMath(int);
