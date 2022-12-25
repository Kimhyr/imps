#ifndef _TABLE_H
#define _TABLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct entry {
        char *key;
        int value;
        struct entry *next;
};

void initiate_entry(struct entry *entry, char *key, int value);
void destroy_entry(struct entry *entry);

struct table {
        size_t size;
        struct entry **entries;
};

void initiate_table(struct table *table, size_t size);
void destroy_table(struct table *table);
bool insert_table_entry(struct table *table, struct entry *entry);
bool delete_table_entry(struct table *table, const char *key);
struct entry *get_table_entry(struct table *table, const char *key);
void print_table(struct table *table);

size_t hash(const char *key, size_t size);

#endif // _TABLE_H
