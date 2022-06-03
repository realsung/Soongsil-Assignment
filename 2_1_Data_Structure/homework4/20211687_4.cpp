#include <iostream>
#include <utility>

using namespace std;

template <class K, class E> class BST;

template <class K, class E>
class Dictionary {
public:
    virtual bool IsEmpty() const = 0;
    // return true iff the dictionary is empty
    virtual pair<K,E>* Get(const K&) const = 0;
    // return pointer to the pair with specified key; return 0 if no such pair
    virtual void Insert(const pair<K,E>&) = 0;
    // insert the given pair; if key is a duplicate update associated element
    virtual void Delete(const K&) = 0;
    // delete pair with specified key
};

template <class T>
class TreeNode {
friend class BST<int, int>;
private:
    T data;
    TreeNode<T> *leftChild;
    TreeNode<T> *rightChild;
public:
    TreeNode() {};
	TreeNode(T thePair) {
		data = thePair;
		leftChild = 0;
		rightChild = 0;
	}
    ~TreeNode(){
        data.first = 0;
        data.second = 0;
    }
};

template <class K, class E>
class BST : Dictionary<K, E>{
public:
	BST() { root = 0; }
	bool IsEmpty() const;
	pair<K, E>* Get(const K&) const;
	pair<K, E>* Get(TreeNode<pair<K, E>>* p, const K& k) const;
	void Insert(const pair<K, E>&);
	void Delete(const K&);
	void Inorder();
	void Inorder(TreeNode<pair<K, E>> *);
	void Visit(TreeNode<pair<K, E>> *);
	void show(pair<K, E> *);
private:
	TreeNode<pair<K, E>> *root; // 트리의 root
};

template <class K, class E>
bool BST<K, E>::IsEmpty() const{
	if (root) {
		return 0;
	}
	else {
		return 1;
	}
}

template <class K, class E>  // Driver
pair<K,E>* BST<K,E>::Get(const K& k) const
{   
    // Search the binary search tree (*this) for a pair with key k.
    // If such a pair is found, return a pointer to this pair; otherwise, return 0.
    return Get(root, k);
}

template <class K, class E>  // Workhorse
pair<K,E>* BST<K,E>::Get(TreeNode<pair<K,E> >* p, const K& k) const
{
    if (!p) return 0;
    if (k < p->data.first) return Get(p->leftChild,k);
    if (k > p->data.first) return Get(p->rightChild,k);
    return &p->data;
}

template <class K, class E>
void BST<K,E>::Insert(const pair<K,E>& thePair)
{   // Insert thePair into the binary search tree.
    // search for thePair.first, pp is parent of p
    TreeNode<pair<K,E> > *p = root, *pp = 0;
    while (p) {
        pp = p;
        if (thePair.first < p->data.first) p = p->leftChild;
        else if (thePair.first > p->data.first) p = p->rightChild;
        else //  duplicate, update associated element
        {p->data.second = thePair.second; return;}
    }

    // perform insertion
    p = new TreeNode<pair<K,E> > (thePair);
    if (root)  // tree not empty
        if (thePair.first < pp->data.first) pp->leftChild = p;
        else pp->rightChild = p;
    else root = p;
}

template<class K, class E>
void BST<K, E>::Delete(const K& k){
	TreeNode<pair<K, E>>* p = root, * pp = NULL;
	while (p && k != p->data.first){
		pp = p;
		if (k < p->data.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)
		return ;
	if (p->leftChild == NULL && p->rightChild == NULL){
		if (pp == NULL)
			root = NULL;
		else if (pp->leftChild == p)
			pp->leftChild = NULL;
		else
			pp->rightChild = NULL;
		delete p;
	}else if (p->leftChild == NULL){
		if (pp == NULL)
			root = p->rightChild;
		else if (pp->leftChild == p)
			pp->leftChild = p->rightChild;
		else
			pp->rightChild = p->rightChild;
		delete p;
	}else if (p->rightChild == NULL){
		if (pp == NULL)
			root = p->leftChild;
		else if (pp->leftChild == p)
			pp->leftChild = p->leftChild;
		else
			pp->rightChild = p->leftChild;
		delete p;
	}
    else if(p->leftChild != NULL && p->rightChild != NULL){
        TreeNode<pair<K, E>> *prevprev = p, *prev = p->rightChild, *curr = p->rightChild->leftChild;
		while (curr){
			prevprev = prev;
			prev = curr;
			curr = curr->leftChild;
		}
		p->data = prev->data;
		if (prevprev == p)
			prevprev->rightChild = prev->rightChild;
		else
			prevprev->leftChild = prev->rightChild;
		delete prev;
    }
}

template <class K, class E>
void BST<K, E>::Visit(TreeNode<pair<K, E>> *currentNode) {
	cout << currentNode->data.first << " : " << currentNode->data.second << endl;
}

template<class K, class E>
void BST<K, E>::Inorder() {
	Inorder(root);
    cout << endl;
}

template<class K, class E>
void BST<K, E>::Inorder(TreeNode<pair<K, E>> *currentNode) {
	if (currentNode) {
		Inorder(currentNode->leftChild);
		Visit(currentNode);
		Inorder(currentNode->rightChild);
	}
}

template <class K, class E>
void BST<K, E>::show(pair<K, E> *p) {
	if(p) {
		cout << p->first << " : " << p->second << endl;
	}
	else {
		cout << "해당 값의 노드가 없습니다." << endl;
	}
}

int main(){
    BST<int, int> Tree;
    cout << "1. 이원 탐색 트리의 노드는 다음과 같은 순서로 추가된다. (insert 함수 사용)" << endl;
    cout << "20220033(90), 20220050(73), 20220043(99), 20220011(82), 20220024(78), 20220046(96), 20220001(72), 20220008(88), 20220036(77), 20220056(93), 20220053(82), 20220059(100)" << endl;
    Tree.Insert(make_pair(20220033, 90));
    Tree.Insert(make_pair(20220050, 73));
    Tree.Insert(make_pair(20220043, 99));
    Tree.Insert(make_pair(20220011, 82));
    Tree.Insert(make_pair(20220024, 78));
    Tree.Insert(make_pair(20220046, 96));
    Tree.Insert(make_pair(20220001, 72));
    Tree.Insert(make_pair(20220008, 88));
    Tree.Insert(make_pair(20220036, 77));
    Tree.Insert(make_pair(20220056, 93));
    Tree.Insert(make_pair(20220053, 82));
    Tree.Insert(make_pair(20220059, 100));

    cout << "2. 중위 순회를 수행하여 모든 노드의 학번과 점수를 출력한다. (inorder 함수 사용)" << endl;
    Tree.Inorder();

    cout << "3. 킷값이 20220050인 노드를 삭제한다. (delete 함수 사용)" << endl;
    Tree.Delete(20220050);

    cout << "4. 중위 순회를 수행하여 모든 노드의 학번과 점수를 출력한다. (inorder 함수 사용)" << endl;
    Tree.Inorder();

    cout << "5. 킷값이 20220008인 노드를 삭제한다. (delete 함수 사용)" << endl;
    Tree.Delete(20220008);

    cout << "6. 중위 순회를 수행하여 모든 노드의 학번과 점수를 출력한다. (inorder 함수 사용)" << endl;
    Tree.Inorder();

    cout << "7. 킷값이 20220056인 노드를 삭제한다. (delete 함수 사용)" << endl;
    Tree.Delete(20220056);

    cout << "8. 중위 순회를 수행하여 모든 노드의 학번과 점수를 출력한다. (inorder 함수 사용)" << endl;
    Tree.Inorder();

    cout << "9. 킷값이 20220056인 노드가 있는지 확인하여 학번과 점수를 출력한다. (get 함수 사용)" << endl;
    Tree.show(Tree.Get(20220056));

    cout << "10. 킷값이 20220043인 노드가 있는지 확인하여 학번과 점수를 출력한다. (get 함수 사용)" << endl;
    Tree.show(Tree.Get(20220043));
}

/*
이원 탐색 트리 클래스를 완성하여라. 단, 트리 노드는 pair(학번, 점수)로 표현한다. 또한 삭제 함수의 단순화를 위해서 자식이 2개인 노드를 삭제할 경우, 오른쪽 서브 트리의 가장 작은 원소로 대체한다.

1. 이원 탐색 트리의 노드는 다음과 같은 순서로 추가된다. (insert 함수 사용)
20220033(90), 20220050(73), 20220043(99), 20220011(82), 20220024(78), 20220046(96), 20220001(72), 20220008(88), 20220036(77), 20220056(93), 20220053(82), 20220059(100)

2. 중위 순회를 수행하여 모든 노드의 학번과 점수를 출력한다. (inorder 함수 사용)

3. 킷값이 20220050인 노드를 삭제한다. (delete 함수 사용)

4. 중위 순회를 수행하여 모든 노드의 학번과 점수를 출력한다. (inorder 함수 사용)

5. 킷값이 20220008인 노드를 삭제한다. (delete 함수 사용)

6. 중위 순회를 수행하여 모든 노드의 학번과 점수를 출력한다. (inorder 함수 사용)

7. 킷값이 20220056인 노드를 삭제한다. (delete 함수 사용)

8. 중위 순회를 수행하여 모든 노드의 학번과 점수를 출력한다. (inorder 함수 사용)

9. 킷값이 20220056인 노드가 있는지 확인하여 학번과 점수를 출력한다. (get 함수 사용)

10. 킷값이 20220043인 노드가 있는지 확인하여 학번과 점수를 출력한다. (get 함수 사용)

구현 여부와 미구현 여부를 표기할 것(과제 제출 방법 및 감점요인은 intro 파일 참고)
*/