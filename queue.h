#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> {
    T *array;
    int capacity;
    int size;
public:
    QueueArray();
    QueueArray(int _capacity);
    void enqueue(T data);
    void dequeue();
    void display();
};

template <class T>
QueueArray<T>::QueueArray()
{
    QueueArray(0);
}

template <typename T>
QueueArray<T>::QueueArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    size = 0;
}

template <typename T>
void QueueArray<T>::enqueue(T data)
{
    if (size == capacity){
        cout << "Not enough capacity.\n";
    }
    else {
        array[size] = data;
    }
}

template <typename T>
void QueueArray<T>::dequeue()
{
    T* temp = new T[capacity];
    for (int i = 0; i < size - 1; i++){
        temp[i] = array[i + 1];
    }
    array = temp;
}

template <typename T>
void QueueArray<T>::display()
{
    for (int i = 0; i < size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}
