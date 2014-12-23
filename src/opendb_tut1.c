/**
 * Summary: Simple database open/close
 * Create/Open a database, print a statement,
 * then close connection to it.
 *
 * Author: Hyunjin Chung
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define DBNAME "./wargame.db"

int main(int argc, char **argv)
{
    //1. open connection to db.
    sqlite3 * db = NULL;
    if( SQLITE_OK != sqlite3_open(DBNAME, &db)){
        printf("db open failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    //2. db connection is good
    printf("db open/create success..\n");

    //3. close connection to db.
    sqlite3_close(db);
    return 0;
}
