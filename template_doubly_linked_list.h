#ifndef _DOUBLY_LINKED_LIST
#define _DOUBLY_LINKED_LIST

template<typename T>
struct Node {
	T data;
	Node<T>* left;
	Node<T>* right;

	Node(const T& _data, Node<T>* _left = nullptr, Node<T>* _right = nullptr);
};

template<typename T>
Node<T>::Node(const T& _data = T(), Node<T>* _left = nullptr, Node<T>* _right = nullptr) :
	data(_data),
	left(_left),
	right(_right){}


template<typename T>
class DoublyLinkedList {
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;

	Node<T>* node_at(size_t index);
	void copy(const DoublyLinkedList<T>& other);

public:

	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>&);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
	~DoublyLinkedList();
	bool is_empty();

	T& peek_first();
	T& peek_last();

	bool pop_first();
	bool pop_last();

	void push_first(const T&);
	void push_last(const T&);

	T& operator[](size_t index);

	void remove_at(size_t index);
	void insert_at(size_t inedx, const T& el);

	void empty_list();
	size_t get_size() const;

};



template<typename T>
Node<T>* DoublyLinkedList<T>::node_at(size_t index) {

	//little optimisation here
	//if the index of the searched element
	//is closer to the beginning, we start
	//searching from the element right of the first
	//if closer to the end, we start from the element
	//left of the last
	Node<T>* current;
	if (index < (size >> 1)) {//first half of list
		current = first->right;
		for (size_t i = 2; i <= index; ++i) {
			current = current->right;
		}
		return current;
	}
	else {//second half of list
		current = last->left;
		for (size_t i = size - 3; i >= index; --i) {
			current = current->left;
		}
		return current;
	}
}

//i think that way is faster than just popping untill there is nothing left
template<typename T>
void DoublyLinkedList<T>::empty_list() {
	Node<T>* temp;

	while (first != nullptr) {
		temp = first;
		first = first->right;
		delete temp;
	}
	last = nullptr;
	size = 0;
}

template<typename T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList<T>& other) {

	if (other.size == 0) {//copying from an empty list
		empty_list();
	}

	first = new Node<T>(other.first->data);

	Node<T>* current_from = other.first->right;
	Node<T>* current_to = first;

	while (current_from != nullptr) {

		current_to->right = new Node<T>(current_from->data, current_to);
		current_to = current_to->right;
		current_from = current_from->right;
	}

	last = current_to;
	size = other.size;
}




template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() :
	first(nullptr),
	last(nullptr),
	size(0) {}


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) {
	copy(other);
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
	if (this != &other) {
		empty_list();
		copy(other);
	}

	return *this;
}



template<typename T>

DoublyLinkedList<T>::~DoublyLinkedList() {
	empty_list();
}

template<typename T>
bool DoublyLinkedList<T>::is_empty() {
	return size == 0;
}



template<typename T>
T& DoublyLinkedList<T>::peek_first() {
	return first->data;
}

template<typename T>
T& DoublyLinkedList<T>::peek_last() {
	return last->data;
}





template<typename T>
bool DoublyLinkedList<T>::pop_first() {
	Node<T>* holder = first;

	if (size > 1) {
		first = first->right;
		first->left = nullptr;
	}
	else if (size == 1) {
		first = last = nullptr;
	}
	else {//empty list
		return false;
	}

	delete holder;
	--size;
	return true;
}

template<typename T>
bool DoublyLinkedList<T>::pop_last() {
	Node<T>* holder = last;


	if (size > 1) {
		last = last->left;
		last->right = nullptr;
	}
	else if (size == 1) {
		first = last = nullptr;
	}
	else {//empty list
		return false;
	}


	delete holder;
	--size;
	return true;
}



template<typename T>
void DoublyLinkedList<T>::push_first(const T& el) {
	if (size == 0) {
		first = last = new Node<T>(el);
	}
	else {
		Node<T>* to_add = new Node<T>(el, nullptr, first);
		first = first->left = to_add;
	}

	++size;
}

template<typename T>
void DoublyLinkedList<T>::push_last(const T& el) {
	if (size == 0) {
		first = last = new Node<T>(el);
	}
	else {
		Node<T>* to_add = new Node<T>(el, last, nullptr);
		last = last->right = to_add;
	}

	++size;
}


template<typename T>
T& DoublyLinkedList<T>::operator[](size_t index) {
	if (index == 0)
		return peek_first();
	else if (index == size - 1)
		return peek_last();
	else if (index >= size)
		throw "Invalid index";


	Node<T>* current = node_at(index);
	return current->data;
}


template<typename T>
void DoublyLinkedList<T>::remove_at(size_t index) {
	if (index == 0) {
		pop_first();
	}
	else if (index == size - 1) {
		pop_last();
	}
	else if (index >= size) {
		throw "Invalid index";
	}
	else {

		Node<T>* current = node_at(index);

		current->left->right = current->right;
		current->right->left = current->left;

		delete current;
		--size;
	}
}

//can't insert element at an index bigger than the size of the list
//an index equal to the size of the list will be the same as push_last
template<typename T>
void DoublyLinkedList<T>::insert_at(size_t index, const T& el){

	if (index == 0) {
		push_first(el);
	}
	else if (index == size) {
		push_last(el);
	}
	else if (index > size) {
		throw "Invalid index";
	}
	else {
		--index;
		//that way the located element is the element 
		//after which we will add the new one

		Node<T>* current = node_at(index);

		current->right->left = new Node<T>(el, current, current->right);
		current->right = current->right->left;

		++size;
	}

}

template<typename T>
size_t DoublyLinkedList<T>::get_size() const {
	return size;
}

#endif // !_DOUBLY_LINKED_LIST
