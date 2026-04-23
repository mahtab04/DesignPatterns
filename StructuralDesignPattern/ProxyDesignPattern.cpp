// Topic: Proxy Pattern
// Standard: C++20
// Build: g++ -std=c++20 -o proxy ProxyDesignPattern.cpp

#include <iostream>
#include <memory>
#include <string>

class IImage
{
public:
  virtual ~IImage() = default;
  virtual void display() = 0;
};

class RealImage : public IImage
{
  std::string fileName_;

  void loadFromDisk()
  {
    std::cout << "Loading image from disk: " << fileName_ << "\n";
  }

public:
  explicit RealImage(std::string fileName) : fileName_(std::move(fileName))
  {
    loadFromDisk();
  }

  void display() override
  {
    std::cout << "Displaying image: " << fileName_ << "\n";
  }
};

class ImageProxy : public IImage
{
  std::string fileName_;
  std::unique_ptr<RealImage> realImage_;
  bool hasAccess_{true};

public:
  explicit ImageProxy(std::string fileName, bool hasAccess = true)
      : fileName_(std::move(fileName)), hasAccess_(hasAccess) {}

  void display() override
  {
    std::cout << "[Proxy] Request to display image\n";

    if (!hasAccess_)
    {
      std::cout << "[Proxy] Access denied\n";
      return;
    }

    if (!realImage_)
    {
      std::cout << "[Proxy] Lazy-loading RealImage\n";
      realImage_ = std::make_unique<RealImage>(fileName_);
    }

    realImage_->display();
  }
};

int main()
{
  std::cout << "=== Proxy Pattern ===\n\n";

  IImage *img = nullptr;

  std::cout << "Allowed user flow:\n";
  ImageProxy allowed("profile_photo.png", true);
  img = &allowed;
  img->display();
  img->display();

  std::cout << "\nDenied user flow:\n";
  ImageProxy denied("secret.png", false);
  img = &denied;
  img->display();

  return 0;
}
