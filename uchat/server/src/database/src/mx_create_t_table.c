#include "database.h"

t_table *mx_create_t_table(char *name, char *params, char *type) {
    t_table *table = (t_table*)malloc(sizeof(t_table));

    table->name = name;
    table->params = params;
    table->type = type;
    table->next = NULL;
    table->data = NULL;
    return table;
}
