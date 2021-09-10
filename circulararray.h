#include <iostream>
#include "sort.h"
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray(); // done
    CircularArray(int _capacity); // done
    virtual ~CircularArray(); // done
    void push_front(T data); // done
    void push_back(T data); // done
    void insert(T data, int pos); // done
    T pop_front(); // done
    T pop_back(); // done
    bool is_full(); // done
    bool is_empty(); // done
    int size(); // done
    void clear(); // done
    T &operator[](int index); // done
    void sort();
    bool is_sorted();
    void reverse(); // done
    string to_string(string sep=" "); // done

private:
    int next(int); // done
    int prev(int); // done
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}

template <class T>
bool CircularArray<T>::is_full(){
    if (next(back) == front){
        return true;
    }
    return false;
}

template <class T>
bool CircularArray<T>::is_empty(){
    if (front == -1 && back == - 1){
        return true;
    }
    return false;
}

template <class T>
void CircularArray<T>::push_front(T data){
    if (is_full()){
        cout << "Queue is full, cannot push " << data << "." << endl;
        return;
    }
    else {
        if (front == -1){
            front = 0;
            back = 0;
        }
        else if (front == 0){
            front = capacity - 1;
        }
        else {
            front--;
        }
        array[front] = data;
    }
}

template <class T>
void CircularArray<T>::push_back(T data){
    if (is_full()){
        cout << "Queue is full, cannot push " << data << "." << endl;
        return;
    }
    if (front == -1){
        front = 0;
        back = 0;
    }
    else if (back == capacity - 1){
        back = 0;
    }
    else {
        back++;
    }
    array[back] = data;
}

template <class T>
T CircularArray<T>::pop_front(){
    if (is_empty()){
        cout << "Queue is empty, cannot pop front.\n";
        return 0;
    }
    if (front == back){
        front = -1;
        back = -1;
        return 0;
    }
    else {
        if (front == capacity - 1){
            front = 0;
            return 0;
        }
        else {
            front++;
            return 0;
        }
    }
}

template <class T>
T CircularArray<T>::pop_back(){
    if (is_empty()){
        cout << "Queue is empty, cannot pop front.\n";
        return 0;
    }
    else {
        if (back == front){
            front = -1;
            back = -1;
            return 0;
        }
        else if (back == 0){
            back = capacity - 1;
            return 0;
        }
        else {
            back--;
            return 0;
        }
    }
}
template <class T>
void CircularArray<T>::insert(T data, int pos){
    if (is_full()){
        cout << "Queue is full, cannot insert.\n";
        return;
    }
    else if (pos > capacity || pos < 0){
        cout << "Cannot insert in that position.\n";
        return;
    }
    else if (abs(front - back) < pos - 1){
        cout << "Cannot insert in that position.\n";
        return;
    }
    else if (front == -1 && back == -1){
        front = 0;
        back = 0;
        array[front] = data;
    }
    else if (front > back){
        bool inserted = false;
        T* temp = new T[capacity];
        int next_front = front;
        for (int i = 0; i < (capacity - front) + (back) + 2; i++){
            if (i == pos){
                temp[next_front] = data;
                inserted = true;
            }
            else if (!inserted){
                temp[next_front] = array[next_front];
                next_front = next(next_front);
            }
            else {
                int not_next_front = next_front;
                next_front = next(next_front);
                temp[next_front] = array[not_next_front];
            }
        }
        array = temp;
        if (back == capacity){
            back = 0;
        }
        else {
            back++;
        }
        return;
    }

    else {
        bool inserted = false;
        T* temp = new T[capacity];
        for (int i = 0; i < back - front + 2; i++){
            if (i == pos){
                temp[front + pos] = data;
                inserted = true;
            }
            else if (!inserted){
                temp[front + i] = array[front + i];
            }
            else {
                temp[front + i] = array[front + i - 1];
            }
        }
        array = temp;
        if (back == capacity){
            back = 0;
        }
        else {
            back++;
        }
        return;
    }
}

template <class T>
int CircularArray<T>::size(){
    if (front == -1){
        return 0;
    }
    else if (back == front){
        return 1;
    }
    else if (back > front){
        return back - front + 1;
    }
    else {
        return (capacity - front) + back + 1;
    }
}

template <class T>
void CircularArray<T>::clear(){
    delete[] array;
    front = -1;
    back = -1;
    array = new T[capacity];
}

template <class T>
T& CircularArray<T>::operator[](int index){
    if (index > capacity - 1 || index < 0){
        cout << "No existing element with that index.\n";
        exit(0);
    }
    int next_front = front;
    for (int i = 0; i < index; i++){
        next_front = next(next_front);
    }
    return array[next_front];
}


template <class T>
void CircularArray<T>::sort(){
    countingSortModified(this->array, size());
}


template <class T>
bool CircularArray<T>::is_sorted(){
    int s = size();
    for (int i = 1; i < s; i++){
        if (array[i - 1] > array[i]){
            return false;
        }
    }
    return true;
}

template <class T>
void CircularArray<T>::reverse(){
    T* ret_array = new T[capacity];
    int i = 0;
    int new_index = back;
    while (new_index != front){
        ret_array[i] = array[new_index];
        new_index = prev(new_index);
        i++;
    }
    ret_array[i] = array[new_index];
    array = ret_array;
}
