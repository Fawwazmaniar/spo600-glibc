/* Test lgamma functions do not set signgam for -ffinite-math-only for ISO C.
   Copyright (C) 2015-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#undef _LIBC
#undef __LIBC_INTERNAL_MATH_INLINES
#undef _GNU_SOURCE
#undef _Mlong_double_
#define _ISOMAC

#include <math.h>
#include <stdio.h>

int signgam;

#define RUN_TESTS(FUNC, TYPE)					\
  do								\
    {								\
      volatile TYPE a, b, c __attribute__ ((unused));		\
      a = 0.5;							\
      b = -0.5;							\
      signgam = 123;						\
      c = FUNC (a);						\
      if (signgam == 123)					\
	puts ("PASS: " #FUNC " (0.5) setting signgam");		\
      else							\
	{							\
	  puts ("FAIL: " #FUNC " (0.5) setting signgam");	\
	  result = 1;						\
	}							\
      signgam = 123;						\
      c = FUNC (b);						\
      if (signgam == 123)					\
	puts ("PASS: " #FUNC " (-0.5) setting signgam");	\
      else							\
	{							\
	  puts ("FAIL: " #FUNC " (-0.5) setting signgam");	\
	  result = 1;						\
	}							\
    }								\
  while (0)

int
main (void)
{
  int result = 0;
  RUN_TESTS (lgammaf, float);
  RUN_TESTS (lgamma, double);
#ifndef NO_LONG_DOUBLE
  RUN_TESTS (lgammal, long double);
#endif
  return result;
}
