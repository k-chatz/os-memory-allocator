/***********************************************************************************************************************
interface file	    : malloc.h
Author				: <Costas Chatzopoulos -1115201300202- 29/10/2017>
Purpose				: memory allocator
***********************************************************************************************************************/

#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H

/*Allocate SIZE bytes of memory.*/
void *mymalloc(size_t);

/* Free a block allocated by `mymalloc'*/
void myfree(void *);

void printPointer(void *ptr);

#endif //MALLOC_MALLOC_H
