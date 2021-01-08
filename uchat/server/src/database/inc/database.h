typedef struct s_names_db_lib {
    char const *name_db;
    char const *name_table;
    sqlite3 **db;
} t_names_db_lib;

typedef struct s_sql_resp {
    char **data;
    struct s_sql_resp *next;
} t_sql_resp;

typedef struct s_table {
    char *name;
    char *params;
    char *type;
    char *data;
    struct s_table *next;
} t_table;


