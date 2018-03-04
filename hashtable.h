/***********************************************************************************************************************
Interface file	         : hashtable.h
Author				    : <Costas Chatzopoulos -1115201300202- 29/10/2017>
Purpose				    : hashtable structure
***********************************************************************************************************************/

#ifndef MALLOCATOR_HASHTABLE_H
#define MALLOCATOR_HASHTABLE_H

#include <stdbool.h>
#include <stdlib.h>
#include "page.h"

#define HASH_SIZE 4093

typedef void *Key;

typedef struct Page *Value;

typedef struct hashPair * Pair;

struct hashPair {
    Key key;
    Value value;
    bool freed;
    unsigned int hash;
};

void hashInsert(Key key, Value value);

Pair hashSearch(Key key);

#endif //MALLOCATOR_HASHTABLE_H
