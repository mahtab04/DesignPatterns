// Builder Design Pattern
// - used to create objects made from a bunch of other objects
// - used to create a complex object from simpler objects

//1. Director-> creates the object using the builder interface
//2. Builder-> interface for creating the parts of the final object
//3. ConcreteBuilder-> implements the builder interface
//4. Product-> the final object that is created


//Steps to create a builder design pattern
// 1. Create a builder class
// 2. Create a director class
// 3. Create a product class
// 4. Create a builder interface
// 5. Create a concrete builder class

#include <iostream>
#include <string>

// Product: Computer
class Computer
{
public:
    void SetCPU(const std::string &cpu)
    {
        cpu_ = cpu;
    }
    void SetGPU(const std::string &gpu)
    {
        gpu_ = gpu;
    }
    void SetRAM(int ram)
    {
        ram_ = ram;
    }

    void ShowInfo()
    {
        std::cout << "CPU: " << cpu_ << ", GPU: " << gpu_ << ", RAM: " << ram_ << "GB" << std::endl;
    }

private:
    std::string cpu_;
    std::string gpu_;
    int ram_;
};

// Abstract Builder
class ComputerBuilder
{
public:
    virtual void BuildCPU() = 0;
    virtual void BuildGPU() = 0;
    virtual void BuildRAM() = 0;
    virtual Computer GetComputer() = 0;
};

// Concrete Builder for a Gaming Computer
class GamingComputerBuilder : public ComputerBuilder
{
public:
    void BuildCPU() override
    {
        computer_.SetCPU("High-end Gaming CPU");
    }

    void BuildGPU() override
    {
        computer_.SetGPU("High-end Gaming GPU");
    }

    void BuildRAM() override
    {
        computer_.SetRAM(16);
    }

    Computer GetComputer() override
    {
        return computer_;
    }

private:
    Computer computer_;
};

// Concrete Builder for a Work Computer
class WorkComputerBuilder : public ComputerBuilder
{
public:
    void BuildCPU() override
    {
        computer_.SetCPU("Office-grade CPU");
    }

    void BuildGPU() override
    {
        computer_.SetGPU("Integrated Graphics");
    }

    void BuildRAM() override
    {
        computer_.SetRAM(8);
    }

    Computer GetComputer() override
    {
        return computer_;
    }

private:
    Computer computer_;
};

// Director
class ComputerDirector
{
public:
    Computer BuildComputer(ComputerBuilder &builder)
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
    Computer gamingComputer = director.BuildComputer(gamingBuilder);
    std::cout << "Gaming Computer Configuration:" << std::endl;
    gamingComputer.ShowInfo();

    // Building a Work Computer
    WorkComputerBuilder workBuilder;
    Computer workComputer = director.BuildComputer(workBuilder);
    std::cout << "\nWork Computer Configuration:" << std::endl;
    workComputer.ShowInfo();

    return 0;
}
