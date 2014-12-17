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

    //4. insert new values into table
    const char * sqlUserInfo = "INSERT INTO USERINFO(ID, USER, STAGE, ITEM, RECORD, CHARACTER, RANK) \
                                 VALUES (1, 'Hyunjin', 20, 'Big Sword', '1 hour', 4); \
                                 INSERT INTO USERINFO(ID, USER, STAGE, ITEM, RECORD, CHARACTER, RANK) \
                                 VALUES (2, 'JayBird', 10, 'SpearHead', '24 hours', 3); \
                                 INSERT INTO USERINFO(ID, USER, STAGE, ITEM, RECORD, CHARACTER, RANK) \
                                 VALUES (3, 'Constella', 1, 'MaceII', '4 hours', 2); \
                                 INSERT INTO USERINFO(ID, USER, STAGE, ITEM, RECORD, CHARACTER, RANK) \
                                 VALUES (4, 'Remez', 9, 'Big Sword II', '19 hours', 1); \
                                 INSERT INTO USERINFO(ID, USER, STAGE, ITEM, RECORD, CHARACTER, RANK) \
                                 VALUES (5, 'GOON', 5, 'AXE of doom', '11 hours', 5); \
                                 "; //mistake semicolon
    int sqlUserInfoLen = strlen(sqlUserInfo) + 1;
    sqlite3_stmt *ppStmt2 = NULL;
    const char **pzTail2 = NULL;

    //Exactly as above
    if(SQLITE_OK != sqlite3_prepare_v2(
                                db,
                                sqlUserInfo,    //this is different
                                sqlUserInfoLen, //this is different
                                &ppStmt2,       //this is different
                                pzTail2)){      //this is different

        printf("preparing statement failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
    }

    if(NULL != ppStmt2){
        if(SQLITE_DONE != sqlite3_step(ppStmt2)){ //different var
            printf("step failed...\n");
            printf("error message is: %s\n", sqlite3_errmsg(db));
        }

        if(SQLITE_OK != sqlite3_finalize(ppStmt2)){ //different var
            printf("finalize failed...\n");
            printf("error message is: %s\n", sqlite3_errmsg(db));
        }
    }

    printf("successfully inserted values to USERINFO table\n");

    sqlite3_close(db);
    return 0;
}
