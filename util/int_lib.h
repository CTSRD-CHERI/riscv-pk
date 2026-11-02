// Stripped-down version of LLVM's compiler-rt int_lib.h

//===-- int_lib.h - configuration header for compiler-rt  -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is not part of the interface of this library.
//
// This file defines various standard types, most importantly a number of unions
// used to access parts of larger types.
//
//===----------------------------------------------------------------------===//
#include <stdint.h>

#define CHAR_BIT __CHAR_BIT__

typedef int32_t si_int;
typedef uint32_t su_int;
#define clzsi __builtin_clz
#define ctzsi __builtin_ctz
#if __SIZEOF_INT__ != 4
#error could not determine appropriate clzsi macro for this system
#endif
typedef  int64_t di_int;
typedef uint64_t du_int;

typedef union {
  di_int all;
  struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    su_int low;
    si_int high;
#else
    si_int high;
    su_int low;
#endif // __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  } s;
} dwords;

typedef union {
  du_int all;
  struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    su_int low;
    su_int high;
#else
    su_int high;
    su_int low;
#endif // __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  } s;
} udwords;

#define COMPILER_RT_ABI __attribute__((visibility("hidden")))

COMPILER_RT_ABI di_int __divdi3(di_int a, di_int b);
COMPILER_RT_ABI si_int __divsi3(si_int a, si_int b);
COMPILER_RT_ABI su_int __udivsi3(su_int n, su_int d);

COMPILER_RT_ABI su_int __udivmodsi4(su_int a, su_int b, su_int *rem);
COMPILER_RT_ABI du_int __udivmoddi4(du_int a, du_int b, du_int *rem);
