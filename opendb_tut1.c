//include sqlite3
//open connection to db
//if error, exit program
//else print success message
//close connection to db
//exit program
//
//

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char **argv)
{
    //1. open connection to db
    sqlite3 * db= NULL;
    const char * dbName = "./jaygame.db";
    if( SQLITE_OK != sqlite3_open(dbName, &db)){
        printf("db open failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    //2. db connection is good
    //call prepare now
    printf("db open/create success..\b");

    sqlite3_close(db);
    return 0;
}
