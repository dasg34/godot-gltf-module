/*************************************************************************/
/*  disjoint_set.h                                                       */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <malloc.h>
#include <algorithm>

/**
	@author Lyuma <xn.lyuma@gmail.com>
*/

template <class T>
class Vector {

	size_t size_;
    size_t capacity_;

public:

	T *write;

	Vector() {
		write = (T*)malloc(sizeof(T) * 1);
		size_ = 0;
        capacity_ = 1;
	}
    ~Vector() {
        for (size_t i = 0; i < size_; i++) {
            write[i].~T();
        }
        free(write);
    }
	Vector<T> &operator=(const Vector<T> &other) {
        resize(0);
        append_array(other);
        return *this;
    }
	Vector(const Vector<T> &other) {
        *this = other;
    }
    void push_back(const T& a) {
        if (size_ >= capacity_) {
            reallocate(4 + capacity_ * 2);
        }
        new(&(write[size_])) T(a);
        size_++;
    }

    void clear() {
        resize(0);
    }

	void reallocate(size_t sz) {
        if (sz == capacity_) {
            return;
        }
        ERR_FAIL_COND(sz == 0);
        ERR_FAIL_COND(sz < size_);
		T *new_data = (T*)malloc(sizeof(T) * sz);
        for (size_t i = 0; i < size_; i++) {
            new(&(new_data[i])) T (static_cast<T&&>(write[i]));
            write[i].~T();
        }
        free(write);
        write = new_data;
        capacity_ = sz;
	}
	void resize(size_t sz) {
        if (sz == size_) {
            return;
        }
        if (sz < size_) {
            for (size_t i = sz; i < size_; i++) {
                write[i].~T();
            }
        }
        if (sz > size_) {
            if (sz > capacity_) {
                reallocate(sz);
            }
            for (size_t i = size_; i < sz; i++) {
                new(&(write[i])) T;
            }
        }
		size_ = sz;
	}
    size_t size() const {
        return size_;
    }
    bool empty() const {
        return size_ == 0;
    }
	T* ptrw() {
		return write;
	}
	const T* ptr() const {
		return write;
	}
	T &operator[](size_t idx) {
		ERR_FAIL_INDEX_V(idx, size_, write[0]); // this bounds check may still crash if empty.
		return write[idx];
	}
	const T &operator[](size_t idx) const {
		ERR_FAIL_INDEX_V(idx, size_, write[0]); // this bounds check may still crash if empty.
		return write[idx];
	}
    int find(const T&needle) const {
        for (int i = 0; i < size_; i++) {
            if (write[i] == needle) {
                return i;
            }
        }
        return -1;
    }
    template <class PoolOtherArray>
    void append_array(PoolOtherArray other) {
        size_t other_size = other.size();
        if (other_size == 0) {
            return;
        }
        if (capacity_ < size_ + other_size) {
            reallocate(size_ + other_size);
        }
        typename PoolOtherArray::Read read = other.read();
        const T *ptr = read.ptr();
        memcpy(&write[size_], ptr, sizeof(T) * other_size);
        size_ += other_size;
    }

    void append_array(const Vector<T> &other) {
        if (other.size_ == 0) {
            return;
        }
        if (capacity_ < size_ + other.size_) {
            reallocate(size_ + other.size_);
        }
        for (size_t i = 0; i < other.size_; i++) {
            new (&write[size_ + i]) T (other[i]);
        }
        size_ += other.size_;
    }
    void sort() {
        std::sort(&write[0], &write[size_]);
    }
};

#endif