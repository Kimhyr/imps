#include "table.h"

#include <stdio.h>

#define $ddo(PROC, ARGS)                                                       \
        do {                                                                   \
                PROC ARGS;                                                     \
                puts(#PROC #ARGS);                                             \
        } while (0)
#define $ddr(PROC, ARGS)                                                       \
        do {                                                                   \
                if (!PROC ARGS)                                                \
                        return 1;                                              \
                puts(#PROC #ARGS);                                             \
        } while (0)

int main() {
        printf("%lu\n", hash("pens", 8));
        struct table table;
        $ddo(initiate_table, (&table, 8));

        struct entry *entry1 = (struct entry *)malloc(sizeof(struct entry));
        char *key1 = (char *)malloc(5 * sizeof(char));
        key1[0] = 'p';
        key1[1] = 'o';
        key1[2] = 'o';
        key1[3] = 'p';
        key1[4] = '\0';
        $ddo(initiate_entry, (entry1, key1, 69));
        struct entry *entry2 = (struct entry *)malloc(sizeof(struct entry));
        char *key2 = (char *)malloc(5 * sizeof(char));
        key2[0] = 'p';
        key2[1] = 'e';
        key2[2] = 'n';
        key2[3] = 's';
        key2[4] = '\0';
        $ddo(initiate_entry, (entry2, key2, 420));

        $ddr(insert_table_entry, (&table, entry1));
        $ddr(insert_table_entry, (&table, entry2));
        $ddo(print_table, (&table));
        $ddr(delete_table_entry, (&table, "poop"));
        $ddo(print_table, (&table));
        $ddo(destroy_table, (&table));
        return 0;
}
