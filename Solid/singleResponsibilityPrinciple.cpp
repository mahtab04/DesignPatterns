// Single Responsibility Principle
// A class should have only one reason to change, meaning that a class should have only one job.
// If a class has more than one responsibility, it becomes coupled. A change to one responsibility results to modification of the other responsibility.


#include <iostream>
#include <vector>
#include <string>

// Without SRP
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

    void displayTasks() {
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

// With SRP
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

class TaskUI {
public:
    static void displayTasks(const std::vector<std::string>& tasks) {
        for (const auto& task : tasks) {
            std::cout << task << std::endl;
        }
    }
};

class TaskInput {
public:
    static std::string inputTask() {
        std::string task;
        std::cout << "Enter a task: ";
        std::getline(std::cin, task);
        return task;
    }

    static std::string removeTask() {
        std::string task;
        std::cout << "Enter a task to remove: ";
        std::getline(std::cin, task);
        return task;
    }
};

int main() {
    TodoList todoList;
    TaskManager taskManager;

    // Without SRP
    todoList.inputTask();
    todoList.removeTask();
    todoList.displayTasks();

    // With SRP
    taskManager.addTask(TaskInput::inputTask());
    taskManager.deleteTask(TaskInput::removeTask());
    TaskUI::displayTasks(taskManager.getTasks());

    return 0;
}
