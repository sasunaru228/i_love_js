//
//  main.cpp
//  i-Love-Js/Node.js
//
//  Created by Дмитрий Орлов on 07.09.2021.
//  MacBook 13inch 2017
//

#include <iostream>
#include <cmath>
#include <utility>

using namespace std;



struct Node {
    int value;
    Node* next;
    explicit Node(int value) : value(value), next(nullptr) {}
};
class List{
    Node* first;
    Node* last;
public:
    List() : first(nullptr), last(nullptr){}

    bool isEmpty(){
        return first == nullptr;
    }
    void pushLast(int value){
        Node* param = new Node(value);
        if (isEmpty()){
            first = param;
            last = param;
            return;
        }
        last -> next = param;
        last = param;
    }
    void pushFirst(int value){
        Node* param = new Node(value);

        if (isEmpty()){
            first = param;
            last = param;
            return;
        }
        param -> next = first;
        first = param;
    }
    void show(){
        if (isEmpty()){
            return;
        }
        Node* param = first;
        while (param) {
            cout << param -> value << " ";
            param = param -> next;
        }
        cout << endl;
    }

    int removeFirst() {
        if (isEmpty()) return 0;
        Node* param = first;
        first = param -> next;
        int xxx = param -> value;
        delete param;
        return xxx;
    }
    int removeLast() {
        if (isEmpty()) return 0;
        if (first == last) {
            return removeFirst();
        }
        Node* param = first;
        while (param -> next != last) param = param -> next;
        param -> next = nullptr;
        int xxx = last -> value;
        delete last;
        last = param;
        return xxx;
    }
    int getSize(){
        int count = 0;
        Node* param = first;
        if (isEmpty()) return count;
        while (param) {
            param = param -> next;
            count++;
        }
        return count;
    }
    Node* operator[] (int id){
        if (isEmpty()) return nullptr;
        Node* value = first;
        for (int i = 0; i < id; i++) {
            value = value -> next;
            if (!value) return nullptr;
        }
        return value;
    }
    void removeId(int id) {
        if (isEmpty()) return;
        if (first == last) {
            removeFirst();
            return;
        }
        if (id == 0){
            removeFirst();
            return;
        }
        Node* prev = nullptr;
        Node* next = nullptr;
        Node* now = nullptr;
        Node* param = first;
        for (int i = 0; i <= (id + 1); i++){
            //            cout << param << endl;
            if (param == nullptr) {
                break;
            }
            if (i == (id - 1)){
                prev = param;
            }
            if (i == id){
                now = param;
            }
            if (i == (id + 1)){
                next = param;
            }
            param = param -> next;
        }
        if (next == nullptr){
            removeLast();
            return;
        }
        prev -> next = next;
        cout << "удален элемент по интексу[" << id << "] со значением - " << now -> value << endl;
        delete now;
    }
    void insertInto(int id, int value){
        if (isEmpty()) return;
        if (id == 0) {
            pushFirst(value);
            return;
        }
        Node* prev = nullptr;
        Node* next = nullptr;
        Node* param = first;
        for (int i = 0; i <= (id + 1); i++){
            if (param == nullptr) {
                break;
            }
            if (i == (id - 1)){
                prev = param;
            }
            if (i == id){
                next = param;
            }
            param = param -> next;
        }
        if (prev == nullptr) {
            cout << "невозможно добавить элемент на столь далекий индекс" << endl;
            return;
        }
        if (next == nullptr){
            pushLast(value);
            return;
        }
        Node* creation = new Node(value);
        creation -> next = next;
        prev -> next = creation;
    }
};


class Stack{
public:
    void push(int value){
        if (count == 0){
            mass = (int *)malloc(sizeof(int) * capacity);
            mass[0] = value;
            count++;
        }
        else {
            count++;
            if (count == capacity) resize();
            mass[count - 1] = value;
        }
    }
    int pop(){
        int value;
        if (count == 0) {
            return 0;
        }
        if (count == 1) {
            value = mass[0];
            mass = nullptr;
            return value;
        }

        value = mass[count - 1];
        count--;
        limit = capacity - (count * int((1 + sqrt(5)) / 2));
        if (count < limit) resize();
        return value;
    }
    int getSize() {
        return count;
    }
    int last(){
        return getNumber(count - 1);
    }
    int getNumber(int id){
        if (id >= count){
            return 0;
        }
        else{
            return mass[id];
        }
    }
    void show(){
        for (int i = 0; i < count; i++){
            cout << mass[i] << " ";
        }
        cout << endl;
    }
    void resize(){
        capacity = count * int((1 + sqrt(5)) / 2);
        mass = (int *)realloc(mass, sizeof(int) * capacity);
    }

private:
    int *mass = nullptr;
    int count = 0;
    int capacity = 10;
    int limit = 0;
};


string postFix(string value){
    List queue;
    Stack stack;
    for (int i = 0; i < value.length(); i++){
        if (value[i] >= '0' && value[i] <= '9'){
            queue.pushFirst(value[i]);
            continue;
        }
        else if (value[i] == '+' || value[i] == '-' || value[i] == '*' || value[i] == '/'){
            if (stack.getSize() == 0 || stack.last() == '('){
                stack.push(value[i]);
            }
            else if ((value[i] == '*' || value[i] == '/') && (stack.last() == '+' || stack.last() == '-') ){
                stack.push(value[i]);
            }
            else {
                while(stack.getSize() != 0 ){
                    if (stack.last() == '(' || ((stack.last() == '*' || stack.last() == '/') && (value[i] == '+' || value[i] == '-')) ){//доделать
                        stack.push(value[i]);
                        break;
                    }
                    queue.pushFirst(stack.pop());

                }
            }
        }

    }

    while (!queue.isEmpty()){
        char newChar = queue.removeFirst();
        value = value + newChar;
    }

    return value;
}



int main() {
    Stack obj;
    obj.push(1);
    obj.push(2);
    obj.push(20);
    obj.push(25);
    cout << obj.getNumber(3) << "\n";
    obj.show();
    obj.pop();
    obj.show();
    cout << obj.getSize() << endl;
    cout << obj.getNumber(3) << "\n";
    cout << "last - " << obj.last() << endl;

    List obj2;
    obj2.pushLast(5);
    obj2.pushLast(10);
    obj2.pushLast(20);
    obj2.pushLast(99999);
    obj2.pushLast(35);
    obj2.pushLast(99);
    obj2.pushLast(228);
    obj2.pushLast(322);
    obj2.show();
    obj2.removeFirst();
    obj2.pushFirst(26);
    obj2.pushFirst(10);
    obj2.pushFirst(2000);
    obj2.show();
    obj2.removeId(2);
    obj2.show();
    obj2.insertInto(43, 26102000);
    obj2.show();
    cout << obj2.getSize() << endl;
    cout << obj2[0] -> value << endl;

    string primer = "3+4";
    cout << postFix(primer);
    return 0;


}
