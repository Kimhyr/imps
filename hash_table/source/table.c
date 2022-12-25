#include "table.h"

#include <stdio.h>
#include <string.h>

void initiate_entry(struct entry *entry, char *key, int value) {
        entry->key = key;
        entry->value = value;
        entry->next = NULL;
}

void destroy_entry(struct entry *entry) {
        free(entry->key);
}

void initiate_table(struct table *table, size_t size) {
        table->size = size;
        table->entries = (struct entry **)calloc(size, sizeof(struct entry *));
}

void destroy_table(struct table *table) {
        for (size_t i = 0; i < table->size; ++i) {
                struct entry *root = table->entries[i];
                if (!root)
                        continue;
                do {
                        destroy_entry(root);
                        struct entry *entry = root->next;
                        free(root);
                        root = entry;
                } while (root);
        }
        free(table->entries);
}

bool insert_table_entry(struct table *table, struct entry *entry) {
        struct entry **node = &table->entries[hash(entry->key, table->size)];
        for (; *node; node = &(*node)->next)
                if (strcmp((*node)->key, entry->key) == 0)
                        return false;
        *node = entry;
        return true;
}

bool delete_table_entry(struct table *table, const char *key) {
        struct entry **target = &table->entries[hash(key, table->size)];
        struct entry *prev = NULL;
        for (;;) {
                if (!target)
                        return false;
                if (strcmp((*target)->key, key) == 0)
                        break;
                prev = *target;
                target = &(*target)->next;
        }
        destroy_entry(*target);
        void **mlock = (void **)*target;
        if (prev)
                prev->next = (*target)->next;
        else
                *target = (*target)->next;
        free(mlock);
        return true;
}

struct entry *get_table_entry(struct table *table, const char *key) {
        struct entry *entry = table->entries[hash(key, table->size)];
        for (; entry; entry = entry->next)
                break;
        return entry;
}

void print_table(struct table *table) {
        for (size_t i = 0; i < table->size; ++i) {
                struct entry *curr = table->entries[i];
                if (!curr) {
                        printf("$:entry %lu NULL\n", i);
                        continue;
                }
                do
                        printf("$:entry %lu %s %i\n", i, curr->key,
                               curr->value);
                while ((curr = curr->next));
        }
}

size_t hash(const char *key, size_t size) {
        size_t result = 0;
        while (*key++)
                result += *key;
        return result % size;
}
