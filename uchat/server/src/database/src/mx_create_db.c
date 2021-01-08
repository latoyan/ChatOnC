#include "database.h"

static void mx_create_db(char const *name_db) {
    int fd = open(name_db, O_WRONLY | O_CREAT | O_TRUNC, 0600);

    if (fd) {
        printf("Database %s is create!\n", name_db);
    }
    else
        printf("ERROR FD\n");
    close(fd);
}
