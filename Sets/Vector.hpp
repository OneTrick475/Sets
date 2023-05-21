#pragma once
#include "iostream"

namespace vectorConstants {
	const size_t initialLength = 16;
	const size_t resizeCoef = 2;
}

template<typename T>
class Vector {
	T* data = nullptr;
	size_t length = vectorConstants::initialLength;
	size_t count = 0;

	void resize();

	void free();
	void copyFrom(const Vector& other);
	void moveFrom(Vector&& other);

public:
	Vector();
	Vector(size_t initialLength);
	Vector(const Vector& other);
	Vector(Vector&& other);
	Vector& operator=(const Vector& other);
	Vector& operator=(Vector&& other);
	~Vector();

	size_t len() const;
	void pushBack(const T& element);
	void pushBack(T&& element);
	void pushAt(const T& element, size_t index);
	void pushAt(T&& element, size_t index);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vector);
};


template <typename T>
void Vector<T>::free() {
	delete[] data;
	data = nullptr;
	count = length = 0;
}

template <typename T>
void Vector<T>::copyFrom(const Vector& other) {
	length = other.length;

	data = new T[length];

	for (size_t i = 0; i < other.len(); i++) {
		data[i] = other.data[i];
	}
	count = other.count;
}

template <typename T>
void Vector<T>::moveFrom(Vector&& other) {
	length = other.length;
	count = other.count;
	data = other.data;
	other.data = nullptr;
}

template<typename T>
Vector<T>::Vector(size_t initialLength) : length(initialLength) {
	data = new T[length];
}

template<typename T>
Vector<T>::Vector() : Vector(vectorConstants::initialLength) {}

template<typename T>
Vector<T>::Vector(const Vector& other) {
	copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector&& other) {
	moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
Vector<T>::~Vector() {
	free();
}

template <typename T>
size_t Vector<T>::len() const {
	return count;
}

template <typename T>
void Vector<T>::resize() {
	length *= vectorConstants::resizeCoef;

	T* temp = new T[length];
	for (size_t i = 0; i < count; i++)
		temp[i] = data[i];

	delete[] data;
	data = temp;
}

template<typename T>
void Vector<T>::pushBack(const T& element) {
	if (count == length)
		resize();

	data[count++] = element;
}

template<typename T>
void Vector<T>::pushBack(T&& element) {
	if (count == length)
		resize();

	data[count++] = std::move(element);
}

template <typename T>
void Vector<T>::pushAt(const T& element, size_t index) {
	if (count == length)
		resize();

	for (size_t i = count; i > index; i--)
		data[i] = data[i - 1];

	data[index] = element;
	count++;
}

template <typename T>
void Vector<T>::pushAt(T&& element, size_t index) {
	if (count == length)
		resize();

	for (size_t i = count; i > index; i--)
		data[i] = data[i - 1];

	data[index] = std::move(element);
	count++;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
	return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
	return data[index];
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
	for (size_t i = 0; i < vector.count; i++)
		os << vector[i] << " ";
	return os;
}

