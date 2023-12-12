/**
 * \file exports.h
 * @author evo (kok.in@yahoo.com) https://github.com/evo-i
 * \brief export functions.
 * \version 0.1
 * \date 2023-12-12
 *
 * Copyright © 2023 evo-i ({author}) https://github.com/evo-i
 *
 */

#ifndef KODIK_EXPORTS_H
#define KODIK_EXPORTS_H 1

#if (defined _WIN32 || defined __CYGWIN__) && !defined(__GNUC__)
  #define KODIK_HELPER_DLL_IMPORT __declspec(dllimport)
  #define KODIK_HELPER_DLL_EXPORT __declspec(dllexport)
  #define KODIK_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define KODIK_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define KODIK_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define KODIK_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define KODIK_HELPER_DLL_IMPORT
    #define KODIK_HELPER_DLL_EXPORT
    #define KODIK_HELPER_DLL_LOCAL
  #endif
#endif

#ifdef KODIK_DLL
  #ifdef KODIK_DLL_EXPORTS
    #define KODIK_API KODIK_HELPER_DLL_EXPORT
  #else
    #define KODIK_API KODIK_HELPER_DLL_IMPORT
  #endif /* KODIK_DLL_EXPORTS */
  #define KODIK_LOCAL KODIK_HELPER_DLL_LOCAL
#else /* KODIK_DLL is not defined: this means KODIK is a static lib. */
  #define KODIK_API
  #define KODIK_LOCAL
#endif /* KODIK_DLL */

#endif /* KODIK_EXPORTS_H */
