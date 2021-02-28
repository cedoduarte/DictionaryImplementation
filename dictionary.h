#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct Dictionary Dictionary;
typedef struct DictionaryNode DictionaryNode;

struct DictionaryNode
{
    void *key;
    void *value;
    DictionaryNode *prev;
    DictionaryNode *next;
};

struct Dictionary
{
    unsigned size;
    DictionaryNode *end;
    DictionaryNode *begin;
};

#ifdef __cplusplus
extern "C"
{
#endif

/* Auxiliary functions */
DictionaryNode *dictionary_node_create(void *key, void *value, DictionaryNode *prev, DictionaryNode *next);
Dictionary *dictionary_create(unsigned size, DictionaryNode *end, DictionaryNode *begin);
DictionaryNode *dictionary_node_delete(DictionaryNode *node);

/* Dictionary API */
Dictionary *dictionary_new(void);
void dictionary_delete(Dictionary *d);
DictionaryNode *dictionary_push_front(Dictionary *d, void *key, void *value);
DictionaryNode *dictionary_push_back(Dictionary *d, void *key, void *value);
DictionaryNode *dictionary_find_from_key(Dictionary *d, void *key);
DictionaryNode *dictionary_remove_from_key(Dictionary *d, void *key);
void dictionary_for_each(Dictionary *d, void (*callback)(DictionaryNode *));

#ifdef __cplusplus
}
#endif

#endif // DICTIONARY_H
