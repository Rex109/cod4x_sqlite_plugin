#include <cstring>
#include <string>
#include "sqlite/sqlite3.h"
#include "functions.hpp"

PCL int OnInit()
{ 
    Plugin_ScrAddFunction("sqlite3_open", Scr_Sqlite3_Open_f);
    Plugin_ScrAddFunction("sqlite3_close", Scr_Sqlite3_Close_f);
    Plugin_ScrAddFunction("sqlite3_exec", Scr_Sqlite3_Exec_f);
    Plugin_ScrAddFunction("sqlite3_fetch_assoc", Scr_Sqlite3_Fetch_Assoc_f);
    Plugin_ScrAddFunction("sqlite3_num_rows", Scr_Sqlite3_Num_Rows_f);
    
	return 0;
}

PCL void OnInfoRequest(pluginInfo_t *info)
{
    info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
    info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR;

    info->pluginVersion.major = 1;
    info->pluginVersion.minor = 0;
    strncpy(info->fullName,"SQLite Plugin",sizeof(info->fullName));
    strncpy(info->shortDescription,"CoD4X SQLite3 support for GSC",sizeof(info->shortDescription));
    strncpy(info->longDescription,"CoD4X SQLite3 support for GSC",sizeof(info->longDescription));
}