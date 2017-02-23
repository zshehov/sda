//array implementation of a fixed size minheap
//uses macros {parent, left, right}
#ifndef _HEAP
#define _HEAP

#define CAPACITY 20

template<typename T>
class Heap {
private:
	T container[CAPACITY];
	size_t size;
	size_t left(size_t index);
	size_t right(size_t index);
	size_t parent(size_t index);
	void swap(T&, T&);
public:
	Heap();

	void moveup(size_t index);
	void heapify(size_t index);

	bool push(const T& el);
	T& peekmin();
	void removemin();
	size_t getSize()const;
};

template<typename T>
size_t Heap<T>::left(size_t index) {
	return (index << 1) + 1;
}

template<typename T>
size_t Heap<T>::right(size_t index) {
	return (index << 1) + 2;
}

template<typename T>
size_t Heap<T>::parent(size_t index) {
	return (index - 1) >> 1;
}

template<typename T>
void Heap<T>::swap(T& first, T& second) {
	T third(first);

	first = second;
	second = third;
}

template<typename T>
Heap<T>::Heap() :
	container(),
	size(0) {}

template<typename T>
void Heap<T>::moveup(size_t index) {
	while (index > 0 && (container[parent(index)] > container[index])) {
		swap(container[index], container[parent(index)]);
		index = parent(index);
	}
}

template<typename T>
void Heap<T>::heapify(size_t index) {

	size_t min;

	while (true) {
		if (left(index) < size && (container[index] > container[left(index)]))
			min = left(index);
		else
			min = index;
	

		if (right(index) < size && (container[min] > container[right(index)])) 
			min = right(index);
		

		if (min != index) {
			swap(container[index], container[min]);
			index = min;
		}
		else {
			break;
		}
	}
}

template<typename T>
bool Heap<T>::push(const T& pair) {
	if (size == CAPACITY) 
		return 0;

	container[size++] = pair;
	moveup(size-1);	
	return true;
}

template<typename T>
T& Heap<T>::peekmin() {
	return container[0];
}

template<typename T>
void Heap<T>::removemin() {
	container[0] = container[--size];
	heapify(0);
}


template<typename T>
size_t Heap<T>::getSize() const {
	return size;
}

#endif //!_HEAP
