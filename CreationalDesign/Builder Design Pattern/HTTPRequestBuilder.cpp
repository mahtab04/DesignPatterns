// HTTP Request Builder Pattern — C++20 Implementation
// Demonstrates building complex HTTP requests with multiple optional parts
// Standard: C++20
// Build: g++ -std=c++20 -o http_request HTTPRequestBuilder.cpp

#include <format>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// ========================
// Product: HTTPRequest
// ========================
class HTTPRequest
{
public:
  struct QueryParam
  {
    std::string key;
    std::string value;
  };

  const std::string &getMethod() const { return method_; }
  const std::string &getURL() const { return url_; }
  const std::map<std::string, std::string> &getHeaders() const
  {
    return headers_;
  }
  const std::string &getBody() const { return body_; }
  const std::vector<QueryParam> &getQueryParams() const
  {
    return query_params_;
  }

  void display() const
  {
    std::cout << std::format("═══════════════════════════════════\n");
    std::cout << std::format("📨 HTTP {} Request\n", method_);
    std::cout << std::format("URL: {}\n", url_);

    if (!query_params_.empty())
    {
      std::cout << std::format("Query Parameters:\n");
      for (const auto &param : query_params_)
      {
        std::cout << std::format("  • {} = {}\n", param.key, param.value);
      }
    }

    if (!headers_.empty())
    {
      std::cout << std::format("Headers:\n");
      for (const auto &[key, value] : headers_)
      {
        std::cout << std::format("  • {}: {}\n", key, value);
      }
    }

    if (!body_.empty())
    {
      std::cout << std::format("Body:\n{}\n", body_);
    }
    std::cout << std::format("═══════════════════════════════════\n");
  }

private:
  friend class HTTPRequestBuilder;

  std::string method_{"GET"};
  std::string url_;
  std::map<std::string, std::string> headers_;
  std::string body_;
  std::vector<QueryParam> query_params_;
};

// ========================
// Abstract Builder
// ========================
class HTTPRequestBuilder
{
public:
  virtual ~HTTPRequestBuilder() = default;

  HTTPRequestBuilder &setMethod(const std::string &method)
  {
    request_->method_ = method;
    return *this;
  }

  HTTPRequestBuilder &setURL(const std::string &url)
  {
    request_->url_ = url;
    return *this;
  }

  HTTPRequestBuilder &addHeader(const std::string &key,
                                const std::string &value)
  {
    request_->headers_[key] = value;
    return *this;
  }

  HTTPRequestBuilder &setBody(const std::string &body)
  {
    request_->body_ = body;
    return *this;
  }

  HTTPRequestBuilder &addQueryParam(const std::string &key,
                                    const std::string &value)
  {
    request_->query_params_.push_back({key, value});
    return *this;
  }

  HTTPRequestBuilder &setContentType(const std::string &contentType)
  {
    request_->headers_["Content-Type"] = contentType;
    return *this;
  }

  HTTPRequestBuilder &setAuthorization(const std::string &token)
  {
    request_->headers_["Authorization"] = std::format("Bearer {}", token);
    return *this;
  }

  std::unique_ptr<HTTPRequest> build()
  {
    if (request_->url_.empty())
    {
      throw std::runtime_error("URL is required!");
    }
    return std::move(request_);
  }

protected:
  HTTPRequestBuilder() : request_(std::make_unique<HTTPRequest>()) {}

  std::unique_ptr<HTTPRequest> request_;
};

// ========================
// Concrete Builder: Standard HTTP Builder
// ========================
class StandardHTTPBuilder : public HTTPRequestBuilder
{
public:
  StandardHTTPBuilder() : HTTPRequestBuilder()
  {
    // Set default headers for standard HTTP requests
    addHeader("User-Agent", "C++20-HTTPClient/1.0");
  }
};

// ========================
// Concrete Builder: API Client Builder (for REST APIs)
// ========================
class APIClientBuilder : public HTTPRequestBuilder
{
public:
  APIClientBuilder() : HTTPRequestBuilder()
  {
    // Set default headers for API requests
    addHeader("User-Agent", "C++20-APIClient/1.0");
    addHeader("Accept", "application/json");
  }

  APIClientBuilder &setAPIKey(const std::string &apiKey)
  {
    request_->headers_["X-API-Key"] = apiKey;
    return *this;
  }

  APIClientBuilder &setJSONBody(const std::string &jsonData)
  {
    setContentType("application/json");
    setBody(jsonData);
    return *this;
  }
};

int main()
{
  std::cout << std::format("\n🌐 HTTP Request Builder Pattern Examples\n\n");

  // Example 1: Simple GET request
  std::cout << std::format("Example 1️⃣: Simple GET Request\n");
  StandardHTTPBuilder getBuilder;
  auto getRequest = getBuilder.setMethod("GET")
                        .setURL("https://api.example.com/users")
                        .addQueryParam("page", "1")
                        .addQueryParam("limit", "10")
                        .build();
  getRequest->display();

  // Example 2: POST request with body
  std::cout << std::format("\nExample 2️⃣: POST Request with JSON Body\n");
  StandardHTTPBuilder postBuilder;
  auto postRequest = postBuilder.setMethod("POST")
                         .setURL("https://api.example.com/users")
                         .setContentType("application/json")
                         .setBody(R"({"name":"John Doe","email":"john@example.com"})")
                         .addHeader("Authorization", "Bearer abc123token")
                         .build();
  postRequest->display();

  // Example 3: API Client with simplified builder
  std::cout << std::format("\nExample 3️⃣: API Client Builder\n");
  APIClientBuilder apiBuilder;
  auto apiRequest = apiBuilder.setMethod("PUT")
                        .setURL("https://api.github.com/repos/user/repo")
                        .setAPIKey("ghp_1234567890abcdef")
                        .setJSONBody(R"({"description":"Updated repo"})")
                        .setAuthorization("personal-token-12345")
                        .build();
  apiRequest->display();

  // Example 4: Complex request with many parameters
  std::cout << std::format("\nExample 4️⃣: Complex Request with Multiple Headers\n");
  StandardHTTPBuilder complexBuilder;
  auto complexRequest = complexBuilder.setMethod("POST")
                            .setURL("https://api.example.com/search")
                            .addQueryParam("q", "C++20")
                            .addQueryParam("lang", "en")
                            .addHeader("Accept-Language", "en-US")
                            .addHeader("Accept-Encoding", "gzip, deflate")
                            .addHeader("Connection", "keep-alive")
                            .setContentType("application/x-www-form-urlencoded")
                            .setBody("search_term=build+pattern&filter=recent")
                            .build();
  complexRequest->display();

  return 0;
}
