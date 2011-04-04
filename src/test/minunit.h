/* http://www.jera.com/techinfo/jtns/jtn002.html */
#ifndef _MINUNIT_H
#define _MINUNIT_H

#include <stdio.h>

extern int tests_run;

#define mu_assert(test_passed)\
do {\
  ++tests_run;\
  printf("%s:%d: %s: %s\n", __FILE__, __LINE__, test_passed ? "success" : "fail", __func__);\
  return test_passed;\
} while(0);

#define mu_run_test(test) do { if (!test()) return 1; } while (0)

#endif /* _MINUNIT_H */

