/*
과제 3

체인이 프로그램 4.6과 같이 정의되었다고 가정한다.
C++ 템플릿 클래스 Chain<T>를 완전히 코딩하고 테스트하라.
1) - 13)을 구현해야 한다. 단, 원소는 0번째부터 시작한다고 가정한다.
1) 초기에 공백 체인을 생성하는 생성자
2) 체인의 모든 원소를 삭제하는 소멸자
3) 체인의 맨 앞에 삽입하는 함수
4) 체인의 맨 뒤에 삽입하는 함수
5) 리스트의 첫 번째 원소를 반환하는 Front 함수
6) 리스트의 마지막 원소를 반환하는 Back 함수
7) 리스트의 i번째 원소를 반환하는 함수 Get(i)
8) 체인의 맨 앞에서 원소를 삭제하는 함수
9) 체인의 맨 뒤에서 원소를 삭제하는 함수
10) i번째 원소 뒤에 삽입하는 함수
11) i번째 원소를 삭제하는 함수
12) 반복자
13) accumulate 알고리즘 사용 가능

테스트 방법
1부터 9까지의 정수를 갖는 노드를 추가한다. (자료구조 4장 폴더의 11장 강의자료 9페이지 Number 클래스 객체를 노드에 추가)
반복자를 이용하여 체인의 각 노드들을 출력하여 1부터 9까지 순차적으로 출력되는지 확인한다.
0을 맨 앞에 삽입한다.
반복자를 이용하여 전체 노드의 값을 출력한다.
10을 맨 뒤에 삽입한다.
반복자를 이용하여 전체 노드의 값을 출력한다.
Front를 호출하여 0이 나오는지 확인한다.
Back을 호출하여 10이 나오는지 확인한다.
Get(2)를 호출하여 2가 나오는지 확인한다.
맨 앞에 있는 0을 삭제한다.
반복자를 이용하여 전체 노드의 값을 출력한다.
맨 뒤에 있는 10을 삭제한다.
반복자를 이용하여 전체 노드의 값을 출력한다.
3과 4 노드 사이에 100을 삽입한다. (2번째 원소 뒤에 삽입)
반복자를 이용하여 전체 노드의 값을 출력한다.
6을 삭제한다. (6번째 원소 삭제)
accumulate 알고리즘을 사용하여 전체 노드의 총합을 출력한다.
구현 여부와 미 구현 여부를 1) ~ 13)으로 표기할 것(과제 제출 방법 및 감점요인은 intro 파일 참고)
*/

#include <iostream>
#include <numeric>
using namespace std;

template <class T> class Chain; // forward declaration
template <class T> class ChainNode;
template <class T> class ChainIterator;

template <class T>
class ChainNode {
friend class Chain<T>;
friend class ChainIterator<T>;
private:
    T data;
    ChainNode<T> *link;
public:
    ChainNode(T element=0, ChainNode* next=0){ data = element; link = next; }
};

template <class T>
class Chain {
private:
    ChainNode<T> *first;
public:
    // class ChainIterator;
    // 1) 초기에 공백 체인을 생성하는 생성자
    Chain(); // constructor initializing first to 0
    // 2) 체인의 모든 원소를 삭제하는 소멸자
    ~Chain();
    // 3) 체인의 맨 앞에 삽입하는 함수
    void pushFront(T& element);
    // 4) 체인의 맨 뒤에 삽입하는 함수
    void pushBack(T& element);
    // 5) 리스트의 첫 번째 원소를 반환하는 Front 함수
    T Front();
    // 6) 리스트의 마지막 원소를 반환하는 Back 함수
    T Back();
    // 7) 리스트의 i번째 원소를 반환하는 함수 Get(i)
    T Get(int idx);
    // 8) 체인의 맨 앞에서 원소를 삭제하는 함수
    void popFront();
    // 9) 체인의 맨 뒤에서 원소를 삭제하는 함수
    void popBack();
    // 10) i번째 원소 뒤에 삽입하는 함수
    void pushIdx(int idx, T& element);
    // 11) i번째 원소를 삭제하는 함수
    void popIdx(int idx);
    // 12) 반복자
    void printAll();
    // 13) accumulate 알고리즘 사용 가능
    ChainIterator<T> begin() {return ChainIterator<T>(first);}
    ChainIterator<T> end() {return ChainIterator<T>(0);}

    // Chain manipulation operations

};


template <class T>
Chain<T>::Chain(){ first = NULL; }

template <class T>
Chain<T>::~Chain(){
    ChainNode<T> *next;
    ChainNode<T> *tmp;

    if(first != NULL && first->link != NULL){
        next = first->link;
        while(next->link != NULL){
            tmp = next;
            next = next->link;
            tmp->data = 0;
            tmp->link = NULL;
            delete tmp;
        }
    }
}

template <class T>
void Chain<T>::pushFront(T& element){
    ChainNode<T> *tmp = new ChainNode<T>(element, NULL);

    if(first == NULL) {
        first = new ChainNode<T>();
        first->link = tmp;
    }else{
        tmp->link = first->link;
        first->link = tmp;
    }
}

template <class T>
void Chain<T>::pushBack(T& element){
    ChainNode<T> *tmp = new ChainNode<T>(element, NULL);
    ChainNode<T> *next;

    if(first == NULL){
        first = new ChainNode<T>();
        first->link = tmp;
    }else{
        next = first;
        while(next->link != NULL){
            next = next->link;
        }
        next->link = tmp;
    }
}

template <class T>
T Chain<T>::Front(){
    if(first == NULL || first->link == NULL) { return -1; }
    return first->link->data;
}

template <class T>
T Chain<T>::Back(){
    ChainNode<T> *next;
    
    if(first == NULL || first->link == NULL) return -1;
    next = first;
    while(next->link != NULL){
        next = next->link;
    }
    return next->data;
}

template <class T>
T Chain<T>::Get(int idx){
    ChainNode<T> *next;

    if(first == NULL) { return -1; }
    next = first;
    for(int count = 0; count <= idx; count++){
        if(next->link == NULL) return -1;
        next = next->link;
    }
    return next->data;
    
}

template <class T>
void Chain<T>::popFront(){
    ChainNode<T> *node;

    if(first == NULL || first->link == NULL) { return; }
    node = first->link;
    if(node->link == NULL){
        node->data = 0;
        node = NULL;
        delete node;
    }else{
        node->data = 0;
        first->link = node->link;
        node->link = NULL;
        delete node;
    }
}

template <class T>
void Chain<T>::popBack(){
    ChainNode<T> *next;
    ChainNode<T> *tmp;
    if(first == NULL || first->link == NULL) return;
    if(first->link->link == NULL){
        first->link->data = 0;
        first->link = NULL;
        delete first->link;
    }
    next = first;
    while(next->link != NULL){
        next = next->link;
        if(next->link->link == NULL){
            tmp = next->link;
            next->link->data = 0;
            next->link = NULL;
            delete tmp;
            break;
        }
    }
}

template <class T>
void Chain<T>::pushIdx(int idx, T& element){
    ChainNode<T> *tmp = new ChainNode<T>(element, NULL);
    ChainNode<T> *next;

    if(first == NULL) {
        first = new ChainNode<T>(0, tmp);
        return;
    }
    next = first;
    for(int count = 0; count <= idx; count++){
        if(next->link == NULL){
            next->link = tmp;
            return;
        }
        next = next->link;
    }
    tmp->link = next->link;
    next->link = tmp;
}

template <class T>
void Chain<T>::popIdx(int idx){
    ChainNode<T> *next;
    ChainNode<T> *tmp;
    bool flag = true;

    if(first == NULL || first->link == NULL) { return; }
    next = first;
    if(first->link->link == NULL){
        first->link->data = 0;
        first->link = NULL;
        delete first->link;
        return;
    }
    for(int count = 1; count <= idx; count++){
        next = next->link;
        if(next->link->link == NULL){
            tmp = next->link;
            next->link->data = 0;
            next->link = NULL;
            delete tmp;
            flag = false;
            break;
        }
    }
    if(flag){
        tmp = next->link;
        next->link->data = 0;
        next->link = next->link->link;
        delete tmp;
    }
}

template <class T>
void Chain<T>::printAll(){
    if(first == NULL || first->link == NULL) { return; }
    ChainNode<T> *next = first;
    // while or for 객체 반복자 둘다 구현
    /*
    while(next->link != NULL){
        next = next->link;
        cout << next->data << " ";
    }
    cout << endl;
    */
    for(ChainNode<T> *i = first->link; ; i=i->link){
        cout << i->data << " ";
        if(i->link == NULL) break;
    }
    cout << endl;
    return;
}

class Number{
private:
    int num;
public:
    Number(int n=0) : num(n){
        //cout << "Number(int n=0)" << endl;
    }
    ~Number() { }
    Number& operator=(const Number &ref){
        // cout << "operator=()" << endl;
        num = ref.num;
        return *this;
    }
    operator int (){ return num; }
    void showNumber() { cout << num << endl; }
};

template <class T>
class ChainIterator {
public:
    // typedefs required by C++ for a forward iterator omitted

    // constructor
    ChainIterator(ChainNode<T>* startNode = 0)
    {current = startNode;}

    // dereferencing operators
    T& operator*() const {return current->data;}
    T* operator->() const {return &current->data;}

    // increment
    ChainIterator& operator++()   // preincrement
    {current = current->link; return *this;}
    ChainIterator operator++(int) // postincrement
    {
        ChainIterator old = *this;
        current = current->link;
        return old;
    }

    // equality testing
    bool operator!=(const ChainIterator right) const
    {return current != right.current;}
    bool operator==(const ChainIterator right) const
    {return current == right.current;}

private:
    ChainNode<T>* current;
};

int main(){
    Chain<Number> numberlist;
    
    cout << "1부터 9까지의 정수를 갖는 노드를 추가한다." << endl;
    for(int i=1; i<10; i++){
        numberlist.pushBack(* new Number(i));
    }
    
    cout << "반복자를 이용하여 체인의 각 노드들을 출력하여 1부터 9까지 순차적으로 출력되는지 확인한다." << endl;
    numberlist.printAll();

    cout << "0을 맨 앞에 삽입한다." << endl;
    numberlist.pushFront(* new Number(0));

    cout << "반복자를 이용하여 전체 노드의 값을 출력한다." << endl;
    numberlist.printAll();

    cout << "10을 맨 뒤에 삽입한다." << endl;
    numberlist.pushBack(* new Number(10));

    cout << "반복자를 이용하여 전체 노드의 값을 출력한다." << endl;
    numberlist.printAll();

    cout << "Front를 호출하여 0이 나오는지 확인한다." << endl;
    cout << numberlist.Front() << endl;

    cout << "Back을 호출하여 10이 나오는지 확인한다." << endl;
    cout << numberlist.Back() << endl;

    cout << "Get(2)를 호출하여 2가 나오는지 확인한다." << endl;
    cout << numberlist.Get(2) << endl;

    cout << "맨 앞에 있는 0을 삭제한다." << endl;
    numberlist.popFront();

    cout << "반복자를 이용하여 전체 노드의 값을 출력한다." << endl;
    numberlist.printAll();

    cout << "맨 뒤에 있는 10을 삭제한다." << endl;
    numberlist.popBack();

    cout << "반복자를 이용하여 전체 노드의 값을 출력한다." << endl;
    numberlist.printAll();

    cout << "3과 4 노드 사이에 100을 삽입한다. (2번째 원소 뒤에 삽입)" << endl;
    numberlist.pushIdx(2, * new Number(100));

    cout << "반복자를 이용하여 전체 노드의 값을 출력한다." << endl;
    numberlist.printAll();

    cout << "6을 삭제한다. (6번째 원소 삭제)" << endl;
    numberlist.popIdx(6);

    cout << "반복자를 이용하여 전체 노드의 값을 출력한다." << endl;
    numberlist.printAll();

    cout << "accumulate 알고리즘을 사용하여 전체 노드의 총합을 출력한다." << endl;
    cout << std::accumulate(numberlist.begin(), numberlist.end(), 0) << '\n';

    return 0;
}