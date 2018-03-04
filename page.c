/***********************************************************************************************************************
implementation file	: page.c
Author				: <Costas Chatzopoulos -1115201300202- 29/10/2017>
Purpose				: page management
***********************************************************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "page.h"
#include <limits.h>
#include <assert.h>

static void *block_start = NULL;    /*1MB Memory*/

static void *current_page = NULL;   /*Current Memory Block*/

static void *block_end = NULL;      /*End of block_start*/

static int bi;

bool _block_is_full() {
    return current_page + PAGE > block_end;
}

void _allocate_block() {
    bi = 0;
    block_start = (unsigned long) malloc(BLOCK);
    block_end = block_start + BLOCK;
    current_page = (void *) (((unsigned long) block_start - ((unsigned long) block_start % PAGE)) + PAGE);
    printf("Allocate block - Start: [%p]\tEnd: [%p]\tCurrent Page: [%p]\n", block_start, block_end, current_page);
}

void *_getPage() {
    if (block_start == NULL || _block_is_full())
        _allocate_block();
    void *page = current_page;
    ++bi;
    //printf("_getPage()\t[Page count= %d]\t[page = %p]\n", bi, current_page);
    current_page += PAGE;
    return page;
}

void _printBits(char *bytes) {
    assert(bytes != NULL);
    int i, j;
    unsigned int size = sizeof(char);
    unsigned int maxPow = (unsigned int) (1 << (size * 8 - 1));
    for (j = 0; j < 16; ++j) {
        char tmp;
        tmp = bytes[j];
        for (i = 0; i < size * 8; ++i) {
            printf("%u", tmp & maxPow ? 1 : 0);
            tmp = tmp << 1;
        }
        if (j < 15)
            printf(" ");
    }
}

void _toggleBit(struct Page *page, unsigned long segment) {
    assert(page != NULL);
    assert(segment <= page->segments);
    unsigned long bit = 129 - segment;
    const unsigned long position = ((bit - 1) / CHAR_BIT);
    bit %= 8;
    const unsigned long shift = (bit == 0) ? 0 : CHAR_BIT - bit;
    page->bits[position] = (char) (page->bits[position] ^ (0x1 << shift));
}

unsigned int _firstFreeSegment(struct Page *page) {
    unsigned int bit = 0, i = 0;
    char x = page->bits[15];
    if (page->level <= PAGE && page->level > SEGMENT_2048) {
        for (bit = page->segments; (x & 0x01) != 0; --bit)
            x = x << 1;
        return bit;
    } else if (page->level <= SEGMENT_2048 && page->level > SEGMENT_1024) {
        for (bit = page->segments; (x & 0x02) != 0; --bit)
            x = x << 1;
        return bit;
    } else if (page->level <= SEGMENT_1024 && page->level > SEGMENT_512) {
        for (bit = page->segments; (x & 0x08) != 0; --bit)
            x = x << 1;
        return bit;
    } else if (page->level <= SEGMENT_512 && page->level > SEGMENT_256) {
        for (bit = page->segments; (x & 0x80) != 0; --bit)
            x = x << 1;
        return bit;
    } else {
        for (i = (unsigned int) (512 / page->level); i > 0; --i) {
            x = page->bits[16 - i];
            bit = CHAR_BIT;
            while (1) {
                if (bit < 1)
                    break;
                if ((x & 0x80) == 0) {
                    return bit + (CHAR_BIT * (i - 1));
                }
                x = x << 1;
                bit--;
            }
        }
        return 0;
    }
}

struct Page *createPage(size_t level) {
    assert(level > 0);
    struct Page *page = (struct Page *) malloc(sizeof(struct Page));
    page->segment = _getPage();
    page->level = level;
    page->segments = (unsigned int) (PAGE / level);
    return page;
}

void *getSegment(struct Page *page) {
    assert(page != NULL);
    unsigned int n = _firstFreeSegment(page);
    if (!n)
        return NULL;
    else {
        _toggleBit(page, n);
        return page->segment + (page->level * (n - 1));
    }
}

void *freeSegment(struct Page *page, void *ptr) {
    unsigned long x = (unsigned long) ptr;
    x = x >> (page->segments + 1);
    unsigned long offset = (x % page->segments) + 1;
     _toggleBit(page, offset);
}

void IT_PrintValue(FILE *out, listItemType *data, void *pointer, int hash) {
    if (data != NULL) {
        printf("PAGE %d) %p - SEGMENT SIZE:[%d] SEGMENTS:[%d] [", bi, data->segment, (unsigned int) data->level,
               data->segments);
        _printBits(data->bits);
        printf("]\t[POINTER: %p - HASH: %d]\n", pointer, hash);
    } else
        printf("EMPTY PAGE!\n");
}
