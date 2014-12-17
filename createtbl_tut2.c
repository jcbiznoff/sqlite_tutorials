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
//need for strlen
#include <string.h>

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

    //2. prepare statement
    const char * sqlCreateTbl = "CREATE TABLE IF NOT EXISTS USERINFO( \
                                 ID         INT     PRIMARY KEY     NOT NULL, \
                                 USER       TEXT                    NOT NULL, \
                                 STAGE      INT                     NOT NULL, \
                                 ITEM       TEXT                    NOT NULL, \
                                 RECORD     TEXT                    NOT NULL, \
                                 CHARACTER  TEXT                    NOT NULL, \
                                 RANK       INT                     NOT NULL \
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

    //3. step, and finalize
    if(NULL != ppStmt){
        if(SQLITE_DONE != sqlite3_step(ppStmt)){
            printf("step failed...\n");
            printf("error message is: %s\n", sqlite3_errmsg(db));
        }

        if(SQLITE_OK != sqlite3_finalize(ppStmt)){
            printf("finalize failed...\n");
            printf("error message is: %s\n", sqlite3_errmsg(db));
        }
    }

    printf("successfully created a USERINFO table\n");

    sqlite3_close(db);
    return 0;
}
