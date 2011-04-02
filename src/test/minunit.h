/* http://www.jera.com/techinfo/jtns/jtn002.html */
#ifndef _MINUNIT_H
#define _MINUNIT_H

#include <stdio.h>
#include <string.h>

extern int tests_run;

#define mu_assert(assertion) do { ++tests_run; printf("%s:%d: %s: %s\n", __FILE__, __LINE__, assertion ? "success" : "fail", __func__); if (!assertion) return 1; } while (0)
#define mu_run_test(test) do { int msg = test(); if (msg) return 1; } while (0)

#endif /* _MINUNIT_H */

