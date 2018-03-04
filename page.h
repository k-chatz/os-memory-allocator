/***********************************************************************************************************************
interface file	    : page.c
Author				: <Costas Chatzopoulos -1115201300202- 29/10/2017>
Purpose				: page management
***********************************************************************************************************************/

#ifndef MALLOCATOR_PAGE_H
#define MALLOCATOR_PAGE_H

#include <stdio.h>

#define BLOCK 0x100000          /*1048576 Bytes (1MB)*/
#define SEGMENT_32 0x20         /*32 Bytes*/
#define SEGMENT_64 0x40         /*64 Bytes*/
#define SEGMENT_128 0x80        /*128 Bytes*/
#define SEGMENT_256 0x100       /*256 Bytes*/
#define SEGMENT_512 0x200       /*512 Bytes*/
#define SEGMENT_1024 0x400      /*1024 Bytes*/
#define SEGMENT_2048 0x800      /*2048 Bytes*/
#define PAGE 0x1000             /*4096 Bytes*/

typedef struct Page {
    size_t level;
    unsigned int segments;
    char bits[16];
    void *segment;
} listItemType;

struct Page *createPage(size_t level);

void *getSegment(struct Page *page);

void *freeSegment(struct Page *page, void *ptr);

void IT_PrintValue(FILE *out, listItemType *data, void * pointer, int hash);

#endif //MALLOCATOR_PAGE_H
