![License](https://img.shields.io/github/license/rex109/cod4x_sqlite_plugin)
[![Personal Discord](https://img.shields.io/discord/953653773962739793?color=%237289DA&label=Personal%20Discord&logo=discord&logoColor=%23FFFFFF)](https://discord.gg/QDYk75vBBk)
[![ManyAsset](https://img.shields.io/discord/585171589750849538?color=%23FF8711&label=ManyAsset&logo=discord&logoColor=%23FFFFFF)](https://discord.gg/v2TWkeR)
# CoD4x SQLite Plugin
CoD4X SQLite3 support for GSC

# Added functions

## `handle = sqlite3_open(<filename>);`

Connects to a sqlite3 database, returns the handle.

## `sqlite3_close(<handle>);`

Closes the connection to the sqlite3 database specified by the handle.

## `sqlite3_exec(<handle>, <query>);`

Executes a query on the sqlite3 database specified by the handle.

## `array = sqlite3_fetch_assoc(<handle>);`

Fetches the associative array of the result of the last query.

## `count = sqlite3_num_rows(<handle>);`

Returns the number of rows in the result of the last query.