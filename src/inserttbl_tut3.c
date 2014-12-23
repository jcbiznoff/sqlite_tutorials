/**
 * Summary: Insert data values into USERINFO table
 * Insert 5 different rows into USERINFO table
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
        }

        if(SQLITE_OK != sqlite3_finalize(ppStmt)){
            printf("finalize failed...\n");
            printf("error message is: %s\n", sqlite3_errmsg(db));
        }
    }

    //4. insert data values into table
    const char * sqlUserInfo = "INSERT INTO USERINFO(ID, USER, STAGE, ITEM, RECORD, CHARACTER, RANK) \
                                 VALUES (1, 'Hyunjin', 20, 'Big Sword', '1 hour', 'Goblin', 4), \
                                 (2, 'JayBird', 10, 'SpearHead', '24 hours', 'Sorcerer', 3), \
                                 (3, 'Constella', 1, 'MaceII', '4 hours', 'Bat', 2), \
                                 (4, 'Remez', 9, 'Big Sword II', '19 hours', 'human', 1), \
                                 (5, 'GOON', 5, 'AXE of doom', '11 hours', 'zombie', 5); \
                                 ";
    int sqlUserInfoLen = strlen(sqlUserInfo) + 1;
    sqlite3_stmt *ppStmt2 = NULL;
    const char **pzTail2 = NULL;

    //5. preapre, step, and finalize
    if(SQLITE_OK != sqlite3_prepare_v2(
                                db,
                                sqlUserInfo,    //use new insert string
                                sqlUserInfoLen, //match max length
                                &ppStmt2,       //use new string
                                pzTail2)){      //use new pointer

        printf("preparing statement failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
    }

    if(NULL != ppStmt2){
        if(SQLITE_DONE != sqlite3_step(ppStmt2)){ //different var
            printf("step failed...\n");
            printf("error message is: %s\n", sqlite3_errmsg(db));
        }else{
            printf("successfully inserted values to USERINFO table\n");
        }

        if(SQLITE_OK != sqlite3_finalize(ppStmt2)){ //different var
            printf("finalize failed...\n");
            printf("error message is: %s\n", sqlite3_errmsg(db));
        }
    }

    //6. close connection to db.
    sqlite3_close(db);
    return 0;
}
