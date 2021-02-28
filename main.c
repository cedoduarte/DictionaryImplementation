#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(DictionaryNode *node)
{
    const char *key = (const char *) node->key;
    const char *value = (const char *) node->value;
    printf("%s => %s\n", key, value);
}

int main(void)
{
    Dictionary *d = dictionary_new();

    dictionary_push_back(d, "1", "domingo");
    dictionary_push_back(d, "2", "lunes");
    dictionary_push_back(d, "3", "martes");
    dictionary_push_back(d, "4", "miercoles");
    DictionaryNode *n1 = dictionary_push_front(d, "-1", "minus one");
    dictionary_push_back(d, "5", "jueves");
    dictionary_push_back(d, "6", "viernes");
    dictionary_push_back(d, "7", "sabado");
    DictionaryNode *n2 = dictionary_push_front(d, "0", "zero");

    dictionary_for_each(d, print);

    printf("\n");

    DictionaryNode *a = dictionary_find_from_key(d, n1->key);
    DictionaryNode *b = dictionary_find_from_key(d, n2->key);
    printf("a->key = %s\n", (const char *)a->key);
    printf("b->key = %s\n", (const char *)b->key);

    dictionary_remove_from_key(d, n1->key);
    dictionary_remove_from_key(d, n2->key);

    printf("\n");

    dictionary_for_each(d, print);

    dictionary_delete(d);
    return 0;
}
