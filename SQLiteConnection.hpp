#pragma once
#include "sqlite/sqlite3.h"
#include <unordered_map>
#include <vector>
#include <string>

class SQLiteConnection {
private:
    sqlite3* db;

public:
    std::unordered_map<std::string, std::vector<std::string>> assoc;
    int num_rows;
    int connection_status;
    std::string errorMessage;

    SQLiteConnection(const char* dbPath);

    int Exec(const char* sql);

    ~SQLiteConnection();
};