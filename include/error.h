#ifndef ERROR_H
#define ERROR_H

#define FATAL_ERROR(CAUSE) fatal_error(__FILE__, __LINE__, #CAUSE)

void fatal_error(const char* file, int line, const char* causes);

enum errors { TYPE, ARITY, NAME, DIVISION_BY_ZERO, SYNTAXE, RUNTIME };

void error(enum errors type, const char* function, const char* explanation);

#endif
