#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include <util/dbg.h>
#include <stdlib.h>

#define mu_suite_start() char *message = NULL

#define mu_assert(test, message) if (!(test)) {\
	log_err(message); return message; }

#define mu_run_test(test) debug("\n-----%s", " " #test); \
	message = test(); tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
	if(argc)debug("----- RODANDO: %s", argv[0]);\
	printf("----\nRODANDO: %s\n", argv[0]);\
	char *result = name();\
	if (result != 0) {\
		printf("FALHOU: %s\n", result);\
	}\
	else {\
		printf("TODOS TESTES PASSARAM\n");\
	}\
	printf("Testes rodados: %d\n", tests_run);\
	exit(result != 0);\
}

int tests_run;
#endif
