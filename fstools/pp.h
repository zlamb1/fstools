#ifndef FSTOOLS_PP_H
#define FSTOOLS_PP_H 1

#ifdef __GNUC__
#define _packed(decl) decl __attribute__((packed))
#endif

#ifdef _MSC_VER
#define _packed(decl) __pragma(pack(push, 1)) decl __pragma(pack(pop))
#endif

#ifndef _packed
#error Unsupported Compiler
#endif

#endif