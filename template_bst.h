#ifndef _BST
#define _BST

//when using objects that have count property and the tree needs to remember
//how many of the same objects are added define WITH_COUNT
//else the bst will not add repeating elements
//#define WITH_COUNT 

template <typename T>
class node {
public:
	T value;
	node<T>* left;
	node<T>* right;

#ifdef WITH_COUNT
	size_t count;
#endif // WITH_COUNT

	node(const T& _value, node<T>* _left = nullptr, node<T>* _right = nullptr);
	node();

};


template<typename T>
node<T>::node() :
	value(T()),
#ifdef WITH_COUNT
	count(0),//relies that T has property count
#endif // WITH_COUNT
	left(nullptr),
	right(nullptr) {}



template<typename T>
node<T>::node(const T& _value, node<T>* _left = nullptr, node<T>* _right = nullptr) :
	value(_value),

#ifdef WITH_COUNT
	count( _value.count),//relies that T has property count
#endif // WITH_COUNT

	left(_left),
	right(_right) {}




template <typename T>
class BST {

private:
	node<T>* root;
	node<T>* findNextBigger(node<T>*& curr);
	node<T>* copy(node<T>* copy_from);
	
public:
	friend class Interface;
	BST();
	BST(const BST<T>& other);
	BST<T>& operator=(const BST<T>& other);
	node<T>*& getRoot();
	void insert(const T& key, node<T>*& curr);
	bool find(const T& key, node<T>*& curr);
	bool remove(const T& key, node<T>*& curr);
	~BST();
	void clear(node<T>*& curr);
	
};



template<typename T>
node<T>* BST<T>::findNextBigger(node<T>*& curr) {
	if (curr->left)
		return findNextBigger(curr->left);

	node<T>* holder = curr;
	curr = curr->right;
	return holder;
}



template<typename T>
node<T>* BST<T>::copy(node<T>* copy_from) {

	if (copy_from == nullptr) {
		return nullptr;
	}
	else {
		return new node<T>(copy_from->value, copy(copy_from->left), copy(copy_from->right));
	}
}


template<typename T>
BST<T>::BST() :
	root(nullptr) {}



template<typename T>
BST<T>::BST(const BST<T>& other) :
	root(copy(other.root)) {}



template<typename T>
BST<T>& BST<T>::operator=(const BST<T>& other) {
	if (this != &other) {
		clear(root);
		root = copy(other.root);
	}

	return *this;
}



template<typename T>
node<T>*& BST<T>:: getRoot(){
	return root;
}



template<typename T>
void BST<T>::insert(const T& key, node<T>*& curr) {
	if (!curr) {
		curr = new node<T>(key);
	}

	else if (key == curr->value) {
		
#ifdef WITH_COUNT
		++(curr->count);
#endif // WITH_COUNT
		
		return;//if WITH_COUNT is not defined no new element will be added
	}

	else {
		insert(key, key < curr->value ? curr->left : curr->right);
	}
}




template<typename T>
bool BST<T>::find(const T& key, node<T>*& curr) {
	if (!curr)
		return false;

	if (key == curr->value)
		return true;

	return find(key, key < curr->value ? curr->left : curr->right);
}



template<typename T>
bool BST<T>::remove(const T& key, node<T>*& curr) {
	if (!curr)
		return false;

	if (!(key == curr->value))
		return remove(key, key < curr->value ? curr->left : curr->right);


#ifdef WITH_COUNT
	if (curr->count > 1) {//if there is more than one of these equal elements
		--(curr->count);//only count is decreased, no nodes are removed
		return true;
	}
#endif // WITH_COUNT

	node<T>* holder = curr;

	if (curr->left && curr->right) {

		node<T>* replacer = findNextBigger(curr->right);
		replacer->left = curr->left;
		replacer->right = curr->right;
		curr = replacer;

	}
	else if (curr->left) {
		curr = curr->left;
	}
	else if (curr->right) {
		curr = curr->right;
	}
	else {
		curr = nullptr;
	}

	delete holder;
	holder = nullptr;
	return true;

}



template<typename T>
BST<T>::~BST() {
	clear(root);
}


template<typename T>
void BST<T>::clear(node<T>*& curr) {
	if (curr) {
		clear(curr->left);
		clear(curr->right);
		delete curr;
	}
}

#endif // !_BST
