#ifndef _DYNAMIC_STACK
#define _DYNAMIC_STACK

template<typename T>
struct node {
	T data;
	node<T> *prev;

	node(const T& _data = T(), node<T>* _prev = nullptr);
};

template<typename T>
node<T>::node(const T& _data = T(), node<T>* _prev = nullptr) :
	data(_data),
	prev(_prev) {}


template<typename T>
class Stack {
private:

	node<T>* top;
	size_t size;

	void copy(const Stack<T>&);
public:
	void empty_stack();

	Stack();
	Stack(const Stack<T>&);
	Stack<T>& operator=(const Stack<T>&);
	~Stack();

	bool pop();
	void push(const T&);
	T& peek();

	
	
	bool is_empty() const;
	size_t get_size() const;


};

template<typename T>
void Stack<T>::copy(const Stack<T>& other) {
	if (other.size == 0) {//if copying from an empty stack
		empty_stack();
		return;
	}

	node<T>* current_from = other.top, *current_to;
	
	//initiate top
	current_to = top = new node<T>(current_from->data);
	

	current_from = current_from->prev;
	while (current_from != nullptr) {
		
		current_to->prev = new node<T>(current_from->data);

		current_from = current_from->prev;
		current_to = current_to->prev;
	}

	size = other.size;
}


template<typename T>
void Stack<T>::empty_stack() {

	//doing it that way instead of just popping because it
	//doesn't waste time for --size and checking if size == 0

	node<T>* holder;

	while (top != nullptr) {
		holder = top;
		top = top->prev;

		delete holder;
	}
	size = 0;
}



template<typename T>
Stack<T>::Stack() :
	top(nullptr),
	size(0) {}


template<typename T>
Stack<T>::Stack(const Stack<T>& other) :
	top(nullptr),
	size(0){copy(other);}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
	if (this != &other) {
		empty_stack();
		copy(other);
	}

	return *this;
}

template<typename T>
Stack<T>::~Stack() {
	empty_stack();
}


template<typename T>
bool Stack<T>::pop() {
	if (size == 0)
		return false;

	node<T>* holder = top;
	top = top->prev;

	delete holder;
	--size;
	return true;
}


template<typename T>
void Stack<T>::push(const T& el) {

	top = new node<T>(el, top);
	++size;
}

template<typename T>
T& Stack<T>::peek() {

	if (size == 0)
		throw "Invalid index";

	return top->data;
}


template<typename T>
bool Stack<T>::is_empty() const {
	return size == 0;
}

template<typename T>
size_t Stack<T>::get_size() const{
	return size;
}
#endif // !_DYNAMIC_STACK
