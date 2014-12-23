/*
 * Shows how to use sqlite3_exec() function
 * Performance wise, avoid this call and use prepare/step/bind sequence instead.
 * sqlite3_exec is a wrapper for the above sequence anyway plus a possible overhead.
 * But it is convenient to use.
 *
 * Reference:
 * http://stackoverflow.com/questions/1703203/in-sqlite-do-prepared-statements-really-improve-performance
 */
