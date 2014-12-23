/**
 *
 *  Shows how to using binding function.
 *  Binding is required to prevent from injection attacks.
 *  For example, getting a text obtained from user may contain SQL statments
 *  such as dropping tables. If parameter binding is used, such statements can be detected.
 *
 *  Author: Hyunjin Chung
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define DBNAME "./wargame.db"

int main(int argc, char **argv){

    //1. open connection to db.
    sqlite3 * db = NULL;
    if( SQLITE_OK != sqlite3_open(DBNAME, &db)){
        printf("db open failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    //2. ask user input for rank from console
    int rank;
    printf("update rank for Hyunjin: \n");
    scanf("%d", &rank);

    //2. build an update query
    const char * updateRank = " UPDATE USERINFO \
                                 SET RANK = ? \
                                 WHERE ID = 1 \
                                 ";
    sqlite3_stmt *ppStmt = NULL;
    const char **pzTail = NULL;

    //5. preapre statemetn
    if(SQLITE_OK != sqlite3_prepare_v2(
                                db,
                                updateRank,
                                -1, //read up to first null terminator
                                &ppStmt,
                                pzTail)){
        printf("preparing statement failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
    }

    //6. bind the question makr with rank specified above.
    if(SQLITE_OK != sqlite3_bind_int(
                            ppStmt,
                            1,    // index of the question mark
                            rank  //updated rank
                            )){
        printf("failed to bind integer\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
    }

    //Should check the update via SELECT * WHERE id=1..
    //but leave as below for now
    printf("update is successful! inserted rank [%d]\n", rank);

    //7. step
    if(SQLITE_DONE != sqlite3_step(ppStmt)){ //different var
        printf("step failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
    }

    //8. finalize
    if(SQLITE_OK != sqlite3_finalize(ppStmt)){ //different var
        printf("finalize failed...\n");
        printf("error message is: %s\n", sqlite3_errmsg(db));
    }


    //9. close db
    sqlite3_close(db);

    return 0;
}
