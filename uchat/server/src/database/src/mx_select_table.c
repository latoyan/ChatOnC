#include "database.h"

static void mx_sel_tab_add (char *request);

t_sql_resp *mx_select_table(char const *name_db, char const *name_table, sqlite3 **db, t_table *table, char *condition, int columns) {
    int res_open = sqlite3_open(name_db, db);
    t_table *tmp = table;
    char *request = NULL;
    sqlite3_stmt *response = NULL;
    t_sql_resp *result = NULL;
    int step = 0;
    int row;
    char **tmp_arr = NULL;

    mx_stradd(&request, "SELECT ");
    if (!tmp)
        mx_stradd(&request, "*");
    else
        while(tmp) {
            mx_stradd(&request, tmp->name);
            if (tmp->next)
                mx_stradd(&request, ",");
            mx_stradd(&request, " ");
            tmp = tmp->next;
    }
    
    sqlite3_open(name_db, db);
    sqlite3_prepare_v2(*db, request, mx_strlen(request) + 1, &response, NULL);

    while(1) {
        step = sqlite3_step(response);
        tmp_arr = mx_create_char_arr(columns);
        if(step == SQLITE_ROW) {
            for (int i = 0; i < columns; i++) {
                sqlite3_column_bytes (response, i);
                tmp_arr[i] = (char*)sqlite3_column_text(response, i);
            }
            mx_push_sql_resp(&result, tmp_arr);
        }
        else if (step == SQLITE_DONE)
            break;
        //mx_push_sql_resp(&result, tmp_arr);
        //mx_del_strarr(&tmp_arr);
    }
    return result;
}

static void mx_sel_tab_add (char *request, name_table) {
    mx_stradd(&request, " FROM ");
    mx_stradd(&request, name_table);
    mx_stradd(&request, " ");
    mx_stradd(&request, condition);
    mx_stradd(&request, ";");
}
