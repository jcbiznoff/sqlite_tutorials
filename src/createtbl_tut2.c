/**
 * Summary: Creating a table called USERINFO
 * Create a userinfo table if it does not exist.
 *
 * Author: Hyunjin Chung
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

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

    //2. prepare statement
    const char * sqlCreateTbl = "CREATE TABLE IF NOT EXISTS USERINFO( \
                                 ID        INT   PRIMARY KEY NOT NULL, \
                                 USER      TEXT              NOT NULL, \
                                 STAGE     INT               NOT NULL, \
                                 ITEM      TEXT              NOT NULL, \
                                 RECORD    TEXT              NOT NULL, \
                                 CHARACTER TEXT              NOT NULL, \
                                 RANK      INT               NOT NULL \
                                 );"; //careful about semicolon. also "if not exists" is important. otherwise error
    int sqlCreateTblLen = strlen(sqlCreateTbl) + 1;
    sqlite3_stmt *ppStmt = NULL;
    const char **pzTail = NULL;

    if(SQLITE_OK != sqlite3_prepare_v2(
                                db,
                                sqlCreateTbl,
                                sqlCreateTblLen,
                                &ppStmt,
                                pzTail)){
        printf("preparing statement failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
    }

    //3. step and finalize
    if(NULL != ppStmt){
        if(SQLITE_DONE != sqlite3_step(ppStmt)){
            printf("step failed...\n");
            printf("error message is: %s\n", sqlite3_errmsg(db));
        }else{
            printf("create table success!\n");
        }

        if(SQLITE_OK != sqlite3_finalize(ppStmt)){
            printf("finalize failed...\n");
            printf("error message is: %s\n", sqlite3_errmsg(db));
        }
    }

    //3. close connection to db.
    sqlite3_close(db);
    return 0;
}
