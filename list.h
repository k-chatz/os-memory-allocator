/***********************************************************************************************************************
Interface file	        : list.h
Author				    : <Costas Chatzopoulos -1115201300202- 29/10/2017>
Purpose			    	: list structure
***********************************************************************************************************************/

#ifndef MALLOC_LIST_H
#define MALLOC_LIST_H

#include <stdbool.h>
#include "page.h"

typedef struct list *listPtr;

bool listExists(listPtr *list);

void listCreate(listPtr *list);

listItemType *listGetFirstData(listPtr list);

listItemType *listInsert(listPtr, listItemType *);

listItemType *listNext(listPtr);

listItemType *listPrevious(listPtr);

void listPrintContent(listPtr list, FILE *out);

#endif //MALLOC_LIST_H
