// Interface Segregation Principle
// No client should be forced to depend on methods it does not use.
// Many small, specific interfaces are better than one large, general-purpose
// interface.

#include <iostream>
#include <string>

// ========================
// Without ISP (Violation)
// ========================

// One fat interface forces all workers to implement everything
class IWorker
{
public:
  virtual ~IWorker() = default;
  virtual void work() = 0;
  virtual void eat() = 0;
  virtual void code() = 0;
  virtual void manage() = 0;
};

// Developer doesn't manage, but is forced to implement manage()
class BadDeveloper : public IWorker
{
public:
  void work() override
  {
    std::cout << "[Bad] Developer working..." << std::endl;
  }
  void eat() override { std::cout << "[Bad] Developer eating..." << std::endl; }
  void code() override
  {
    std::cout << "[Bad] Developer coding..." << std::endl;
  }
  void manage() override
  {
    // Forced to implement — does nothing! Violation of ISP.
    throw std::runtime_error("Developer doesn't manage!");
  }
};

// Robot doesn't eat, but is forced to implement eat()
class BadRobot : public IWorker
{
public:
  void work() override { std::cout << "[Bad] Robot working..." << std::endl; }
  void eat() override
  {
    // Forced to implement — makes no sense! Violation of ISP.
    throw std::runtime_error("Robot doesn't eat!");
  }
  void code() override { std::cout << "[Bad] Robot coding..." << std::endl; }
  void manage() override { throw std::runtime_error("Robot doesn't manage!"); }
};

// ========================
// With ISP (Correct)
// ========================

// Small, focused interfaces
class IWorkable
{
public:
  virtual ~IWorkable() = default;
  virtual void work() = 0;
};

class IFeedable
{
public:
  virtual ~IFeedable() = default;
  virtual void eat() = 0;
};

class ICodable
{
public:
  virtual ~ICodable() = default;
  virtual void code() = 0;
};

class IManageable
{
public:
  virtual ~IManageable() = default;
  virtual void manage() = 0;
};

// Developer implements only what it needs
class Developer : public IWorkable, public IFeedable, public ICodable
{
  std::string name;

public:
  Developer(const std::string &n) : name(n) {}

  void work() override { std::cout << name << " is working." << std::endl; }
  void eat() override { std::cout << name << " is eating lunch." << std::endl; }
  void code() override
  {
    std::cout << name << " is writing code." << std::endl;
  }
};

// Manager implements only what it needs
class Manager : public IWorkable, public IFeedable, public IManageable
{
  std::string name;

public:
  Manager(const std::string &n) : name(n) {}

  void work() override { std::cout << name << " is working." << std::endl; }
  void eat() override { std::cout << name << " is eating lunch." << std::endl; }
  void manage() override
  {
    std::cout << name << " is managing the team." << std::endl;
  }
};

// Robot only works and codes — no eating or managing
class Robot : public IWorkable, public ICodable
{
  std::string model;

public:
  Robot(const std::string &m) : model(m) {}

  void work() override { std::cout << model << " is working." << std::endl; }
  void code() override
  {
    std::cout << model << " is writing code." << std::endl;
  }
};

// Functions can accept specific interfaces
void assignWork(IWorkable &worker) { worker.work(); }

void feedWorker(IFeedable &worker) { worker.eat(); }

int main()
{
  std::cout << "=== Without ISP (Violation) ===" << std::endl;
  BadDeveloper badDev;
  badDev.work();
  badDev.code();
  // badDev.manage(); // Would throw — forced to implement something useless

  std::cout << "\n=== With ISP (Correct) ===" << std::endl;
  Developer dev("Alice");
  Manager mgr("Bob");
  Robot bot("RX-100");

  // Each function accepts only the interface it needs
  assignWork(dev);
  assignWork(mgr);
  assignWork(bot);

  std::cout << std::endl;
  feedWorker(dev);
  feedWorker(mgr);
  // feedWorker(bot); // Won't compile — Robot is not IFeedable. Correct!

  std::cout << std::endl;
  dev.code();
  bot.code();
  mgr.manage();

  return 0;
}
