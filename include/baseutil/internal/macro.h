#ifndef BASEUTIL_INCLUDE_INTERNAL_MACRO_H_
#define BASEUTIL_INCLUDE_INTERNAL_MACRO_H_

#ifdef _MSC_VER
# if BASEUTIL_LINKED_AS_SHARED_LIBRARY
#  define BASEUTIL_API_ __declspec(dllimport)
# elif BUILD_SHARED_LIBS
#  define BASEUTIL_API_ __declspec(dllexport)
# endif
#elif __GNUC__ >= 4 || defined(__clang__)
# define BASEUTIL_API_ __attribute__((visibility ("default")))
#endif // _MSC_VER

#ifndef BASEUTIL_API_
# define BASEUTIL_API_
#endif

#endif  // BASEUTIL_INCLUDE_INTERNAL_MACRO_H_
