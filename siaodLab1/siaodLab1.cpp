/*Лабораторная работа №1 Тема: стеки и очереди*/
/*Наглый программист превращает очередь в больнице в стек*/

#include <iostream>
#include <fstream>
using namespace std;

struct deystv
{
    char znak; //знак действия
    int sym; //число (1/0/-1)
};



class Stack {
protected:
    deystv* m_data;
    int size;

private:
    void copy(const Stack& other) {
        this->size = other.size;
        deystv* newStack = new deystv[this->size];
        for (int i = 0; i < this->size; i++)
            newStack[i] = other.m_data[i];
        if (this->m_data != nullptr) delete[] this->m_data;
        this->m_data = newStack;
    }

public:
    Stack() { //стандартный конструктор
        this->m_data = nullptr;
        this->size = 0;
    }

    Stack(const Stack& other) { // конструктор копирования
        copy(other);
    }


    ~Stack() { //деструктор
        if (this->m_data != nullptr) delete[] this->m_data;
    }

    Stack& operator=(const Stack& other) //подмена понятий
    {
        copy(other);
        return *this;
    }

    void Push(deystv a) { //добавить элемент
        deystv* newStack = new deystv[this->size + 1];
        if (this->m_data != nullptr) {
            for (int i = 0; i < this->size; i++)
                newStack[i] = this->m_data[i];
            delete[] this->m_data;
        }
        this->m_data = newStack;
        this->size++;
        this->m_data[this->size - 1] = a;
    }

    deystv Pop() { //убрать элемент
        if (this->size <= 0) throw "выход за границы";
        deystv a = m_data[this->size - 1];
        if (this->size == 1) {
            delete[] this->m_data;
            this->m_data = nullptr;
        }
        else {
            deystv* newStack = new deystv[this->size - 1];
            for (int i = 0; i < this->size - 1; i++)
                newStack[i] = this->m_data[i];
            delete[] this->m_data;
            this->m_data = newStack;
        }
        this->size--;
        return a;
    }

    deystv Top() { // проверить верхний элемент
        if (this->size <= 0) throw "выход за границы";
        return m_data[this->size - 1];
    }

    bool IsEmpty() { // проверка на пустоту
        return (this->m_data != nullptr) ? false : true;
    }
};

class Queue : public Stack {
public:
    void Push(deystv a) { //добавить элемент
        deystv* newStack = new deystv[this->size + 1];
        if (this->m_data != nullptr) {
            for (int i = 1; i < this->size + 1; i++)
                newStack[i] = this->m_data[i - 1];
            delete[] this->m_data;
        }
        this->m_data = newStack;
        this->size++;
        this->m_data[0] = a;
    }

};

string readStr(string fileName) {
    string s = "";
    fstream inOut;
    inOut.open(fileName, ios::in);
    char mem = NULL;
    while (!inOut.eof()) {
        if (mem != NULL)
            s += mem;
        inOut >> mem;
    }
    inOut.close();
    return s;
}

bool resh(string s) {
    Stack stack;
    deystv d; d.sym = -1; d.znak = NULL;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            stack.Push(d);
            d.sym = -1; d.znak = NULL;
        }
        else if ((s[i] == 'F') || (s[i] == 'T')) {
            bool znach;
            if (s[i] == 'F') {
                znach = 0;
            }
            else {
                znach = 1;
            }
            if (d.znak == NULL) {
                d.sym = znach;
            }
            else {
                if (d.znak == '-') {
                    d.sym = !znach;
                }
                else if (d.znak == '&') {
                    d.sym = d.sym && znach;
                }
                else if (d.znak == '|') {
                    d.sym = d.sym || znach;
                }
            }
            d.znak = NULL;
        }
        else if (s[i] == '-') {
            d.znak = '-';
        }
        else if (s[i] == '&') {
            d.znak = '&';
        }
        else if (s[i] == '|') {
            d.znak = '|';
        }
        else if (s[i] == ')') {
            deystv mem = stack.Pop();
            if (mem.znak == '-') {
                d.sym = !d.sym;
            }
            else if (mem.znak == '&') {
                d.sym = d.sym && mem.sym;
            }
            else if (mem.znak == '|') {
                d.sym = d.sym || mem.sym;
            }
            d.znak = NULL;
        }
    }
    return d.sym;
}


int main()
{
    
    string F = readStr("text.txt");
    cout << F << endl;
    cout << resh(F);
    //Queue q;
    //q.Push(1);
    //q.Push(2);
    //q.Push(3);
    //q.Push(4);
    //q.Pop();
    //Queue z(q);
    //z.Push(10);
    //q.Push(11);
    //q.print();
    //z.print();
    
}
