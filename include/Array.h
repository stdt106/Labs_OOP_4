#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <utility>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t currentSize;
    size_t currentCapacity;

    void resize(size_t newCapacity) {
        
        std::shared_ptr<T[]> newData(new T[newCapacity]);
        
        
        for (size_t i = 0; i < currentSize; ++i) {
            newData[i] = std::move(data[i]);
        }
        
        data = newData;
        currentCapacity = newCapacity;
    }

public:
    Array() : data(nullptr), currentSize(0), currentCapacity(0) {}
    
    Array(size_t initialCapacity) 
        : data(new T[initialCapacity]), currentSize(0), currentCapacity(initialCapacity) {}

    
    void push_back(T&& value) {
        if (currentSize >= currentCapacity) {
            size_t newCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
            resize(newCapacity);
        }
        data[currentSize] = std::move(value);
        ++currentSize;
    }

    
    void push_back(const T& value) {
        if (currentSize >= currentCapacity) {
            size_t newCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
            resize(newCapacity);
        }
        data[currentSize] = value;
        ++currentSize;
    }

    T& operator[](size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void remove(size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < currentSize - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --currentSize;
    }

    size_t size() const { return currentSize; }
    size_t capacity() const { return currentCapacity; }
    bool empty() const { return currentSize == 0; }

    T* begin() { return data.get(); }
    T* end() { return data.get() + currentSize; }
    const T* begin() const { return data.get(); }
    const T* end() const { return data.get() + currentSize; }
};

#endif