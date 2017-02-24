#ifndef _LINKED_LIST
#define _LINKED_LIST

template<typename T>
struct Node {
	T data;
	Node<T> * next;
	
	Node(const T & _data, Node<T>* _next = nullptr);
};


template<typename T>
Node<T>::Node(const T& _data, Node<T>* _next = nullptr) :
	data(_data),
	next(_next) {}


template<typename T>
class LinkedList {
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;
	void copy(const LinkedList& other);
	
	Node<T>* find_at(size_t index)const;
public:
	LinkedList();
	LinkedList(const LinkedList& _other);
	LinkedList& operator=(const LinkedList& other);
	~LinkedList();


	void push_first(const T& el);
	void push_last(const T& el);

	bool pop_first();
	bool pop_last();

	T& get_first();
	T& get_last();


	T& operator[](size_t index);
	void remove_at(size_t index);

	void insert_after(size_t index, const T& el);
	void insert_before(size_t index, const T& el);

	void append(const LinkedList& other);
	void empty_list();
	bool is_empty() const;
	size_t get_size() const;
};

template<typename T>
void LinkedList<T>::copy(const LinkedList& other) {

	// in the case we are copying from an empty list
	if (other.first == nullptr) {
		first = last = nullptr;
		size = 0;
		return;
	}

	first = new Node<T>(other.first->data);

	Node<T>* current_to = first;
	Node<T>* current_from = other.first->next;

	while (current_from != nullptr) {

		//creates a new node in this linked list with a copy of the data 
		//from the corresponding node from the other linked list
		current_to->next = new Node<T>(current_from->data);

		current_to = current_to->next;//goes to next node from this linked list
		current_from = current_from->next;//goes to next node from the other linked list
	}

	last = current_to;//last is the last copied node
	size = other.size;
}

template<typename T>
void LinkedList<T>::empty_list() {
	Node<T>* temp;

	while (first != nullptr) {
		temp = first;
		first = first->next;
		delete temp;
	}
	last = nullptr;
	size = 0;
}

template<typename T>

Node<T>* LinkedList<T>::find_at(size_t index) const {

	if (first == nullptr || index >= size) {
		return nullptr;
	}

	Node<T>* current = first;

	for (size_t i = 0; i < index; ++i) {
		current = current->next;
	}

	return current;
}


template<typename T>
LinkedList<T>::LinkedList() :
	first(nullptr),
	last(nullptr),
	size(0) {}


template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
	copy(other);
}


template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {

	if (this != &other) {
		empty_list();
		copy(other);
	}

	return *this;
}


template<typename T>
LinkedList<T>::~LinkedList() {
	empty_list();
}


template<typename T>
void LinkedList<T>::push_first(const T& el) {

	Node<T>* to_add = new Node<T>(el);
	to_add->next = first;
	first = to_add;

	if (size == 0)
		last = first;

	++size;
}


template<typename T>
void LinkedList<T>::push_last(const T& el) {

	Node<T>* to_add = new Node<T>(el);

	if (size == 0) {
		first = last = to_add;
	}
	else {
		last->next = to_add;
		last = to_add;

	}

	++size;
}

template<typename T>
bool LinkedList<T>::pop_first() {
	if (size == 0)
		return false;//nothing to pop

	Node<T>* temp = first;
	first = first->next;

	delete temp;
	--size;
	return true;
}

template<typename T>
bool LinkedList<T>::pop_last() {
	if (size == 0)
		return false;//nothing to pop

	//if there is only 1 element
	if (first == last) {
		pop_first();
		//since last doesn't point to anything now
		//it should be nullptr
		last = nullptr;
		return true;
	}

		

	//at this point we are sure that we have 
	//atleast 2 elements in the list
	//since last element is at index size - 1,
	//we are getting the one before that
	Node<T>* preceding = find_at(size - 2);

	preceding->next = nullptr;
	delete last;
	last = preceding;

	--size;
	return true;
}

template<typename T>
T& LinkedList<T>::get_first() {
	if (size == 0) {
		throw "Empty list";
	}

	return first->data;
}

template<typename T>
T& LinkedList<T>::get_last() {
	if (size == 0) {
		throw "Empty list";
	}

	return last->data;
}

template<typename T>
T& LinkedList<T>::get_at(size_t index) {


}

template<typename T>
T& LinkedList<T>::operator[](size_t index) {
	Node<T>* target = find_at(index);

	if (target == nullptr)
		throw "Invalid index";

	return target->data;
}



template<typename T>
void LinkedList<T>::remove_at(size_t index) {
	//removing the node at index 0 is same as pop the first element
	if (index == 0) {
		pop_first();
		return;
	}
		

	Node<T>* pretarget = find_at(index - 1);
	if (pretarget == nullptr)
		throw "Invalid index";


	Node<T>* target = pretarget->next;

	pretarget->next = target->next;
	delete target;
	--size;
}

template<typename T>
void LinkedList<T>::insert_after(size_t index, const T& el) {
	//inserting after the last element is the same as push_last
	if (index == size - 1) {
		push_last(el);
		return;
	}
		

	Node<T>* target = find_at(index);

	if (target == nullptr)
		throw "Invalid index";

	Node<T>* insertee = new Node<T>(el);
	insertee->next = target->next;
	target->next = insertee;
	++size;
}

template<typename T>
void LinkedList<T>::insert_before(size_t index, const T& el) {
	//inserting before the first element is same as push_first

	if (index == 0) {
		push_first(el);
		return;
	}
		
	Node<T>* target = find_at(index - 1);

	if (target == nullptr)
		throw "Invalid index";


	Node<T>* insertee = new Node<T>(el);
	insertee->next = target->next;
	target->next = insertee;
	++size;
}

template<typename T>
void LinkedList<T>::append(const LinkedList<T>& other) {
	Node<T>* current = other.first;

	while (current != nullptr) {
		push_last(new Node<T>(current->data));

		current = current->next;
	}
}



template<typename T>
bool LinkedList<T>::is_empty()const {
	if (size == 0 && (first != nullptr || last != nullptr))
		throw "SUMTHING WRONG";

	return size == 0;
}

template<typename T>
size_t LinkedList<T>::get_size()const {
	return size;
}

#endif // !_LINKED_LIST


