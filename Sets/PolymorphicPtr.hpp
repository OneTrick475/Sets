#pragma once
#include <iostream>

template<typename T>
class PolymorphicPtr {
	T* ptr = nullptr;

	void free();
	void copyFrom(const PolymorphicPtr& other);
	void moveFrom(PolymorphicPtr&& other);

public:
	PolymorphicPtr() = default;
	PolymorphicPtr(T* ptr);
	PolymorphicPtr(const PolymorphicPtr& other);
	PolymorphicPtr(PolymorphicPtr&& other);
	PolymorphicPtr& operator=(const PolymorphicPtr& other);
	PolymorphicPtr& operator=(PolymorphicPtr&& other);
	~PolymorphicPtr();

	T* operator->();
	const T* operator->() const;
	T& operator*();
	const T& operator*() const;
};


template <typename T>
void PolymorphicPtr<T>::free(){
	delete ptr;
	ptr = nullptr;
}

template <typename T>
void PolymorphicPtr<T>::copyFrom(const PolymorphicPtr& other) {
	if (other.ptr == nullptr)
		return;
	ptr = other.ptr->clone();
}

template <typename T>
void PolymorphicPtr<T>::moveFrom(PolymorphicPtr&& other) {
	ptr = other.ptr;
	other.ptr = nullptr;
}

template <typename T>
PolymorphicPtr<T>::PolymorphicPtr(T* ptr) : ptr(ptr) {}

template <typename T>
PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr& other) {
	copyFrom(other);
}

template <typename T>
PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr&& other) {
	moveFrom(std::move(other));
}

template <typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(const PolymorphicPtr& other) {
	if(this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(PolymorphicPtr&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
PolymorphicPtr<T>::~PolymorphicPtr() {
	free();
}

template <typename T>
T* PolymorphicPtr<T>::operator->() {
	return ptr;
}

template <typename T>
const T* PolymorphicPtr<T>::operator->() const {
	return ptr;
}

template <typename T>
T& PolymorphicPtr<T>::operator*() {
	return *ptr;
}

template <typename T>
const T& PolymorphicPtr<T>::operator*() const {
	return *ptr;
}






