// Topic: Builder Pattern
// Standard: C++20
// Build: g++ -std=c++20 -o http_request HTTPRequestBuilder.cpp

#include <format>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// ─────────────────────────────────────────────
// Product: HttpRequest
// ─────────────────────────────────────────────
class HttpRequest
{
public:
  std::string method;
  std::string url;
  std::vector<std::pair<std::string, std::string>> headers;
  std::optional<std::string> body;
  int timeoutMs{5000};

  void print() const
  {
    std::cout << std::format("  {} {}\n", method, url);
    for (const auto &[k, v] : headers)
      std::cout << std::format("  {}: {}\n", k, v);
    if (body)
      std::cout << std::format("  Body: {}\n", *body);
    std::cout << std::format("  Timeout: {}ms\n", timeoutMs);
  }
};

// ─────────────────────────────────────────────
// Fluent Builder — HTTP Request (using smart pointers)
// ─────────────────────────────────────────────
class HttpRequestBuilder
{
  std::unique_ptr<HttpRequest> req_;

public:
  HttpRequestBuilder() : req_{std::make_unique<HttpRequest>()} {}

  HttpRequestBuilder &get(std::string_view url)
  {
    req_->method = "GET";
    req_->url = url;
    return *this;
  }

  HttpRequestBuilder &post(std::string_view url)
  {
    req_->method = "POST";
    req_->url = url;
    return *this;
  }

  HttpRequestBuilder &put(std::string_view url)
  {
    req_->method = "PUT";
    req_->url = url;
    return *this;
  }

  HttpRequestBuilder &deleteReq(std::string_view url)
  {
    req_->method = "DELETE";
    req_->url = url;
    return *this;
  }

  HttpRequestBuilder &header(std::string_view key, std::string_view val)
  {
    req_->headers.emplace_back(key, val);
    return *this;
  }

  HttpRequestBuilder &body(std::string_view b)
  {
    req_->body = std::string{b};
    return *this;
  }

  HttpRequestBuilder &timeout(int ms)
  {
    req_->timeoutMs = ms;
    return *this;
  }

  // Returns ownership via unique_ptr
  [[nodiscard]] std::unique_ptr<HttpRequest> build()
  {
    return std::move(req_); // transfers ownership to caller
  }
};

// ─────────────────────────────────────────────
// main
// ─────────────────────────────────────────────
int main()
{
  std::cout << std::format("=== Builder Pattern (Fluent Interface) ===\n\n");

  // Example 1: GET Request
  std::cout << std::format("GET Request:\n");
  auto getReq = HttpRequestBuilder{}
                    .get("https://api.example.com/users")
                    .header("Accept", "application/json")
                    .header("Authorization", "Bearer token123")
                    .timeout(3000)
                    .build();
  getReq->print();

  std::cout << '\n';

  // Example 2: POST Request
  std::cout << std::format("POST Request:\n");
  auto postReq = HttpRequestBuilder{}
                     .post("https://api.example.com/users")
                     .header("Content-Type", "application/json")
                     .body(R"({"name":"Alice","age":30})")
                     .build();
  postReq->print();

  std::cout << '\n';

  // Example 3: PUT Request
  std::cout << std::format("PUT Request:\n");
  auto putReq = HttpRequestBuilder{}
                    .put("https://api.example.com/users/42")
                    .header("Content-Type", "application/json")
                    .header("Authorization", "Bearer token456")
                    .body(R"({"name":"Charlie","email":"charlie@example.com"})")
                    .timeout(5000)
                    .build();
  putReq->print();

  std::cout << '\n';

  // Example 4: Using shared_ptr for shared ownership
  std::cout << std::format("Shared Ownership Example:\n");
  std::shared_ptr<HttpRequest> shared = HttpRequestBuilder{}
                                            .get("https://api.example.com/health")
                                            .header("Accept", "*/*")
                                            .timeout(1000)
                                            .build();

  auto copy = shared; // both point to the same request
  std::cout << std::format("shared_ptr use_count: {}\n", shared.use_count());
  copy->print();

  return 0;
}
