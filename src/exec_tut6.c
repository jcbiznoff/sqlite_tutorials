/*
 * Shows how to use sqlite3_exec() function.
 * Performance wise, avoid this call and use prepare/step/bind sequence instead.
 * sqlite3_exec is a wrapper for the above sequence anyway plus a possible overhead.
 * But it is convenient to use.
 *
 * Author: Hyunjin Chung
 * Reference:
 * http://stackoverflow.com/questions/1703203/in-sqlite-do-prepared-statements-really-improve-performance
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#define DBNAME "./wargame.db"

// 0. define callback as below
static int callback(void *data, int argc, char **argv, char **colName){
    int i;
    printf("%s\n", (const char*)data);
    for(i=0; i<argc; i++)
       printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
    printf("\n");
    return 0;
}

int main(int argc, char **argv){

    //1. open connection to db.
    sqlite3 * db = NULL;
    if( SQLITE_OK != sqlite3_open(DBNAME, &db)){
        printf("db open failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    //2. build a select query
    const char * selectquery = "SELECT * FROM USERINFO";
    const char * userdata = "Callback is executed";
    char * errMsg = 0;

    //3. execute sql
    if(SQLITE_OK != sqlite3_exec(
                        db,
                        selectquery,
                        callback,
                        (void*)userdata,
                        &errMsg
                    )){
        printf("error message is: %s\n", sqlite3_errmsg(db));
    }else
        printf("Successfully queried\n");

    //9. close db
    sqlite3_close(db);
    return 0;
}

