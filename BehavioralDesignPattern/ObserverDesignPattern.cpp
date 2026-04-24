// Topic: Observer Pattern
// Standard: C++20
// Build: g++ -std=c++20 -o observer ObserverDesignPattern.cpp

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ── Observer Interface ──
class IObserver
{
public:
  virtual ~IObserver() = default;
  virtual void update(const std::string &message) = 0;
};

// ── Subject (Observable) ──
class NewsPublisher
{
  std::vector<std::shared_ptr<IObserver>> subscribers_;
  std::string latestNews_;

public:
  void attach(const std::shared_ptr<IObserver> &observer)
  {
    subscribers_.push_back(observer);
  }

  void detach(const std::shared_ptr<IObserver> &observer)
  {
    subscribers_.erase(
        std::remove(subscribers_.begin(), subscribers_.end(), observer),
        subscribers_.end());
  }

  void notify()
  {
    for (auto &sub : subscribers_)
    {
      sub->update(latestNews_);
    }
  }

  void publishNews(const std::string &news)
  {
    latestNews_ = news;
    std::cout << "Publisher: New article -> " << news << "\n";
    notify();
  }
};

// ── Concrete Observers ──
class EmailSubscriber : public IObserver
{
  std::string name_;

public:
  explicit EmailSubscriber(std::string name) : name_(std::move(name)) {}

  void update(const std::string &message) override
  {
    std::cout << "  [Email] " << name_ << " received: " << message << "\n";
  }
};

class AppSubscriber : public IObserver
{
  std::string name_;

public:
  explicit AppSubscriber(std::string name) : name_(std::move(name)) {}

  void update(const std::string &message) override
  {
    std::cout << "  [App]   " << name_ << " received: " << message << "\n";
  }
};

int main()
{
  std::cout << "=== Observer Pattern ===\n\n";

  NewsPublisher publisher;

  auto alice = std::make_shared<EmailSubscriber>("Alice");
  auto bob = std::make_shared<AppSubscriber>("Bob");
  auto carol = std::make_shared<EmailSubscriber>("Carol");

  publisher.attach(alice);
  publisher.attach(bob);
  publisher.attach(carol);

  publisher.publishNews("C++26 Released!");

  std::cout << "\n-- Carol unsubscribes --\n\n";
  publisher.detach(carol);

  publisher.publishNews("Qt 7.0 is out!");

  return 0;
}
