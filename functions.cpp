#include "SQLiteConnection.hpp"
#include "functions.hpp"

#define MAX_DB_CONNECTIONS 10

SQLiteConnection* dbConnections[MAX_DB_CONNECTIONS];

void Scr_Sqlite3_Open_f()
{
    int argc = Plugin_Scr_GetNumParam();
    if (argc != 1)
    {
        Plugin_Scr_Error("Usage: handle = sqlite3_open(<dbPath>);");
        return;
    }

    const char* dbPath = Plugin_Scr_GetString(0);

    int i = 0;
    for (;i < MAX_DB_CONNECTIONS; i++)
    {
        if (dbConnections[i] == NULL)
            break;
    }

    if (i == MAX_DB_CONNECTIONS - 1)
    {
        pluginError("Maximum number of database connections reached (%d).", MAX_DB_CONNECTIONS);
        return;
    }

    dbConnections[i] = new SQLiteConnection(dbPath);

    if(dbConnections[i]->connection_status)
    {
        pluginError("Failed to open database: %s", dbPath);
        return;
    }

    Plugin_Scr_AddInt(i);
}

void Scr_Sqlite3_Close_f()
{
    int argc = Plugin_Scr_GetNumParam();
    if (argc != 1)
    {
        Plugin_Scr_Error("Usage: sqlite3_close(<handle>);");
        return;
    }

    int handle = Plugin_Scr_GetInt(0);

    if (handle < 0 || handle >= MAX_DB_CONNECTIONS || dbConnections[handle] == NULL)
    {
        pluginError("Invalid database connection handle.");
        return;
    }

    delete dbConnections[handle];
    dbConnections[handle] = NULL;
}

void Scr_Sqlite3_Exec_f()
{
    int argc = Plugin_Scr_GetNumParam();
    if (argc != 2)
    {
        Plugin_Scr_Error("Usage: sqlite3_exec(<handle>, <sql>);");
        return;
    }

    int handle = Plugin_Scr_GetInt(0);
    const char* sql = Plugin_Scr_GetString(1);

    if (handle < 0 || handle >= MAX_DB_CONNECTIONS || dbConnections[handle] == NULL)
    {
        pluginError("Invalid database connection handle.");
        return;
    }

    int rc = dbConnections[handle]->Exec(sql);

    if (rc != SQLITE_OK)
    {
        pluginError("Failed to execute SQL statement: %s", dbConnections[handle]->errorMessage.c_str());
        return;
    }
}

void Scr_Sqlite3_Fetch_Assoc_f()
{
    int argc = Plugin_Scr_GetNumParam();
    if (argc != 1)
    {
        Plugin_Scr_Error("Usage: sqlite3_fetch_assoc(<handle>);");
        return;
    }

    int handle = Plugin_Scr_GetInt(0);

    if (handle < 0 || handle >= MAX_DB_CONNECTIONS || dbConnections[handle] == NULL)
    {
        pluginError("Invalid database connection handle.");
        return;
    }

    Plugin_Scr_MakeArray();

    for (auto const& x : dbConnections[handle]->assoc)
    {
        Plugin_Scr_MakeArray();
        
        for (auto const& y : x.second)
        {
            Plugin_Scr_AddString(y.c_str());
            Plugin_Scr_AddArray();
        }
            
        Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(x.first.c_str()));
    }
}

void Scr_Sqlite3_Num_Rows_f()
{
    int argc = Plugin_Scr_GetNumParam();
    if (argc != 1)
    {
        Plugin_Scr_Error("Usage: sqlite3_num_rows(<handle>);");
        return;
    }

    int handle = Plugin_Scr_GetInt(0);

    if (handle < 0 || handle >= MAX_DB_CONNECTIONS || dbConnections[handle] == NULL)
    {
        pluginError("Invalid database connection handle.");
        return;
    }

    Plugin_Scr_AddInt(dbConnections[handle]->num_rows);
}

void pluginError(const char *const Format_, ...)
{
    char buffer[1024] = {'\0'};
    va_list va;
    va_start(va, Format_);
#ifdef _WIN32
    _vsnprintf(buffer, sizeof(buffer), Format_, va);
#else
    vsnprintf(buffer, sizeof(buffer), Format_, va);
#endif
    buffer[sizeof(buffer) - 1] = '\0';
    va_end(va);

    Plugin_Scr_Error(buffer);
}