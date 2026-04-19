// Comment
// - used to create objects made from a bunch of other objects
// - used to create a complex object from simpler objects

// 1. Director   -> creates the object using the builder interface
// 2. Builder    -> interface for creating the parts of the final object
// 3. ConcreteBuilder -> implements the builder interface
// 4. Product    -> the final object that is created

#include <iostream>
#include <memory>
#include <string>

// Product: Computer
class Computer
{
public:
  void SetCPU(const std::string &cpu) { cpu_ = cpu; }
  void SetGPU(const std::string &gpu) { gpu_ = gpu; }
  void SetRAM(int ram) { ram_ = ram; }

  void ShowInfo()
  {
    std::cout << "CPU: " << cpu_ << ", GPU: " << gpu_ << ", RAM: " << ram_
              << "GB" << std::endl;
  }

private:
  std::string cpu_;
  std::string gpu_;
  int ram_ = 0;
};

// Abstract Builder
class ComputerBuilder
{
public:
  virtual ~ComputerBuilder() = default;
  virtual void BuildCPU() = 0;
  virtual void BuildGPU() = 0;
  virtual void BuildRAM() = 0;
  virtual std::unique_ptr<Computer> GetComputer() = 0;
};

// Concrete Builder for a Gaming Computer
class GamingComputerBuilder : public ComputerBuilder
{
public:
  GamingComputerBuilder() : computer_(std::make_unique<Computer>()) {}

  void BuildCPU() override { computer_->SetCPU("High-end Gaming CPU"); }
  void BuildGPU() override { computer_->SetGPU("High-end Gaming GPU"); }
  void BuildRAM() override { computer_->SetRAM(16); }

  std::unique_ptr<Computer> GetComputer() override
  {
    return std::move(computer_);
  }

private:
  std::unique_ptr<Computer> computer_;
};

// Concrete Builder for a Work Computer
class WorkComputerBuilder : public ComputerBuilder
{
public:
  WorkComputerBuilder() : computer_(std::make_unique<Computer>()) {}

  void BuildCPU() override { computer_->SetCPU("Office-grade CPU"); }
  void BuildGPU() override { computer_->SetGPU("Integrated Graphics"); }
  void BuildRAM() override { computer_->SetRAM(8); }

  std::unique_ptr<Computer> GetComputer() override
  {
    return std::move(computer_);
  }

private:
  std::unique_ptr<Computer> computer_;
};

// Director
class ComputerDirector
{
public:
  std::unique_ptr<Computer> BuildComputer(ComputerBuilder &builder)
  {
    builder.BuildCPU();
    builder.BuildGPU();
    builder.BuildRAM();
    return builder.GetComputer();
  }
};

int main()
{
  ComputerDirector director;

  // Building a Gaming Computer
  GamingComputerBuilder gamingBuilder;
  auto gamingComputer = director.BuildComputer(gamingBuilder);
  std::cout << "Gaming Computer Configuration:" << std::endl;
  gamingComputer->ShowInfo();

  // Building a Work Computer
  WorkComputerBuilder workBuilder;
  auto workComputer = director.BuildComputer(workBuilder);
  std::cout << "\nWork Computer Configuration:" << std::endl;
  workComputer->ShowInfo();

  return 0;
}
