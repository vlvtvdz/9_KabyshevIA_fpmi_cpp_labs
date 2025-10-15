#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include <cstring>

//Русский язык
char bufRus[256];
char* Rus(const char* text) {
    CharToOem(text, bufRus);
    return bufRus;
}


struct Node {
    double data;
    Node* next;
};


// Класс Stack — динамическая структура (стек)
class Stack {
public:
    Node* top;
    Stack() { top = 0; }
    ~Stack() { Clear(); }

    void Push(double value);
    double Pop();
    bool IsEmpty() { return top == 0; }
    void Print();
    void Clear();
};

// Добавление элемента в стек
void Stack::Push(double value) {
    Node* p = new Node;
    p->data = value;
    p->next = top;
    top = p;
}

// Извлечение элемента из стека
double Stack::Pop() {
    if (IsEmpty()) {
        std::cout << Rus("Стек пуст!") << std::endl;
        return 0;
    }
    Node* p = top;
    double value = p->data;
    top = top->next;
    delete p;
    return value;
}

// Вывод содержимого стека
void Stack::Print() {
    if (IsEmpty()) {
        std::cout << Rus("Стек пуст!") << std::endl;
        return;
    }
    Node* p = top;
    std::cout << Rus("Содержимое стека (сверху вниз):") << std::endl;
    while (p) {
        std::cout << std::fixed << std::setprecision(2) << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

// Очистка стека
void Stack::Clear() {
    while (!IsEmpty()) Pop();
}

// Класс Sequence — поиск возрастающих серий
class Sequence {
public:
    double arr[100];
    int n;
    Sequence() { n = 0; }

    void Input();
    void FindIncreasingSeries();
};

// Ввод последовательности
void Sequence::Input() {
    std::cout << Rus("Введите количество элементов: ");
    std::cin >> n;
    std::cout << Rus("Введите элементы (через пробел): ");
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
}

// Поиск возрастающих серий
void Sequence::FindIncreasingSeries() {
    if (n == 0) {
        std::cout << Rus("Последовательность пуста!") << std::endl;
        return;
    }

    std::cout << Rus("Возрастaющие серии:") << std::endl;
    int start = 0;
    while (start < n) {
        std::cout << Rus("Серия: ");
        std::cout << arr[start] << " ";
        int end = start;
        while (end + 1 < n && arr[end + 1] > arr[end]) {
            end++;
            std::cout << arr[end] << " ";
        }
        std::cout << std::endl;
        start = end + 1;
    }
}

// Меню
int Menu() {
    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "   0. Push элемент" << std::endl;
    std::cout << "   1. Pop элемент" << std::endl;
    std::cout << "   2. Показать стек" << std::endl;
    std::cout << "   3. Найти возрастающие серии" << std::endl;
    std::cout << "   4. Выход" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << Rus("Выберите пункт меню: ");
    int k;
    std::cin >> k;
    return k;
}

// Main 
int main() {
    Stack st;
    Sequence seq;
    int k;

    while (1) {
        k = Menu();
        switch (k) {
        case 0: {
            double x;
            std::cout << Rus("Введите число: ");
            std::cin >> x;
            st.Push(x);
            break;
        }
        case 1: {
            double val = st.Pop();
            if (!st.IsEmpty() || val != 0)
                std::cout << Rus("Удален элемент: ") << val << std::endl;
            break;
        }
        case 2: {
            st.Print();
            getch();
            break;
        }
        case 3: {
            seq.Input();
            seq.FindIncreasingSeries();
            getch();
            break;
        }
        case 4:
            std::cout << Rus("Выход из программы...") << std::endl;
            return 0;
        default:
            std::cout << Rus("Неверный пункт меню!") << std::endl;
        }
    }
}