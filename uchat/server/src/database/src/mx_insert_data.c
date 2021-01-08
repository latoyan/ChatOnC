#include "database.h"

static char *mx_request_db2(char *request, t_table *tmp, t_table *table);
static void mx_cycle_st(char *request, t_table *tmp);
static void mx_cycle_sec(char *request, t_table *tmp);

void mx_insert_data(t_names_db_lib lib_db, t_table *table) {
    int res = sqlite3_open(lib_db.name_db, lib_db.db);
    char *err_msg = 0;

    t_table *tmp = table;
    char *request = mx_strjoin("INSERT INTO ", lib_db.name_table);

    request = mx_request_db2(request, tmp, table);
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

static char *mx_request_db2(char *request, t_table *tmp, t_table *table) {
    mx_stradd(&request, " (");
    while(tmp)
        mx_cycle_st(request, tmp);
    mx_stradd(&request, ") VALUES (");
    tmp = table;
    while(tmp)
        mx_cycle_sec(request, tmp);
    mx_stradd(&request, ");");
    return request;
}

static void mx_cycle_st(char *request, t_table *tmp) {
    mx_stradd(&request, tmp->name);
    if (tmp->next)
        mx_stradd(&request, ", ");
    tmp = tmp->next;
}

static void mx_cycle_sec(char *request, t_table *tmp) {
    if (!mx_strcmp("TEXT", tmp->type))
        mx_stradd(&request, "\'");
    mx_stradd(&request, tmp->data);
    if (!mx_strcmp("TEXT", tmp->type))
        mx_stradd(&request, "\'");
    if (tmp->next)
        mx_stradd(&request, ", ");
    tmp = tmp->next;
}
