// Dependency Inversion Principle
// High-level modules should not depend on low-level modules. Both should depend
// on abstractions. Abstractions should not depend on details. Details should
// depend on abstractions.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ========================
// Without DIP (Violation)
// ========================

// Low-level module
class MySQLDatabase
{
public:
  void save(const std::string &data)
  {
    std::cout << "[Bad] Saving '" << data << "' to MySQL database."
              << std::endl;
  }
};

// High-level module directly depends on low-level module
class BadUserService
{
private:
  MySQLDatabase db; // Tight coupling to MySQL!

public:
  void createUser(const std::string &name)
  {
    std::cout << "[Bad] Creating user: " << name << std::endl;
    db.save(name);
  }
};

// Problem: If we want to switch to PostgreSQL or an in-memory DB for testing,
// we have to modify BadUserService. This violates DIP.

// ========================
// With DIP (Correct)
// ========================

// Abstraction (interface) that both high-level and low-level modules depend on
class IDatabase
{
public:
  virtual ~IDatabase() = default;
  virtual void save(const std::string &data) = 0;
  virtual std::string getName() const = 0;
};

// Low-level module 1: MySQL
class MySQLDB : public IDatabase
{
public:
  void save(const std::string &data) override
  {
    std::cout << "Saving '" << data << "' to MySQL." << std::endl;
  }
  std::string getName() const override { return "MySQL"; }
};

// Low-level module 2: PostgreSQL
class PostgreSQLDB : public IDatabase
{
public:
  void save(const std::string &data) override
  {
    std::cout << "Saving '" << data << "' to PostgreSQL." << std::endl;
  }
  std::string getName() const override { return "PostgreSQL"; }
};

// Low-level module 3: In-Memory (for testing)
class InMemoryDB : public IDatabase
{
private:
  std::vector<std::string> storage;

public:
  void save(const std::string &data) override
  {
    storage.push_back(data);
    std::cout << "Saving '" << data
              << "' to In-Memory DB. (Total records: " << storage.size() << ")"
              << std::endl;
  }
  std::string getName() const override { return "InMemory"; }
};

// High-level module depends on abstraction, NOT on concrete implementations
class UserService
{
private:
  IDatabase &db; // Depends on interface!

public:
  // Dependency is INJECTED via constructor
  UserService(IDatabase &database) : db(database) {}

  void createUser(const std::string &name)
  {
    std::cout << "Creating user '" << name << "' using " << db.getName()
              << " database." << std::endl;
    db.save(name);
  }
};

// Another high-level module reusing the same abstraction
class LogService
{
private:
  IDatabase &db;

public:
  LogService(IDatabase &database) : db(database) {}

  void log(const std::string &message)
  {
    std::cout << "Logging to " << db.getName() << ": " << message << std::endl;
    db.save("[LOG] " + message);
  }
};

int main()
{
  std::cout << "=== Without DIP (Violation) ===" << std::endl;
  BadUserService badService;
  badService.createUser("John");
  // Can't easily switch databases or mock for testing

  std::cout << "\n=== With DIP (Correct) ===" << std::endl;

  // Easily switch between different database implementations
  MySQLDB mysql;
  PostgreSQLDB postgres;
  InMemoryDB inMemory;

  // Same UserService, different databases — no code change needed
  UserService service1(mysql);
  service1.createUser("Alice");

  std::cout << std::endl;
  UserService service2(postgres);
  service2.createUser("Bob");

  std::cout << std::endl;
  UserService service3(inMemory); // Great for testing!
  service3.createUser("Charlie");

  std::cout << "\n--- Log Service reuses the same abstraction ---" << std::endl;
  LogService logger(inMemory);
  logger.log("User Charlie was created");

  return 0;
}
