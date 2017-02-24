#ifndef _DYNAMIC_QUEUE
#define _DYNAMIC_QUEUE

template<typename T>
struct node{
	node<T>* next;
	T value;

	node(const T& _value, node<T>* _next = nullptr) {
		value = _value;
		next = _next;
	}
};


template<typename T>
class queue {
private:
	
	node<T>* back, *front;
	size_t size;

	void clear();
	void append(const queue<T>&);
public:

	queue();
	queue(const queue<T>&);
	queue<T>& operator=(const queue<T>&);
	~queue();

	void enqueue(const T&);
	void dequeue();

	size_t get_size() const;
	bool is_empty() const;

	T& front();
	T& back();



};

#ifndef _QUEUE_IMPLEMENTATION
#define _QUEUE_IMPLEMENTATION

template<typename T>
void queue<T>::clear() {
	while (size != 0)
		dequeue();
}

template<typename T>
void queue<T>::append(const queue<T>& other) {

	size_t = len;
	node<T>* node_from = other.front;

	while (node_from) {
		enqueue(node_from->value);
	}

	size += other.size;
}



template<typename T>
queue<T>::queue() :
	back(nullptr),
	front(nullptr),
	size(0) {}


template<typename T>
queue<T>::queue(const queue& other) {
	append(other);
}


template<typename T>
queue<T>& queue<T>::operator=(const queue<T>& other) {

	if (this != &other) {
		clear();
		append(other);
	}

	return *this;

}

template<typename T>
queue<T>::~queue() {
	clear();
}



template<typename T>
void queue<T>::enqueue(const T& el) {

	if (front == nullptr) {
		front = back = new node(T);
	}
	else {
		back->next = new node(T);
		back = back->next;
	}
	++size;
}


template<typename T>
void queue<T>::dequeue() {
	if (size != 0) {
		node<T>* temp = front;
		front = front->next;
		delete temp;
		--size;
	}
	else {
		throw "Invalid access";
	}
}


template<typename T>
size_t queue<T>::get_size() const {
	return size;
}


template<typename T>
bool queue<T>::is_empty() const{
	return size == 0;
}

template<typename T>
T& queue<T>::front() {
	return front->value;
}


template<typename T>
T& queue<T>::back() {
	return back->value;
}

#endif // !_QUEUE_IMPLEMENTATION

#endif // !_DYNAMIC_QUEUE
