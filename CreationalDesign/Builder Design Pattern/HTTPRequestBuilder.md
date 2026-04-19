// HTTP Request Builder Example Documentation

# HTTP Request Builder Pattern

## Overview
The HTTP Request Builder is a practical example of the Builder pattern used to construct complex HTTP requests with many optional components (headers, query parameters, authentication, body, etc.).

## Components

### Product: `HTTPRequest`
Represents a complete HTTP request with:
- HTTP method (GET, POST, PUT, DELETE, etc.)
- URL
- Headers (key-value pairs)
- Query parameters
- Request body
- Display method for inspection

### Abstract Builder: `HTTPRequestBuilder`
Provides a fluent interface for building requests:
- `setMethod()` — Set HTTP method
- `setURL()` — Set request URL
- `addHeader()` — Add custom headers
- `setBody()` — Set request body
- `addQueryParam()` — Add query parameters
- `setContentType()` — Convenience method for Content-Type header
- `setAuthorization()` — Convenience method for Authorization header
- `build()` — Return the constructed HTTPRequest

### Concrete Builders

#### `StandardHTTPBuilder`
- Basic HTTP client builder
- Sets default `User-Agent` header
- Good for general-purpose requests

#### `APIClientBuilder` (extends HTTPRequestBuilder)
- Specialized for REST API calls
- Sets default `Accept: application/json`
- Provides `setAPIKey()` for API authentication
- Provides `setJSONBody()` for convenience

## Key Features

### Fluent Interface (Method Chaining)
```cpp
auto request = builder
    .setMethod("POST")
    .setURL("https://api.example.com/users")
    .addHeader("Content-Type", "application/json")
    .setBody(jsonData)
    .build();
```

### Validation
- Throws exception if URL is missing when building
- Can be extended to validate other requirements

### Type Safety
- Uses C++20 `std::format` for safe string formatting
- Compile-time type checking

### Extensibility
- Easy to add new builder types (e.g., `GraphQLBuilder`, `SOAPBuilder`)
- Convenience methods can be added to specific builders

## Usage Examples

### Simple GET Request
```cpp
StandardHTTPBuilder builder;
auto request = builder
    .setMethod("GET")
    .setURL("https://api.example.com/users")
    .addQueryParam("page", "1")
    .addQueryParam("limit", "10")
    .build();
```

### POST with JSON
```cpp
StandardHTTPBuilder builder;
auto request = builder
    .setMethod("POST")
    .setURL("https://api.example.com/users")
    .setContentType("application/json")
    .setBody(R"({"name":"John","email":"john@example.com"})")
    .setAuthorization("Bearer token123")
    .build();
```

### API Client with Special Builder
```cpp
APIClientBuilder builder;
auto request = builder
    .setMethod("PUT")
    .setURL("https://api.github.com/repos/user/repo")
    .setAPIKey("ghp_xxxxx")
    .setJSONBody(R"({"description":"Updated"})")
    .build();
```

## Benefits

| Aspect | Benefit |
|--------|---------|
| **Readability** | Clear, fluent syntax shows request structure |
| **Flexibility** | Easy to add/remove optional components |
| **Safety** | Validation happens before request is built |
| **Reusability** | Builder can be reused multiple times |
| **Maintenance** | Adding new parameters doesn't require constructor changes |
| **Testability** | Easy to create various test request combinations |

## Real-World Use Cases

- **HTTP Client Libraries** — Building requests before sending over network
- **API Testing Frameworks** — Constructing test requests programmatically
- **Web Scrapers** — Creating varied requests to different endpoints
- **Microservices** — Building inter-service communication requests
- **Mobile Apps** — Constructing network requests with optional auth/headers

## Comparison: Without Builder vs With Builder

### Without Builder (Problematic)
```cpp
// Requires constructor overloading or parameter objects
HTTPRequest req("POST", "url", headers, body, queryParams, ...);
```

### With Builder (Clean)
```cpp
APIClientBuilder builder;
auto req = builder
    .setMethod("POST")
    .setURL("url")
    .addHeader("key", "value")
    .setBody(body)
    .addQueryParam("param", "value")
    .build();
```

## Compilation

```bash
g++ -std=c++20 -o http_request HTTPRequestBuilder.cpp
./http_request
```

## C++20 Features Used

- `std::format` — Type-safe string formatting
- `std::unique_ptr` — Smart pointer memory management
- `std::map` — Header storage
- `std::vector` — Query parameters collection
- Structured bindings — `for (const auto &[key, value] : headers_)`
