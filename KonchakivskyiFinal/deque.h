#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <iostream>
#include <functional>

template <typename T>
class Deque {
public:
    void pushFront(const T& value) { doPushFront(value); }
    void pushBack(const T& value) { doPushBack(value); }
    T popFront() { return doPopFront(); }
    T popBack() { return doPopBack(); }
    const T& front() const { return doFront(); }
    const T& back() const { return doBack(); }
    bool isEmpty() const { return doIsEmpty(); }
    size_t size() const { return doSize(); }
    void clear() { doClear(); }

    virtual ~Deque() = default;

protected:
    virtual void doPushFront(const T& value) = 0;
    virtual void doPushBack(const T& value) = 0;
    virtual T doPopFront() = 0;
    virtual T doPopBack() = 0;
    virtual const T& doFront() const = 0;
    virtual const T& doBack() const = 0;
    virtual bool doIsEmpty() const = 0;
    virtual size_t doSize() const = 0;
    virtual void doClear() = 0;
};

template <typename T>
class ArrayDeque : public Deque<T> {
private:
    static const size_t DEFAULT_CAPACITY = 10;
    T* array;
    size_t capacity;
    size_t frontIdx;
    size_t backIdx;
    size_t count;

    void resize(size_t newCapacity);

protected:
    void doPushFront(const T& value) override;
    void doPushBack(const T& value) override;
    T doPopFront() override;
    T doPopBack() override;
    const T& doFront() const override;
    const T& doBack() const override;
    bool doIsEmpty() const override;
    size_t doSize() const override;
    void doClear() override;

public:
    ArrayDeque();
    ~ArrayDeque();
    ArrayDeque(const ArrayDeque& other);
    ArrayDeque& operator=(const ArrayDeque& other);
    ArrayDeque(ArrayDeque&& other) noexcept;
    ArrayDeque& operator=(ArrayDeque&& other) noexcept;
};

template <typename T>
class ListDeque : public Deque<T> {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t count;

protected:
    void doPushFront(const T& value) override;
    void doPushBack(const T& value) override;
    T doPopFront() override;
    T doPopBack() override;
    const T& doFront() const override;
    const T& doBack() const override;
    bool doIsEmpty() const override;
    size_t doSize() const override;
    void doClear() override;

public:
    ListDeque();
    ~ListDeque();
    ListDeque(const ListDeque& other);
    ListDeque& operator=(const ListDeque& other);
    ListDeque(ListDeque&& other) noexcept;
    ListDeque& operator=(ListDeque&& other) noexcept;
};

template <typename T, typename Implementation>
class DequeWithImpl {
private:
    Implementation impl;

public:
    void pushFront(const T& value) { impl.pushFront(value); }
    void pushBack(const T& value) { impl.pushBack(value); }
    T popFront() { return impl.popFront(); }
    T popBack() { return impl.popBack(); }
    const T& front() const { return impl.front(); }
    const T& back() const { return impl.back(); }
    bool isEmpty() const { return impl.isEmpty(); }
    size_t size() const { return impl.size(); }
    void clear() { impl.clear(); }
};

template <typename T>
class ArrayImpl {
private:
    static const size_t DEFAULT_CAPACITY = 10;
    T* array;
    size_t capacity;
    size_t frontIdx;
    size_t backIdx;
    size_t count;

    void resize(size_t newCapacity);

public:
    ArrayImpl();
    ~ArrayImpl();
    ArrayImpl(const ArrayImpl& other);
    ArrayImpl& operator=(const ArrayImpl& other);
    ArrayImpl(ArrayImpl&& other) noexcept;
    ArrayImpl& operator=(ArrayImpl&& other) noexcept;

    void pushFront(const T& value);
    void pushBack(const T& value);
    T popFront();
    T popBack();
    const T& front() const;
    const T& back() const;
    bool isEmpty() const;
    size_t size() const;
    void clear();
};

template <typename T>
class ListImpl {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t count;

public:
    ListImpl();
    ~ListImpl();
    ListImpl(const ListImpl& other);
    ListImpl& operator=(const ListImpl& other);
    ListImpl(ListImpl&& other) noexcept;
    ListImpl& operator=(ListImpl&& other) noexcept;

    void pushFront(const T& value);
    void pushBack(const T& value);
    T popFront();
    T popBack();
    const T& front() const;
    const T& back() const;
    bool isEmpty() const;
    size_t size() const;
    void clear();
};

template <typename T>
using ArrayDequeComposition = DequeWithImpl<T, ArrayImpl<T>>;

template <typename T>
using ListDequeComposition = DequeWithImpl<T, ListImpl<T>>;


#endif