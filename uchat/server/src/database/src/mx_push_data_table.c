#include "database.h"

void mx_push_data_table(t_table **table, char **datas) {
    t_table *tmp = *table;
    int i = 0;

    while(tmp) {
        mx_strdel(&tmp->data);
        tmp->data = datas[i];
        tmp = tmp->next;
        i++;
    }
}
