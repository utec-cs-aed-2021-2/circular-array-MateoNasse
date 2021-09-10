#pragma once

#include <iostream>

using namespace std;

template <typename T>
void print(T* array, int n){
    for (int i = 0; i < n; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

template <typename T>
class CircularArray {
    T* array;
    int capacity;
    int front_t;
    int rear_t;
public:
    void print_it(){
        cout << "front: " << front_t << endl;
        cout << "rear: " << rear_t << endl;
    }

    CircularArray(int c){
        front_t = -1;
        rear_t = -1;
        capacity = c;
        array = new T[capacity];
    };

    T next(T data){
        return (data + 1) % capacity;
    }

    T prev(T index){
        return (index == 0) ? capacity - 1 : index - 1;
    }

    int size(){
        if (front_t == -1){
            return 0;
        }
        else if (rear_t == front_t){
            return 1;
        }
        else if (rear_t > front_t){
            return rear_t - front_t + 1;
        }
        else {
            return (capacity - front_t) + rear_t + 1;
        }
    }

    bool empty(){
        if (front_t == -1 && rear_t == - 1){
            return true;
        }
        return false;
    }

    bool full(){
        if (next(rear_t) == front_t){
            return true;
        }
        return false;
    }

    void cool(){
        cout << "COOL " <<front_t << endl;
    }

    T front(){
        return array[front_t];
    }

    T rear(){
        return array[rear_t];
    }

    void push_front(T data){
        if (full()){
            cout << "Queue is full, cannot push " << data << "." << endl;
            return;
        }
        else {
            if (front_t == -1){
                front_t = 0;
                rear_t = 0;
            }
            else if (front_t == 0){
                front_t = capacity - 1;
            }
            else {
                front_t--;
            }
            array[front_t] = data;
        }
    }

    void push_back(T data){
        if (full()){
            cout << "Queue is full, cannot push " << data << "." << endl;
            return;
        }
        if (front_t == -1){
            front_t = 0;
            rear_t = 0;
        }
        else if (rear_t == capacity - 1){
            rear_t = 0;
        }
        else {
            rear_t++;
        }
        array[rear_t] = data;
    }

    void pop_front(){
        if (empty()){
            cout << "Queue is empty, cannot pop front.\n";
        }
        if (front_t == rear_t){
            front_t = -1;
            rear_t = -1;
        }
        else {
            if (front_t == capacity - 1){
                front_t = 0;
            }
            else {
                front_t++;
            }
        }
    }

     void pop_back(){
        if (empty()){
            cout << "Queue is empty, cannot pop front.\n";
        }
        else {
            if (rear_t == front_t){
                front_t = -1;
                rear_t = -1;
            }
            else if (rear_t == 0){
                rear_t = capacity - 1;
            }
            else {
                rear_t--;
            }
        }
    }

    void insert(int position, T data){
        if (full()){
            cout << "Queue is full, cannot insert.\n";
            return;
        }
        else if (position > capacity || position < 0){
            cout << "Cannot insert in that position.\n";
            return;
        }
        else if (abs(front_t - rear_t) < position - 1){
            cout << "Cannot insert in that position.\n";
            return;
        }
        else if (front_t == -1 && rear_t == -1){
            front_t = 0;
            rear_t = 0;
            array[front_t] = data;
        }
        else if (front_t > rear_t){
            bool inserted = false;
            T* temp = new T[capacity];
            int next_front = front_t;
            for (int i = 0; i < (capacity - front_t) + (rear_t) + 2; i++){
                if (i == position){
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
            if (rear_t == capacity){
                rear_t = 0;
            }
            else {
                rear_t++;
            }
            return;
        }

        else {
            bool inserted = false;
            T* temp = new T[capacity];
            int next_front = front_t;
            for (int i = 0; i < rear_t - front_t + 2; i++){
                if (i == position){
                    temp[front_t + position] = data;
                    inserted = true;
                }
                else if (!inserted){
                    temp[front_t + i] = array[front_t + i];
                }
                else {
                    temp[front_t + i] = array[front_t + i - 1];
                }
            }
            array = temp;
            if (rear_t == capacity){
                rear_t = 0;
            }
            else {
                rear_t++;
            }
            return;
        }
    }

    T& operator[](int index){
        if (index > capacity - 1 || index < 0){
            cout << "No existing element with that index.\n";
            exit(0);
        }
        int next_front = front_t;
        for (int i = 0; i < index; i++){
            next_front = next(next_front);
        }
        return array[next_front];
    }

    void clear(){
        delete[] array;
        front_t = -1;
        rear_t = -1;
        array = new T[capacity];
    }

    T* reverse(){
        T* ret_array = new T[capacity];
        int i = 0;
        int new_index = rear_t;
        while (new_index != front_t){
            ret_array[i] = array[new_index];
            new_index = prev(new_index);
            i++;
        }
        ret_array[i] = array[new_index];
        new_index = prev(new_index);
        return ret_array;
    }
};
