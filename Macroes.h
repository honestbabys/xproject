#ifndef _COMMON_MACROES_H_
#define _COMMON_MACROES_H_
#if defined TRACE
#define TRACE(STR) printf("Filename %s Line %d tracing %s\r\n",__FILE__,__LINE__,STR);
#else
#define TRACE(STR)
#endif
#if defined DEBUG
#define DEBUG(...) printf("Filename %s Line %d debug ",__FILE__,__LINE__); \
                   printf(__VA_ARGS__); \
                   printf("\r\n");
#else
#define DEBUG(...)
#endif 
#endif 
