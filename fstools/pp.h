#ifndef FSTOOLS_PP_H
#define FSTOOLS_PP_H 1

#ifdef __GNUC__
#define FST_PACK(decl) decl __attribute__((packed))
#endif

#ifdef _MSC_VER
#define FST_PACK(decl) __pragma(pack(push, 1)) decl __pragma(pack(pop))
#endif

#ifndef FST_PACK
#error unsupported compiler
#endif

#endif