#include "database.h"

static char *mx_request_db(t_table *tmp, char *request);

void mx_create_table(t_names_db_lib lib_db, t_table *table) {
    int res = sqlite3_open(lib_db.name_db, lib_db.db);
    char *err_msg = 0;
    t_table *tmp = table;
    char *request = mx_strjoin("CREATE TABLE ", lib_db.name_table);

    request = mx_request_db(tmp, request);
    if (res!= SQLITE_OK)
        mx_print_error("Cannot open database", 1, true);
    else
        res = sqlite3_exec(*lib_db.db, request, 0, 0, &err_msg);
    if (res != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(*lib_db.db);
        return;
    }
    sqlite3_close(*lib_db.db);
}

static char *mx_request_db(t_table *tmp, char *request) {
    mx_stradd(&request, " (");
    while(tmp) {
        mx_stradd(&request, tmp->name);
        mx_stradd(&request, " ");
        mx_stradd(&request, tmp->type);
        mx_stradd(&request, " ");
        mx_stradd(&request, tmp->params);
        if (tmp->next)
            mx_stradd(&request, ", ");
        tmp = tmp->next;
    }
    mx_stradd(&request, ");");
    return request;
}
