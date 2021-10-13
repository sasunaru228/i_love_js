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
        while (param -> next != last) {
            param = param -> next;
        }
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
            count = 0;
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
            queue.pushFirst(' ');
            if (stack.getSize() == 0 || stack.last() == '('){
                stack.push(value[i]);
            }
            else if ((value[i] == '*' || value[i] == '/') && (stack.last() == '+' || stack.last() == '-') ){
                stack.push(value[i]);
            }
            else {
                do {
                    queue.pushFirst(stack.pop());
                }
                while(stack.getSize() != 0 && (stack.last() == '(' || ((stack.last() == '*' || stack.last() == '/') && (value[i] == '+' || value[i] == '-'))));
                stack.push(value[i]);
            }
        }
        else if (value[i] == '('){
            stack.push(value[i]);
        }
        else if (value[i] == ')'){
            while (stack.last() != '('){
                queue.pushFirst(stack.pop());
            }
            stack.pop();
        }

    }

    value = "";
    while (!queue.isEmpty()){
        char newChar = queue.removeLast();
        value = value + newChar;
    }
    while (stack.getSize() != 0){
        char newOpr = stack.pop();
        value = value + " " + newOpr;
    }
    // костыль
    for (int k = 0; k < value.length(); k++){
        if (((value[k] >= '0' && value[k] <= '9') && (value[k+1] == '+' || value[k+1] == '-' || value[k+1] == '*' || value[k+1] == '/' )) || ((value[k] == '+' || value[k] == '-' || value[k] == '*' || value[k] == '/' ) && (value[k+1] >= '0' && value[k+1] <= '9'))){
            value.insert(k+1, " ");
            k++;
            continue;
        }
    }
    // конец костыля
    return value;
}

int postFixtoResult(string str){
    Stack stack;
    for (int i = 0; i < str.length(); i++){
        if (str[i] >= '0' && str[i] <= '9'){
            int j = i;
            int num = 0;
            string result = "";
            do {
                result = result + str[j];
                j++;
            }
            while (str[j] != ' ');
            for (int k = 0; k < result.length(); k++){
                num = num + (int(result[k] - '0') * pow(10, result.length() - 1));
            }
            if (num != 0) stack.push(num);
        }
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'){
            if (str[i] == '+'){
                int res = stack.pop();
                stack.push(stack.pop() + res);
            }
            if (str[i] == '-'){
                int res = stack.pop();
                stack.push(stack.pop() - res);
            }
            if (str[i] == '*'){
                int res = stack.pop();
                int res1 = stack.pop();
                int result = res1 * res;
                stack.push(result);
            }
            if (str[i] == '/'){
                int res = stack.pop();
                stack.push(stack.pop() / res);
            }
        }
    }
    return stack.getNumber(0);
}


int main() {
    string primer = "3+4";
    cout << "Входящая строка - " << primer << endl;
    cout << postFix(primer) << endl;
    cout << "result - " << postFixtoResult(postFix(primer));
    return 0;


}
