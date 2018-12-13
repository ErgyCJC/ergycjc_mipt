#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Stack
{
public:
    Stack();

    ~Stack();

    void push_back(char key);

    char pop_back();

    char getTop();

    bool isEmpty();

    void reverse();

private:
    char* buffer;
    int size;
    int buffer_size;

};

class Dequeu
{
public:
    Dequeu(){}
    ~Dequeu(){}

    void push_back(char key){ back.push_back(key); }

    void push_front(char key){ front.push_back(key); }

    void print()
    {
        while(!front.isEmpty())
            cout << front.pop_back();
        back.reverse();
        while(!back.isEmpty())
            cout << back.pop_back();
    }
private:
    Stack front;
    Stack back;
};

bool isOpenBracket(char x)
{
    return (x == '[' || x == '(' || x == '{');
}

char neg(char x)
{
    if(x == '[')
        return ']';
    if(x == ']')
        return '[';
    if(x == '(')
        return ')';
    if(x == ')')
        return '(';
    if(x == '{')
        return '}';
    if(x == '}')
        return '{';
    return '\0';
}

int main(int argc, char ** argv)
{
    string line;
    Stack checker;
    Dequeu result;
    bool possible = true;

    cin >> line;
    for(int i = 0; i < line.size() && possible; ++i)
    {
        char t = line[i];

        if(isOpenBracket(t))
        {
            result.push_back(t);
            checker.push_back(t);
        }
        else if(checker.isEmpty())
        {
            result.push_back(t);
            result.push_front(neg(t));
        }
        else if(checker.getTop() == neg(t))
        {
            result.push_back(t);
            checker.pop_back();
        }
        else
        {
            possible = false;
        }
    }

    if(possible)
    {
        while(!checker.isEmpty())
            result.push_back(neg(checker.pop_back()));
        
        result.print();
    }
    else
        cout << "IMPOSSIBLE";
    return 0;
}

Stack::Stack(): size(0), buffer_size(1)
{
    buffer = new char[buffer_size];
}

Stack::~Stack()
{
    delete[] buffer;
}

void Stack::push_back(char key)
{
    if(size == buffer_size)
    {
        char* tmp_buffer = new char[buffer_size * 2];
        for(int i = 0; i < size; ++i)
            tmp_buffer[i] = buffer[i];

        buffer_size *= 2;
        delete[] buffer;
        buffer = tmp_buffer;
    }

    buffer[size] = key;
    ++size;
}

char Stack::pop_back()
{
    char result = buffer[size - 1];
    --size;
    return result;
}

bool Stack::isEmpty()
{
    return size == 0;
}

char Stack::getTop()
{
    return buffer[size - 1];
}

void Stack::reverse()
{
    for(int i = 0; i < size / 2; ++i)
    {
        char t = buffer[i];
        buffer[i] = buffer[size - 1 - i];
        buffer[size - 1 - i] = t;
    }
}