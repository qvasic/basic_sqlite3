#include <iostream>

#include <sqlite3.h>

int read_odometer(sqlite3 *db)
{
    int odometer_value = 0;

    sqlite3_stmt *statement = nullptr;
    const char* select_statement = "select * from odometer where id = ?;";

    if (sqlite3_prepare_v2(db, select_statement, -1, &statement, nullptr) == SQLITE_OK && statement != nullptr
        && sqlite3_bind_int(statement, 1, 0) == SQLITE_OK)
    {
        if (sqlite3_step(statement) == SQLITE_ROW)
        {
            odometer_value = sqlite3_column_int(statement, 1);
        }
        else
        {
            std::cout << "no data read from db" << std::endl;
        }
    }
    else
    {
        std::cout << "could not compile statement" << std::endl;
    }

    sqlite3_finalize(statement);
    return odometer_value;
}

void set_odometer(sqlite3 *db, int value)
{   
    sqlite3_stmt *statement = nullptr;
    const char* select_statement = "update odometer set odometer_cm = ? where id = ?;";

    if (sqlite3_prepare_v2(db, select_statement, -1, &statement, nullptr) == SQLITE_OK && statement != nullptr
        && sqlite3_bind_int(statement, 1, value) == SQLITE_OK && sqlite3_bind_int(statement, 2, 0) == SQLITE_OK)
    {
        if (sqlite3_step(statement) != SQLITE_DONE)
        {
            std::cout << "something wrong while executing sqlite3 statement" << std::endl;
        }
    }
    else
    {
        std::cout << "could not compile statement" << std::endl;
    }

    sqlite3_finalize(statement);
}

int main()
{
    std::cout << "what0" << std::endl;

    sqlite3 *db = nullptr;
    if (sqlite3_open("persist.db", &db) == SQLITE_OK && db != nullptr)
    {
        std::cout << "db open success, odometer = " << read_odometer(db) << std::endl;

        int new_odometer_value_cm = 0;
        std::cout << "enter new value in cm: ";
        std::cin >> new_odometer_value_cm;
        set_odometer(db, new_odometer_value_cm);
    }
    else
    {
        std::cout << "error opening db" << std::endl;
    }

    sqlite3_close(db);
}
