#include "SQLiteConnection.hpp"

SQLiteConnection::SQLiteConnection(const char* dbPath)
{
    connection_status = sqlite3_open(dbPath, &db);

    if (connection_status)
        sqlite3_close(db);
}

int SQLiteConnection::Exec(const char* sql)
{
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    if(rc != SQLITE_OK)
    {
        errorMessage = sqlite3_errmsg(db);
        return rc;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        int columns = sqlite3_column_count(stmt);
        for(int i = 0; i < columns; i++)
        {
            const char* column_name = sqlite3_column_name(stmt, i);
            const char* column_text = (const char*)sqlite3_column_text(stmt, i);
            assoc[column_name].push_back(column_text);
        }
        num_rows++;
    }

    sqlite3_finalize(stmt);

    return rc;
}

SQLiteConnection::~SQLiteConnection()
{
    sqlite3_close(db);
}