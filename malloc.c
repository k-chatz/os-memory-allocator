/***********************************************************************************************************************
implementation file	: malloc.c
Author				: <Costas Chatzopoulos -1115201300202- 29/10/2017>
Purpose				: memory allocator
***********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "malloc.h"
#include "list.h"
#include "hashtable.h"

static listPtr level[8];

void *allocate(listPtr *list, size_t cbytes) {
    assert(cbytes > 0 && cbytes <= PAGE);
    void *pointer = NULL;
    struct Page *page = NULL;
    if (!listExists(list)) {
        listCreate(list);
        page = createPage(cbytes);
        listInsert(*list, page);
        pointer = getSegment(page);
    } else {
        page = listGetFirstData(*list);
        pointer = getSegment(page);
        if (pointer == NULL) {
            do {
                pointer = NULL;
                page = listNext(*list);
                if (page == NULL)
                    break;
                pointer = getSegment(page);
            } while (pointer == NULL);
            if (pointer == NULL) {
                page = createPage(cbytes);
                listInsert(*list, page);
                pointer = getSegment(page);
            }
        }
    }
    hashInsert(pointer, page);
    return pointer;
}

void *mymalloc(size_t cbytes) {
    assert(cbytes > 0);
    if (cbytes > PAGE) {
        return malloc(cbytes);                                      /*CASE OF SYSTEM MALLOC*/
    } else if (cbytes <= PAGE && cbytes > SEGMENT_2048) {
        return allocate(&level[7], PAGE);                           /*CASE OF 4096 BYTE ALLOCATE*/
    } else if (cbytes <= SEGMENT_2048 && cbytes > SEGMENT_1024) {
        return allocate(&level[6], SEGMENT_2048);                   /*CASE OF 2048 BYTE ALLOCATE*/
    } else if (cbytes <= SEGMENT_1024 && cbytes > SEGMENT_512) {
        return allocate(&level[5], SEGMENT_1024);                   /*CASE OF 1024 BYTE ALLOCATE*/
    } else if (cbytes <= SEGMENT_512 && cbytes > SEGMENT_256) {
        return allocate(&level[4], SEGMENT_512);                    /*CASE OF 512* BYTE ALLOCATE*/
    } else if (cbytes <= SEGMENT_256 && cbytes > SEGMENT_128) {
        return allocate(&level[3], SEGMENT_256);                    /*CASE OF 256 BYTE ALLOCATE*/
    } else if (cbytes <= SEGMENT_128 && cbytes > SEGMENT_64) {
        return allocate(&level[2], SEGMENT_128);                    /*CASE OF 128 BYTE ALLOCATE*/
    } else if (cbytes <= SEGMENT_64 && cbytes > SEGMENT_32) {
        return allocate(&level[1], SEGMENT_64);                     /*CASE OF 64 BYTE ALLOCATE*/
    } else if (cbytes <= SEGMENT_32) {
        return allocate(&level[0], SEGMENT_32);                     /*CASE OF 32 BYTE ALLOCATE*/
    }
}

void myfree(void *ptr) {
    assert(ptr != NULL);
    Pair pair = hashSearch(ptr);
    if (pair != NULL) {
        if (pair->freed) {
            fprintf(stderr, "ERROR! Double free for pointer: %p at page(%d) %p\n", pair->key,
                    (unsigned int) pair->value->level, pair->value->segment);
            exit(134);
        } else {
            pair->freed = true;
            freeSegment(pair->value, ptr);
        }
    } else
        free(ptr);
}

void printPointer(void *ptr) {
    assert(ptr != NULL);
    Pair pair = hashSearch(ptr);
    if (pair != NULL) {
        IT_PrintValue(stdout, pair->value, pair->key, pair->hash);
    }
}
