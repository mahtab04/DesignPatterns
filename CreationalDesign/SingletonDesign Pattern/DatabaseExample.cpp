// Singleton Design Pattern
//  Define a class that has only one instance and provides a global point of access to it.

#include <iostream>
#include <string>
#include <vector>

class Database
{
private:
  std::string host_;
  std::string username_;
  std::string password_;
  std::string database_name_;

  // Private constructor so that no objects can be created.
  Database()
      : host_("localhost"), username_("root"), password_("root"),
        database_name_("test")
  {
  }

  // Delete copy and move to prevent duplication
  Database(const Database &) = delete;
  Database &operator=(const Database &) = delete;
  Database(Database &&) = delete;
  Database &operator=(Database &&) = delete;

public:
  // Meyer's Singleton — thread-safe in C++11+, no raw new/delete
  static Database &getInstance()
  {
    static Database instance;
    return instance;
  }

  // Database operations...
  void connect()
  {
    std::cout << "Connected to " << database_name_ << " at " << host_
              << std::endl;
  }

  void disconnect()
  {
    std::cout << "Disconnected from " << database_name_ << std::endl;
  }

  void executeQuery(const std::string &query)
  {
    std::cout << "Executing: " << query << std::endl;
  }

  std::vector<std::string> getResults() const
  {
    // Get the results of the last executed query
    return {};
  }
};

int main()
{
  Database &db1 = Database::getInstance();
  db1.connect();
  db1.disconnect();

  Database &db2 = Database::getInstance();
  db2.connect();
  db2.disconnect();

  // Verify it's the same instance
  std::cout << "\nSame instance? " << (&db1 == &db2 ? "Yes" : "No")
            << std::endl;

  return 0;
}
