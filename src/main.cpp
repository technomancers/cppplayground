#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "todoConfig.h"
#include "main.h"

std::ostream &operator<<(std::ostream &os, const TodoItem &obj)
{
    os << "[";
    if (obj.m_completed)
    {
        os << "x";
    }
    else
    {
        os << " ";
    }
    os << "] " << obj.m_action;
    return os;
}

TodoList::~TodoList()
{
    for (int i = 0; i < m_list.size(); i++)
    {
        delete m_list[i];
    }
}

void TodoList::AddItem(TodoItem *item)
{

    m_list.push_back(item);
}

int TodoList::RemoveItem(int index)
{
    if (index >= m_list.size())
    {
        return 1;
    }
    m_list.erase(m_list.begin() + index);
    return 0;
}

int TodoList::ToggleItem(int index)
{
    if (index >= m_list.size())
    {
        return 1;
    }
    m_list[index]->Toggle();
    return 0;
}

std::ostream &operator<<(std::ostream &os, const TodoList &obj)
{
    for (int i = 0; i < obj.m_list.size(); i++)
    {
        os << *obj.m_list[i] << "\n";
    }
    return os;
}

int main(int argc, char *argv[])
{
    printVersion(argv[0]);
    TodoList foo;
    foo.AddItem(new TodoItem("Finish the list"));
    foo.AddItem(new TodoItem("Just Do it"));
    foo.ToggleItem(1);
    std::cout << foo;
}

// This is the definition of the function.
// This is used by the linker to link the declaration to the definition.
void printVersion(char *name)
{
    std::cout
        << name
        << " Version "
        << TODO_VERSION_MAJOR
        << "."
        << TODO_VERSION_MINOR
        << std::endl;
}

void printArgs(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }
}

void waitForNewLine()
{
    std::cin.get();
}

void writeTodoItem(std::string todo)
{
    std::fstream fs;
    fs.open(TODO_FILE, std::fstream::app);
    fs << "[ ] " << todo << std::endl;
    fs.close();
}

void printTodos()
{

    std::vector<std::string> *todos = readTodoItems();
    for (int i = 0; i < todos->size(); i++)
    {
        std::cout << (*todos)[i] << std::endl;
    }

    delete todos;
}

std::vector<std::string> *readTodoItems()
{
    std::fstream fs;
    fs.open(TODO_FILE, std::fstream::in);
    std::vector<std::string> *todos = new std::vector<std::string>;
    for (std::string todo; std::getline(fs, todo);)
    {
        todos->push_back(todo);
    }
    return todos;
}

void markTodoDone(std::string todo)
{
    std::fstream orig, tmp;

    // Write to tmp what original should look like
    orig.open(TODO_FILE, std::fstream::in);
    tmp.open(TODO_FILE_TMP, std::fstream::out);
    for (std::string line; std::getline(orig, line);)
    {
        std::string sub = line.substr(4);
        if (sub == todo)
        {
            tmp << "[x] " << sub << std::endl;
        }
        else
        {
            tmp << line << std::endl;
        }
    }
    orig.close();
    tmp.close();

    // Overwrite original with tmp
    std::remove(TODO_FILE);
    std::rename(TODO_FILE_TMP, TODO_FILE);
}
