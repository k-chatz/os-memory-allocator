/***********************************************************************************************************************
Implementation file	    : hashtable.h
Author				    : <Costas Chatzopoulos -1115201300202- 29/10/2017>
Purpose			    	: hashtable structure
***********************************************************************************************************************/

#include <assert.h>
#include "hashtable.h"

typedef struct node *Node;

typedef struct list {
    Node start;
    Node current;
} *List;

struct node {
    Node previous, next;
    Pair pair;
};

Node createNode() {
    Node node = (Node) malloc(sizeof(struct node));
    if (node != NULL) {
        node->previous = NULL;
        node->next = NULL;
        return node;
    } else
        return NULL;
}

Node attachNode(List list, Node newNode) {
    assert(list != NULL);
    assert(newNode != NULL);
    if (newNode != NULL) {
        newNode->next = list->start;
        if (list->start != NULL)
            list->start->previous = newNode;
        list->start = newNode;
        list->current = newNode;
        return newNode;
    } else
        return NULL;
}

bool _existsList(List *list) {
    return *list != NULL;
}

void _createList(List *list) {
    assert(*list == NULL);
    *list = (List) malloc(sizeof(struct list));
    if ((*list) != NULL) {
        (*list)->start = NULL;
        (*list)->current = NULL;
    }
}

Pair _insertPair(List list, Pair *pair) {
    assert(list != NULL);
    assert(pair != NULL);
    Node newNode = createNode();
    if (newNode != NULL) {
        newNode = attachNode(list, newNode);
        if (newNode != NULL) {
            list->current = newNode;
            list->current->pair = *pair;
            return list->current->pair;
        }
    }
}

Pair _getFirstPair(List list) {
    assert(list != NULL);
    if (list->start != NULL)
        return list->start->pair;
    else
        return NULL;
}

Pair _getNextPair(List list) {
    assert(list != NULL);
    if (list->current->next != NULL) {
        list->current = list->current->next;
        return list->current->pair;
    }
    return NULL;
}

Pair _createNewHashPair(Key key, Value value, unsigned int index) {
    Pair pair = (Pair) malloc(sizeof(struct hashPair));
    pair->key = key;
    pair->value = value;
    pair->freed = false;
    pair->hash = index;
    return pair;
}

static List hashTable[HASH_SIZE];

unsigned int _hash(unsigned int key) {
    assert(key != NULL);
    return key % HASH_SIZE;
}

Pair hashSearch(Key key) {
    assert(key != NULL);
    Pair pair = NULL;
    unsigned int index = _hash((unsigned int) key);
    pair = _getFirstPair(hashTable[index]);
    if (pair != NULL) {
        if (pair->key != key) {
            do {
                pair = _getNextPair(hashTable[index]);
            } while (pair != NULL && pair->key != key);
        }
    }
    return pair;
}


void hashInsert(Key key, Value value) {
    assert(key != NULL);
    assert(value != NULL);
    Pair pair = NULL;
    unsigned int index = _hash((unsigned int) key);
    if (_existsList(&hashTable[index])) {
        pair = _getFirstPair(hashTable[index]);
        if (pair != NULL) {
            if (pair->key != key) {
                do {
                    pair = _getNextPair(hashTable[index]);
                } while (pair != NULL && pair->key != key);
            }
            if (pair != NULL) {
                pair->key = key;
                pair->value = value;
                pair->freed = false;
            }
            else{
                pair = _createNewHashPair(key, value, index);
                _insertPair(hashTable[index], &pair);
            }
        }
    } else {
        _createList(&hashTable[index]);
        pair = _createNewHashPair(key, value, index);
        _insertPair(hashTable[index], &pair);
    }
    //IT_PrintValue(stdout, value, key, index);
}
