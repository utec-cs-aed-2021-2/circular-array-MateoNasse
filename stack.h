#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> {
    int *array;
    int capacity;
    int size;
public:
    StackArray();
    StackArray(int _capacity);
    void push(T data);
    int pop();
    void display();
};

template <class T>
StackArray<T>::StackArray()
{
    StackArray(0);
}

template <typename T>
StackArray<T>::StackArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    size = 0;
}

template <typename T>
void StackArray<T>::push(T data)
{
    T* temp = new T[capacity];
    temp[0] = data;
    for (int i = 0; i < size; i++){
        temp[i + 1] = array[i];
    }
    array = temp;
}

template <typename T>
T StackArray<T>::pop()
{
    T top = array[0];
    T* temp = new T[capacity];
    for (int i = 0; i < size - 1; i++){
        temp[i] = array[i + 1];
    }
    array = temp;
    return top;
}

template <typename T>
void StackArray<T>::display()
{
    for (int i = 0; i < size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}
