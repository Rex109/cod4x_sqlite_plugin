#pragma once
#include "../pinc.h"

void Scr_Sqlite3_Open_f();
void Scr_Sqlite3_Close_f();
void Scr_Sqlite3_Exec_f();
void Scr_Sqlite3_Fetch_Assoc_f();
void Scr_Sqlite3_Num_Rows_f();

void pluginError(const char *const Format_, ...);