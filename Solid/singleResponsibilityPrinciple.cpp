// Single Responsibility Principle
// A class should have only one reason to change, meaning that a class should have only one job.
// If a class has more than one responsibility, it becomes coupled. A change to one responsibility results to modification of the other responsibility.


#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

// Reference Only (Without SRP)
// Kept for interview explanation: this class mixes business logic, input, and output.
// Not used in main().
class TodoList {
private:
    std::vector<std::string> todos;

public:
    void addTask(const std::string& task) {
        todos.push_back(task);
    }

    void deleteTask(const std::string& task) {
        todos.erase(std::remove(todos.begin(), todos.end(), task), todos.end());
    }

    void displayTasks() const {
        for (const auto& task : todos) {
            std::cout << task << std::endl;
        }
    }

    void inputTask() {
        std::string task;
        std::cout << "Enter a task: ";
        std::getline(std::cin, task);
        addTask(task);
    }

    void removeTask() {
        std::string task;
        std::cout << "Enter a task to remove: ";
        std::getline(std::cin, task);
        deleteTask(task);
    }
};

// SRP: Handles only task state and business operations.
class TaskManager {
private:
    std::vector<std::string> todos;

public:
    void addTask(const std::string& task) {
        todos.push_back(task);
    }

    void deleteTask(const std::string& task) {
        todos.erase(std::remove(todos.begin(), todos.end(), task), todos.end());
    }

    const std::vector<std::string>& getTasks() const {
        return todos;
    }
};

// SRP: Handles only output/presentation.
class TaskUI {
public:
    static void displayTasks(const std::vector<std::string>& tasks) {
        if (tasks.empty()) {
            std::cout << "No tasks available." << std::endl;
            return;
        }

        std::cout << "Current Tasks:" << std::endl;
        for (const auto& task : tasks) {
            std::cout << "- " << task << std::endl;
        }
    }
};

// SRP: Handles only input collection.
class TaskInput {
public:
    static std::string inputTask() {
        std::string task;
        std::cout << "Enter a task: ";
        std::getline(std::cin, task);
        return task;
    }

    static std::string inputTaskToRemove() {
        std::string task;
        std::cout << "Enter a task to remove: ";
        std::getline(std::cin, task);
        return task;
    }
};

int main() {
    TaskManager taskManager;

    // Add one task, remove one task, then display.
    taskManager.addTask(TaskInput::inputTask());
    taskManager.deleteTask(TaskInput::inputTaskToRemove());
    TaskUI::displayTasks(taskManager.getTasks());

    return 0;
}
