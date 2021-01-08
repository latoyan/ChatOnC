#include "database.h"

int mx_strarr_len(char **arr);

t_sql_resp *mx_create_sql_resp(char **data) {
    t_sql_resp *tmp = (t_sql_resp*)malloc(sizeof(t_sql_resp));
    int len = mx_strarr_len(data);
    
    tmp->data = mx_create_char_arr(len);
    for (int i = 0; data[i]; i++)
        tmp->data[i] = mx_strdup(data[i]);
    tmp->next = NULL;
    return tmp;
}

int mx_strarr_len(char **arr) {
    int len = 0;

    while(arr[len])
        len++;
    return len;
}
