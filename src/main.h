#pragma once

// This declares that a function with this signature is defined somewhere.
// This is a compile time check.
void printVersion(char *name);
void printArgs(int argc, char *argv[]);
void waitForNewLine();
void printTodos();
void writeTodoItem(std::string todo);
std::vector<std::string> *readTodoItems();
void markTodoDone(std::string todo);

class TodoItem
{
private:
    std::string m_action;
    bool m_completed;

public:
    TodoItem() = delete;
    TodoItem(std::string action) : m_action(action), m_completed(false) {}
    TodoItem(std::string action, bool completed) : m_action(action), m_completed(completed) {}

    void Toggle() { m_completed = !m_completed; }
    friend std::ostream &operator<<(std::ostream &os, const TodoItem &obj);
};

class TodoList
{
private:
    std::vector<TodoItem *> m_list;

public:
    ~TodoList();
    void AddItem(TodoItem *item);
    int RemoveItem(int index);
    int ToggleItem(int index);
    friend std::ostream &operator<<(std::ostream &os, const TodoList &obj);
};
