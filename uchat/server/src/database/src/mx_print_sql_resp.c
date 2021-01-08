#include "database.h"

void mx_print_sql_resp(t_sql_resp *resp) {
    t_sql_resp *tmp = resp;

    while(tmp) {
        mx_print_strarr(tmp->data, " | ");
        tmp = tmp->next;
    }
}
