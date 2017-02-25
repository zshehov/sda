#ifndef _STATIC_STACK
#define _STATIC_STACK
#define CAPACITY 4


template<typename T>
class Stack {
private:
	T arr[CAPACITY];
	size_t top;


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
	size_t current = 0;
	for (size_t i = 0; i < other.top; ++i) {
		arr[current++] = other.arr[i];
	}
	top = other.top;
}
template<typename T>
void Stack<T>::empty_stack() {
	top = 0;
}

template<typename T>
Stack<T>::Stack() :
	arr(),
	top(0) {}

template<typename T>
Stack<T>::Stack(const Stack<T>& other) {
	copy(other);
}


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
	if (top == 0) 
		return false;
	else
		--top;
		
	return true;
}

template<typename T>
void Stack<T>::push(const T& el) {
	if (top >= CAPACITY)
		throw "Stack overflow";

	arr[top++] = el;
}

template<typename T>
T& Stack<T>::peek() {
	if (top == 0)
		throw "Invalid index";
	return arr[top - 1];
}

template<typename T>
bool Stack<T>::is_empty() const{
	return top == 0;
}

template<typename T>
size_t Stack<T>::get_size() const{
	return top;
}


#endif // !_STATIC_STACK

