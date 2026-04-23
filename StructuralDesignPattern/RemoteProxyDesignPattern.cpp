// Topic: Proxy Pattern (Remote Proxy Example)
// Standard: C++20
// Build: g++ -std=c++20 -o remote_proxy RemoteProxyDesignPattern.cpp

#include <iostream>
#include <memory>
#include <string>

class IWeatherService
{
public:
  virtual ~IWeatherService() = default;
  virtual std::string getTemperature(const std::string &city) = 0;
};

class RemoteWeatherService : public IWeatherService
{
public:
  std::string getTemperature(const std::string &city) override
  {
    std::cout << "[RemoteService] Network call for city: " << city << "\n";

    if (city == "Berlin")
      return "18 C";
    if (city == "Tokyo")
      return "23 C";
    if (city == "Delhi")
      return "31 C";

    return "N/A";
  }
};

class WeatherServiceProxy : public IWeatherService
{
  std::unique_ptr<RemoteWeatherService> remote_;
  int requestCount_{0};
  const int maxRequests_{5};

public:
  WeatherServiceProxy() : remote_(std::make_unique<RemoteWeatherService>()) {}

  std::string getTemperature(const std::string &city) override
  {
    if (++requestCount_ > maxRequests_)
    {
      return "Rate limit exceeded";
    }

    std::cout << "[Proxy] request " << requestCount_ << " of " << maxRequests_ << "\n";
    return remote_->getTemperature(city);
  }
};

int main()
{
  std::cout << "=== Remote Proxy Pattern ===\n\n";

  IWeatherService *service = nullptr;
  WeatherServiceProxy proxy;
  service = &proxy;

  std::cout << "Berlin: " << service->getTemperature("Berlin") << "\n";
  std::cout << "Tokyo : " << service->getTemperature("Tokyo") << "\n";
  std::cout << "Delhi : " << service->getTemperature("Delhi") << "\n";
  std::cout << "Rome  : " << service->getTemperature("Rome") << "\n";
  std::cout << "Paris : " << service->getTemperature("Paris") << "\n";
  std::cout << "Seoul : " << service->getTemperature("Seoul") << "\n";

  return 0;
}
