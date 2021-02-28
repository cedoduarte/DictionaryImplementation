#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>

/* Auxiliary functions */

DictionaryNode *dictionary_node_create(void *key, void *value, DictionaryNode *prev, DictionaryNode *next)
{
    DictionaryNode *node = NULL;
    node = (DictionaryNode *) malloc(sizeof(DictionaryNode));
    node->key = key;
    node->value = value;
    node->prev = prev;
    node->next = next;
    return node;
}

Dictionary *dictionary_create(unsigned size, DictionaryNode *end, DictionaryNode *begin)
{
    Dictionary *d = NULL;
    d = (Dictionary *) malloc(sizeof(Dictionary));
    d->size = size;
    d->end = end;
    d->begin = begin;
    return d;
}

DictionaryNode *dictionary_node_delete(DictionaryNode *node)
{
    DictionaryNode *next = NULL;
    if (node != NULL)
    {
        next = node->next;
        free(node);
        return next;
    }
    return NULL;
}

/* Dictionary API */

Dictionary *dictionary_new(void)
{
    return dictionary_create(0, NULL, NULL);
}

void dictionary_delete(Dictionary *d)
{
    DictionaryNode *node = NULL;
    if (d != NULL)
    {
        if (d->begin != NULL && d->end != NULL)
        {
            node = d->begin;
            while (node != NULL)
                node = dictionary_node_delete(node);
        }
        free(d);
    }
}

DictionaryNode *dictionary_push_front(Dictionary *d, void *key, void *value)
{
    if (d != NULL)
    {
        if (d->begin == NULL && d->end == NULL)
        {
            d->begin = dictionary_node_create(key, value, NULL, NULL);
            d->end = d->begin;
            d->size += 1;
            return d->end;
        }
        else
        {
            d->begin->prev = dictionary_node_create(key, value, NULL, d->begin);
            d->begin = d->begin->prev;
            d->size += 1;
            return d->begin;
        }
    }
    return NULL;
}

DictionaryNode *dictionary_push_back(Dictionary *d, void *key, void *value)
{
    if (d != NULL)
    {
        if (d->begin == NULL && d->end == NULL)
        {
            d->begin = dictionary_node_create(key, value, NULL, NULL);
            d->end = d->begin;
            d->size += 1;
            return d->end;
        }
        else
        {
            d->end->next = dictionary_node_create(key, value, d->end, NULL);
            d->end = d->end->next;
            d->size += 1;
            return d->end;
        }
    }
    return NULL;
}

DictionaryNode *dictionary_find_from_key(Dictionary *d, void *key)
{
    DictionaryNode *node = NULL;
    if (d != NULL)
    {
        node = d->begin;
        while (node != NULL)
        {
            if (node->key == key)
                return node;
            node = node->next;
        }
    }
    return NULL;
}

DictionaryNode *dictionary_remove_from_key(Dictionary *d, void *key)
{
    DictionaryNode *node = NULL;
    DictionaryNode *prev = NULL;
    DictionaryNode *next = NULL;
    if (d != NULL)
    {
        node = dictionary_find_from_key(d, key);
        if (node != NULL)
        {
            if (node == d->begin)
            {
                d->begin = dictionary_node_delete(d->begin);
                d->size -= 1;
                if (d->size == 1)
                    d->end = d->begin;
                return d->begin;
            }
            else if (node == d->end)
            {
                d->end = dictionary_node_delete(d->end);
                d->size -= 1;
                if (d->size == 1)
                    d->begin = d->end;
                return d->end;
            }
            else
            {
                prev = node->prev;
                next = dictionary_node_delete(node);
                d->size -= 1;
                if (prev != NULL)
                    prev->next = next;
                if (next != NULL)
                    next->prev = prev;
                return next;
            }
        }
    }
    return NULL;
}

void dictionary_for_each(Dictionary *d, void (*callback)(DictionaryNode *))
{
    DictionaryNode *node = NULL;
    if (d != NULL)
    {
        node = d->begin;
        while (node != NULL)
        {
            callback(node);
            node = node->next;
        }
    }
}
