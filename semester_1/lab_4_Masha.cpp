#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstring>

// Поддержка русских букв (для Windows консоли)
char bufRus[256];
char* Rus(const char* text) {
    CharToOem(text, bufRus);
    return bufRus;
}

// Шаблон класса Stack<T>
template <class T>
class Stack {
    // Внутренний узел
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(0) {}
    };

    Node* top;

public:
    Stack() : top(0) {}
    ~Stack() { Clear(); }

    void Push(T value);
    T Pop();
    bool IsEmpty() const { return top == 0; }
    void Print() const;
    void Clear();
};

// Реализация методов шаблона Stack<T>

// Добавление элемента в стек
template <class T>
void Stack<T>::Push(T value) {
    Node* p = new Node(value);
    p->next = top;
    top = p;
}

// Удаление элемента
template <class T>
T Stack<T>::Pop() {
    if (IsEmpty()) {
        std::cout << Rus("Стек пуст!") << std::endl;
        return T();
    }
    Node* p = top;
    T value = p->data;
    top = top->next;
    delete p;
    return value;
}

// Вывод содержимого стека
template <class T>
void Stack<T>::Print() const {
    if (IsEmpty()) {
        std::cout << Rus("Стек пуст!") << std::endl;
        return;
    }
    Node* p = top;
    std::cout << Rus("Содержимое стека (сверху вниз):") << std::endl;
    while (p) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

// Очистка стека
template <class T>
void Stack<T>::Clear() {
    while (!IsEmpty()) Pop();
}

// Функции для тестирования различных типов
void StackForInt() {
    Stack<int> s;
    int choice;
    while (true) {
        std::cout << "\n-------------------------------\n";
        std::cout << "0. Push элемент\n";
        std::cout << "1. Pop элемент\n";
        std::cout << "2. Показать стек\n";
        std::cout << "3. Очистить стек\n";
        std::cout << "4. Назад\n";
        std::cout << "-------------------------------\n";
        std::cout << Rus("Выберите пункт меню: ");
        std::cin >> choice;

        switch (choice) {
        case 0: {
            int val;
            std::cout << Rus("Введите целое число: ");
            std::cin >> val;
            s.Push(val);
            break;
        }
        case 1: {
            int val = s.Pop();
            std::cout << Rus("Удален элемент: ") << val << std::endl;
            getch();
            break;
        }
        case 2:
            s.Print();
            getch();
            break;
        case 3:
            s.Clear();
            std::cout << Rus("Стек очищен!") << std::endl;
            getch();
            break;
        case 4:
            return;
        default:
            std::cout << Rus("Неверный пункт меню!") << std::endl;
        }
    }
}

void StackForFloat() {
    Stack<float> s;
    int choice;
    while (true) {
        std::cout << "\n-------------------------------\n";
        std::cout << "0. Push элемент\n";
        std::cout << "1. Pop элемент\n";
        std::cout << "2. Показать стек\n";
        std::cout << "3. Очистить стек\n";
        std::cout << "4. Назад\n";
        std::cout << "-------------------------------\n";
        std::cout << Rus("Выберите пункт меню: ");
        std::cin >> choice;

        switch (choice) {
        case 0: {
            float val;
            std::cout << Rus("Введите вещественное число: ");
            std::cin >> val;
            s.Push(val);
            break;
        }
        case 1: {
            float val = s.Pop();
            std::cout << Rus("Удален элемент: ") << val << std::endl;
            getch();
            break;
        }
        case 2:
            s.Print();
            getch();
            break;
        case 3:
            s.Clear();
            std::cout << Rus("Стек очищен!") << std::endl;
            getch();
            break;
        case 4:
            return;
        default:
            std::cout << Rus("Неверный пункт меню!") << std::endl;
        }
    }
}

void StackForDouble() {
    Stack<double> s;
    int choice;
    while (true) {
        std::cout << "\n-------------------------------\n";
        std::cout << "0. Push элемент\n";
        std::cout << "1. Pop элемент\n";
        std::cout << "2. Показать стек\n";
        std::cout << "3. Очистить стек\n";
        std::cout << "4. Назад\n";
        std::cout << "-------------------------------\n";
        std::cout << Rus("Выберите пункт меню: ");
        std::cin >> choice;

        switch (choice) {
        case 0: {
            double val;
            std::cout << Rus("Введите число (double): ");
            std::cin >> val;
            s.Push(val);
            break;
        }
        case 1: {
            double val = s.Pop();
            std::cout << Rus("Удален элемент: ") << val << std::endl;
            getch();
            break;
        }
        case 2:
            s.Print();
            getch();
            break;
        case 3:
            s.Clear();
            std::cout << Rus("Стек очищен!") << std::endl;
            getch();
            break;
        case 4:
            return;
        default:
            std::cout << Rus("Неверный пункт меню!") << std::endl;
        }
    }
}

// Главное меню
int main() {
    int choice;
    while (true) {
        std::cout << "\n=============================\n";
        std::cout << "   Лабораторная №4 — Шаблоны классов\n";
        std::cout << "=============================\n";
        std::cout << "0. Стек <int>\n";
        std::cout << "1. Стек <float>\n";
        std::cout << "2. Стек <double>\n";
        std::cout << "3. Выход\n";
        std::cout << "=============================\n";
        std::cout << Rus("Выберите пункт меню: ");
        std::cin >> choice;

        switch (choice) {
        case 0: StackForInt(); break;
        case 1: StackForFloat(); break;
        case 2: StackForDouble(); break;
        case 3:
            std::cout << Rus("Выход из программы...") << std::endl;
            return 0;
        default:
            std::cout << Rus("Неверный пункт меню!") << std::endl;
        }
    }
}