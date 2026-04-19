// Topic: Singleton Pattern
// Standard: C++20
// Build: g++ -std=c++20 -o singleton singleton.cpp

#include <format>
#include <iostream>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

// ─────────────────────────────────────────────
// 1. Meyer's Singleton (Thread-safe, Modern)
// ─────────────────────────────────────────────
class Logger
{
public:
  static Logger &instance()
  {
    static Logger inst; // C++11: guaranteed thread-safe init
    return inst;
  }

  void log(std::string_view msg)
  {
    std::cout << std::format("[LOG #{}] {}\n", ++count_, msg);
  }

  [[nodiscard]] int getCount() const { return count_; }

  // Delete copy and move
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;
  Logger(Logger &&) = delete;
  Logger &operator=(Logger &&) = delete;

private:
  Logger() { std::cout << "[Logger] Singleton created\n"; }
  ~Logger() { std::cout << "[Logger] Singleton destroyed\n"; }
  int count_{0};
};

// ─────────────────────────────────────────────
// 2. Template Singleton (Reusable)
// ─────────────────────────────────────────────
template <typename T> class Singleton
{
public:
  static T &instance()
  {
    static T inst;
    return inst;
  }

  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

protected:
  Singleton() = default;
  ~Singleton() = default;
};

class AppConfig : public Singleton<AppConfig>
{
  friend class Singleton<AppConfig>;

  std::string appName_{"MyApp"};
  int version_{1};

  AppConfig() { std::cout << "[AppConfig] Created\n"; }

public:
  void setAppName(std::string_view name) { appName_ = name; }
  [[nodiscard]] const std::string &getAppName() const { return appName_; }
  [[nodiscard]] int getVersion() const { return version_; }
};

// ─────────────────────────────────────────────
// main
// ─────────────────────────────────────────────
int main()
{
  std::cout << "=== 1. Meyer's Singleton ===\n";
  Logger::instance().log("Application started");
  Logger::instance().log("Processing data");

  auto &log = Logger::instance(); // same instance
  log.log("Done");
  std::cout << std::format("Total logs: {}\n\n", log.getCount());

  // Verify same instance
  std::cout << std::format("Same instance? {}\n\n",
                           &Logger::instance() == &log);

  std::cout << "=== 2. Template Singleton ===\n";
  AppConfig::instance().setAppName("CppLearning");
  std::cout << std::format("App: {} v{}\n", AppConfig::instance().getAppName(),
                           AppConfig::instance().getVersion());

  return 0;
}
