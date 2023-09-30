#include <iostream>
#include <string>
#include <vector>

class Database
{
private:
    static Database *m_instance;
    std::string host_;
    std::string username_;
    std::string password_;
    std::string database_name_;
    // Private constructor so that no objects can be created.
    Database()
    {
        host_ = "localhost";
        username_ = "root";
        password_ = "root";
        database_name_ = "test";
    }
    // We don't want to allow copies of the database
    Database(const Database &) = delete;
    Database &operator=(const Database &) = delete;

public:
    static Database *getInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new Database();
        }
        return m_instance;
    }

    // Database operations...
    void connect()
    {
        // Connect to the database
    }

    void disconnect()
    {
        // Disconnect from the database
    }

    void executeQuery(const std::string &query)
    {
        // Execute the given SQL query
    }

    std::vector<std::string> getResults()
    {
        // Get the results of the last executed query
    }
    // Destructor to free the allocated memory.
    ~Database()
    {
        delete m_instance;
    }
};

Database *Database::m_instance = nullptr;

int main()
{
    Database *db1 = Database::getInstance();
    db1->connect();
    db1->disconnect();

    Database *db2 = Database::getInstance();
    db2->connect();
    db2->disconnect();

    // No need to manually delete db1 and db2, the destructor takes care of it when the program exits

    return 0;
}
