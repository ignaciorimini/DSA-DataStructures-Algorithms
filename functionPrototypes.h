#ifndef _FUNCTIONPROTOTYPES_
#define _FUNCTIONPROTOTYPES_

typedef int (*CompareFunction)(void* dato1, void* dato2);
typedef void* (*CopyFunction)(void* dato);
typedef void (*DestroyFunction)(void* dato);
typedef void (*VisitFunction)(void* dato);
typedef unsigned (*HashFunction)(void* dato);

#endif