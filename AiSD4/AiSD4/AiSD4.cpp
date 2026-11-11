#include <iostream>
#include <stdexcept>
#include <locale>
//7 вариант средний уровень
template <typename T> //узлы + ссылки на пред и след элементы
struct DNode {
    T data;
    DNode<T>* prev;
    DNode<T>* next;
    DNode(const T& value) : data(value), prev(nullptr), next(nullptr) {} //конструктор
};

template <typename T> //список + ссылки на начало и конец списка
class DoublyLinkedList {
private:
    DNode<T>* head;
    DNode<T>* tail;
    int count; //кол-во элементов

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {} //конструктор

    ~DoublyLinkedList() {
        clear();
    }

    void push_back(const T& value) { //добавление элемента + случаи
        DNode<T>* newNode = new DNode<T>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    void pop_back() { //удаление элемента
        if (tail == nullptr) throw std::underflow_error("List is empty");
        DNode<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        count--;
    }

    void rotateRight(int k) { //функция из задания
        if (head == nullptr || k <= 0) return;
        k = k % count;
        for (int i = 0; i < k; ++i) {
            DNode<T>* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            temp->prev = nullptr;
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }

    void print() const { //вывод
        DNode<T>* current = head;
        std::cout << "[";
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) std::cout << ", ";
            current = current->next;
        }
        std::cout << "]" << std::endl;
    }

    void printReverse() const { //вывод иначе
        DNode<T>* current = tail;
        std::cout << "[";
        while (current != nullptr) {
            std::cout << current->data;
            if (current->prev != nullptr) std::cout << ", ";
            current = current->prev;
        }
        std::cout << "]" << std::endl;
    }

    void clear() { //удаление списка
        while (head != nullptr) {
            DNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
    //два вспомогательных метода
    int size() const {
        return count;
    }

    bool empty() const {
        return head == nullptr;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    DoublyLinkedList<int> list;

    for (int i = 1; i <= 5; i++) {
        list.push_back(i * 10);//10 20 30 40 50
    }

    std::cout << "== Двусвязный список ==" << std::endl;
    std::cout << "Исходный список: ";
    list.print();

    int k;
    std::cout << "Введите k для сдвига вправо: ";
    std::cin >> k;

    list.rotateRight(k);

    std::cout << "После сдвига вправо на " << k << ": ";
    list.print();

    return 0;
}