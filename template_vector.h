#ifndef _VECTOR
#define _VECTOR
#include<stdexcept>

template<typename T>
class Vector {
private:
	T* parr;
	size_t size;
	size_t capacity;
	void resize();
	void copyArr(const Vector<T>& other);
	void emptyArr();

public:
	Vector();
	Vector(size_t initial_size);
	~Vector();
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	


	void insert(size_t index, const T &);
	void push_back(const T &);
	void push_front(const T &);
	void append(const Vector<T>&);
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	void removeAt(size_t index);

	size_t getCapacity() const;
	size_t getSize() const;

};

template<typename T>
Vector<T>::Vector() {
	parr = new T[capacity = 1];
	size = 0;
}


template<typename T>
Vector<T>::Vector(size_t initial_size) {
	parr = new T[capacity = initial_size];
	size = 0;
}


template<typename T>
void Vector<T>::emptyArr() {
	size = 0;
	capacity = 1;
	delete[] parr;
	parr = nullptr;

}
template<typename T>
Vector<T>:: ~Vector() {
	emptyArr();
}

template<typename T>
void Vector<T>::copyArr(const Vector<T>& other) {
	size_t len = other.getSize();
	for (size_t i = 0; i < len; ++i) {
		parr[i] = other[i];
	}
}


template<typename T>
Vector<T>::Vector(const Vector<T>& other) {
	capacity = other.capacity;
	size = other.getSize();
	parr = new T[capacity];
	copyArr(other);
}

template<typename T>
void Vector<T>::resize() {

	size_t newCapacity = capacity << 1;
	T* pnewArr = new T[newCapacity];

	for (size_t i = 0; i < size; ++i) {
		pnewArr[i] = parr[i];
	}

	delete[] parr;
	parr = pnewArr;
	capacity = newCapacity;

}

template<typename T>
size_t Vector<T>::getCapacity() const{
	return capacity;
}

template<typename T>
size_t Vector<T>::getSize() const{
	return size;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		emptyArr();
		
		capacity = other.getCapacity();
		size = other.getSize();

		parr = new T[capacity];

		copyArr(other);
	}

	return *this;
}


template<typename T>
void Vector<T>::insert(size_t index, const T& item) {
	if (index <= size) {
		if (size >= capacity) {
			resize();
		}

		if (size > 0) {
			for (size_t i = size - 1; i > index; --i) {
				parr[i + 1] = parr[i];
			}
		}
		parr[index] = item;

		++size;
	}
	else {
		throw std::invalid_argument("Index out of range");
	}
}

template<typename T>
void Vector<T>::push_back(const T & item){
	insert(size, item);
}

template<typename T>
void Vector<T>::push_front(const T & item){
	insert(0, item);
}


template<typename T>
void Vector<T>::append(const Vector<T>& other) {
	size_t len = other.getSize();

	for (size_t i = 0; i < len; ++i) {
		push_back(other[i]);
	}
}
template<typename T>
const T & Vector<T>::operator[](size_t index) const{
	if (index < size) {
		return parr[index];
	}
	else {
		throw std::invalid_argument("Index out of range");
	}
}

template<typename T>
T & Vector<T>::operator[](size_t index){
	if (index < capacity) {
		return parr[index];
	}
	else {
		throw std::invalid_argument("Index out of range");
	}
}

template<typename T>
void Vector<T>::removeAt(size_t index){
	if (index < size) {

		for (size_t i = index; i < size - 1; ++i) {
			parr[i] = parr[i + 1];
		}
		--size;
	}
	else {
		throw std::invalid_argument("Index out of range");
	}
}
#endif //!_VECTOR
