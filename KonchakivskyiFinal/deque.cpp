#include "screen.h"
#include "dictionary.h"
#include "deque.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <sstream>


template <typename T>
ArrayDeque<T>::ArrayDeque()
	: capacity(DEFAULT_CAPACITY), frontIdx(0), backIdx(0), count(0) {
	array = new T[capacity];
}

template <typename T>
ArrayDeque<T>::~ArrayDeque() {
	delete[] array;
}

template <typename T>
ArrayDeque<T>::ArrayDeque(const ArrayDeque& other)
	: capacity(other.capacity), frontIdx(other.frontIdx),
	backIdx(other.backIdx), count(other.count) {
	array = new T[capacity];
	for (size_t i = 0; i < capacity; ++i) {
		array[i] = other.array[i];
	}
}

template <typename T>
ArrayDeque<T>& ArrayDeque<T>::operator=(const ArrayDeque& other) {
	if (this != &other) {
		delete[] array;
		capacity = other.capacity;
		frontIdx = other.frontIdx;
		backIdx = other.backIdx;
		count = other.count;
		array = new T[capacity];
		for (size_t i = 0; i < capacity; ++i) {
			array[i] = other.array[i];
		}
	}
	return *this;
}

template <typename T>
ArrayDeque<T>::ArrayDeque(ArrayDeque&& other) noexcept
	: array(other.array), capacity(other.capacity),
	frontIdx(other.frontIdx), backIdx(other.backIdx), count(other.count) {
	other.array = nullptr;
	other.capacity = 0;
	other.frontIdx = 0;
	other.backIdx = 0;
	other.count = 0;
}

template <typename T>
ArrayDeque<T>& ArrayDeque<T>::operator=(ArrayDeque&& other) noexcept {
	if (this != &other) {
		delete[] array;
		array = other.array;
		capacity = other.capacity;
		frontIdx = other.frontIdx;
		backIdx = other.backIdx;
		count = other.count;
		other.array = nullptr;
		other.capacity = 0;
		other.frontIdx = 0;
		other.backIdx = 0;
		other.count = 0;
	}
	return *this;
}

template <typename T>
void ArrayDeque<T>::resize(size_t newCapacity) {
	T* newArray = new T[newCapacity];

	for (size_t i = 0; i < count; ++i) {
		newArray[i] = array[(frontIdx + i) % capacity];
	}

	delete[] array;
	array = newArray;
	capacity = newCapacity;
	frontIdx = 0;
	backIdx = (count == 0) ? 0 : count - 1;
}

template <typename T>
void ArrayDeque<T>::doPushFront(const T& value) {
	if (count == capacity) {
		resize(capacity * 2);
	}

	frontIdx = (frontIdx - 1 + capacity) % capacity;
	array[frontIdx] = value;
	count++;
}

template <typename T>
void ArrayDeque<T>::doPushBack(const T& value) {
	if (count == capacity) {
		resize(capacity * 2);
	}

	if (count > 0) {
		backIdx = (backIdx + 1) % capacity;
	}
	array[backIdx] = value;
	count++;
}

template <typename T>
T ArrayDeque<T>::doPopFront() {
	if (doIsEmpty()) {
		throw std::runtime_error("Deque is empty");
	}

	T value = array[frontIdx];
	frontIdx = (frontIdx + 1) % capacity;
	count--;

	if (count == 0) {
		frontIdx = backIdx = 0;
	}

	return value;
}

template <typename T>
T ArrayDeque<T>::doPopBack() {
	if (doIsEmpty()) {
		throw std::runtime_error("Deque is empty");
	}

	T value = array[backIdx];
	if (count > 1) {
		backIdx = (backIdx - 1 + capacity) % capacity;
	}
	count--;

	if (count == 0) {
		frontIdx = backIdx = 0;
	}

	return value;
}

template <typename T>
const T& ArrayDeque<T>::doFront() const {
	if (doIsEmpty()) {
		throw std::runtime_error("Deque is empty");
	}
	return array[frontIdx];
}

template <typename T>
const T& ArrayDeque<T>::doBack() const {
	if (doIsEmpty()) {
		throw std::runtime_error("Deque is empty");
	}
	return array[backIdx];
}

template <typename T>
bool ArrayDeque<T>::doIsEmpty() const {
	return count == 0;
}

template <typename T>
size_t ArrayDeque<T>::doSize() const {
	return count;
}

template <typename T>
void ArrayDeque<T>::doClear() {
	frontIdx = backIdx = 0;
	count = 0;
}

template <typename T>
ListDeque<T>::ListDeque() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
ListDeque<T>::~ListDeque() {
	doClear();
}

template <typename T>
ListDeque<T>::ListDeque(const ListDeque& other) : head(nullptr), tail(nullptr), count(0) {
	Node* current = other.head;
	while (current) {
		doPushBack(current->data);
		current = current->next;
	}
}

template <typename T>
ListDeque<T>& ListDeque<T>::operator=(const ListDeque& other) {
	if (this != &other) {
		doClear();
		Node* current = other.head;
		while (current) {
			doPushBack(current->data);
			current = current->next;
		}
	}
	return *this;
}

template <typename T>
ListDeque<T>::ListDeque(ListDeque&& other) noexcept
	: head(other.head), tail(other.tail), count(other.count) {
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}

template <typename T>
ListDeque<T>& ListDeque<T>::operator=(ListDeque&& other) noexcept {
	if (this != &other) {
		doClear();
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	return *this;
}

template <typename T>
void ListDeque<T>::doPushFront(const T& value) {
	Node* newNode = new Node(value);

	if (doIsEmpty()) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	count++;
}

template <typename T>
void ListDeque<T>::doPushBack(const T& value) {
	Node* newNode = new Node(value);

	if (doIsEmpty()) {
		head = tail = newNode;
	}
	else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}

	count++;
}

template <typename T>
T ListDeque<T>::doPopFront() {
	if (doIsEmpty()) {
		throw std::runtime_error("Deque is empty");
	}

	T value = head->data;
	Node* temp = head;

	if (head == tail) {
		head = tail = nullptr;
	}
	else {
		head = head->next;
		head->prev = nullptr;
	}

	delete temp;
	count--;

	return value;
}

template <typename T>
T ListDeque<T>::doPopBack() {
	if (doIsEmpty()) {
		throw std::runtime_error("Deque is empty");
	}

	T value = tail->data;
	Node* temp = tail;

	if (head == tail) {
		head = tail = nullptr;
	}
	else {
		tail = tail->prev;
		tail->next = nullptr;
	}

	delete temp;
	count--;

	return value;
}

template <typename T>
const T& ListDeque<T>::doFront() const {
	if (doIsEmpty()) {
		throw std::runtime_error("Deque is empty");
	}
	return head->data;
}

template <typename T>
const T& ListDeque<T>::doBack() const {
	if (doIsEmpty()) {
		throw std::runtime_error("Deque is empty");
	}
	return tail->data;
}

template <typename T>
bool ListDeque<T>::doIsEmpty() const {
	return count == 0;
}

template <typename T>
size_t ListDeque<T>::doSize() const {
	return count;
}

template <typename T>
void ListDeque<T>::doClear() {
	while (head) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}

	head = tail = nullptr;
	count = 0;
}

template <typename T>
ArrayImpl<T>::ArrayImpl()
	: capacity(DEFAULT_CAPACITY), frontIdx(0), backIdx(0), count(0) {
	array = new T[capacity];
}

template <typename T>
ArrayImpl<T>::~ArrayImpl() {
	delete[] array;
}

template <typename T>
ArrayImpl<T>::ArrayImpl(const ArrayImpl& other)
	: capacity(other.capacity), frontIdx(other.frontIdx),
	backIdx(other.backIdx), count(other.count) {
	array = new T[capacity];
	for (size_t i = 0; i < capacity; ++i) {
		array[i] = other.array[i];
	}
}

template <typename T>
ArrayImpl<T>& ArrayImpl<T>::operator=(const ArrayImpl& other) {
	if (this != &other) {
		delete[] array;
		capacity = other.capacity;
		frontIdx = other.frontIdx;
		backIdx = other.backIdx;
		count = other.count;
		array = new T[capacity];
		for (size_t i = 0; i < capacity; ++i) {
			array[i] = other.array[i];
		}
	}
	return *this;
}

template <typename T>
ArrayImpl<T>::ArrayImpl(ArrayImpl&& other) noexcept
	: array(other.array), capacity(other.capacity),
	frontIdx(other.frontIdx), backIdx(other.backIdx), count(other.count) {
	other.array = nullptr;
	other.capacity = 0;
	other.frontIdx = 0;
	other.backIdx = 0;
	other.count = 0;
}

template <typename T>
ArrayImpl<T>& ArrayImpl<T>::operator=(ArrayImpl&& other) noexcept {
	if (this != &other) {
		delete[] array;
		array = other.array;
		capacity = other.capacity;
		frontIdx = other.frontIdx;
		backIdx = other.backIdx;
		count = other.count;
		other.array = nullptr;
		other.capacity = 0;
		other.frontIdx = 0;
		other.backIdx = 0;
		other.count = 0;
	}
	return *this;
}

template <typename T>
void ArrayImpl<T>::resize(size_t newCapacity) {
	T* newArray = new T[newCapacity];

	for (size_t i = 0; i < count; ++i) {
		newArray[i] = array[(frontIdx + i) % capacity];
	}

	delete[] array;
	array = newArray;
	capacity = newCapacity;
	frontIdx = 0;
	backIdx = (count == 0) ? 0 : count - 1;
}

template <typename T>
void ArrayImpl<T>::pushFront(const T& value) {
	if (count == capacity) {
		resize(capacity * 2);
	}

	frontIdx = (frontIdx - 1 + capacity) % capacity;
	array[frontIdx] = value;
	count++;
}

template <typename T>
void ArrayImpl<T>::pushBack(const T& value) {
	if (count == capacity) {
		resize(capacity * 2);
	}

	if (count > 0) {
		backIdx = (backIdx + 1) % capacity;
	}
	array[backIdx] = value;
	count++;
}

template <typename T>
T ArrayImpl<T>::popFront() {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty");
	}

	T value = array[frontIdx];
	frontIdx = (frontIdx + 1) % capacity;
	count--;

	if (count == 0) {
		frontIdx = backIdx = 0;
	}

	return value;
}

template <typename T>
T ArrayImpl<T>::popBack() {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty");
	}

	T value = array[backIdx];
	if (count > 1) {
		backIdx = (backIdx - 1 + capacity) % capacity;
	}
	count--;

	if (count == 0) {
		frontIdx = backIdx = 0;
	}

	return value;
}

template <typename T>
const T& ArrayImpl<T>::front() const {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty");
	}
	return array[frontIdx];
}

template <typename T>
const T& ArrayImpl<T>::back() const {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty");
	}
	return array[backIdx];
}

template <typename T>
bool ArrayImpl<T>::isEmpty() const {
	return count == 0;
}

template <typename T>
size_t ArrayImpl<T>::size() const {
	return count;
}

template <typename T>
void ArrayImpl<T>::clear() {
	frontIdx = backIdx = 0;
	count = 0;
}

template <typename T>
ListImpl<T>::ListImpl() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
ListImpl<T>::~ListImpl() {
	clear();
}

template <typename T>
ListImpl<T>::ListImpl(const ListImpl& other) : head(nullptr), tail(nullptr), count(0) {
	Node* current = other.head;
	while (current) {
		pushBack(current->data);
		current = current->next;
	}
}

template <typename T>
ListImpl<T>& ListImpl<T>::operator=(const ListImpl& other) {
	if (this != &other) {
		clear();
		Node* current = other.head;
		while (current) {
			pushBack(current->data);
			current = current->next;
		}
	}
	return *this;
}

template <typename T>
ListImpl<T>::ListImpl(ListImpl&& other) noexcept
	: head(other.head), tail(other.tail), count(other.count) {
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}

template <typename T>
ListImpl<T>& ListImpl<T>::operator=(ListImpl&& other) noexcept {
	if (this != &other) {
		clear();
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	return *this;
}

template <typename T>
void ListImpl<T>::pushFront(const T& value) {
	Node* newNode = new Node(value);

	if (isEmpty()) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	count++;
}

template <typename T>
void ListImpl<T>::pushBack(const T& value) {
	Node* newNode = new Node(value);

	if (isEmpty()) {
		head = tail = newNode;
	}
	else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}

	count++;
}

template <typename T>
T ListImpl<T>::popFront() {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty");
	}

	T value = head->data;
	Node* temp = head;

	if (head == tail) {
		head = tail = nullptr;
	}
	else {
		head = head->next;
		head->prev = nullptr;
	}

	delete temp;
	count--;

	return value;
}

template <typename T>
T ListImpl<T>::popBack() {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty");
	}

	T value = tail->data;
	Node* temp = tail;

	if (head == tail) {
		head = tail = nullptr;
	}
	else {
		tail = tail->prev;
		tail->next = nullptr;
	}

	delete temp;
	count--;

	return value;
}

template <typename T>
const T& ListImpl<T>::front() const {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty");
	}
	return head->data;
}

template <typename T>
const T& ListImpl<T>::back() const {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty");
	}
	return tail->data;
}

template <typename T>
bool ListImpl<T>::isEmpty() const {
	return count == 0;
}

template <typename T>
size_t ListImpl<T>::size() const {
	return count;
}

template <typename T>
void ListImpl<T>::clear() {
	while (head) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}

	head = tail = nullptr;
	count = 0;
}


template class ArrayDeque<int>;
template class ListDeque<int>;
template class ArrayDeque<std::string>;
template class ListDeque<std::string>;
template class ArrayImpl<int>;
template class ListImpl<int>;
template class ArrayImpl<std::string>;
template class ListImpl<std::string>;
