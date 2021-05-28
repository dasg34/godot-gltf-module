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

#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <PoolArrays.hpp>
#include "map.h"

/**
	@author Marios Staikopoulos <marios@staik.net>
*/

#ifndef SWAP
#define SWAP(m_x, m_y) __swap_tmpl((m_x), (m_y))
template <class T>
inline void __swap_tmpl(T &x, T &y) {
	T aux = x;
	x = y;
	y = aux;
}
#endif //swap

template <class T>
struct DJComparator {
        inline bool operator()(const T &p_a, const T &p_b) const { return (p_a < p_b); }
};

/* This DisjointSet class uses Find with path compression and Union by rank */
template <typename T, class C = DJComparator<T>>
class DisjointSet {
	struct Element {
		T object;
		Element *parent = nullptr;
		int rank = 0;
	};

	typedef Map<T, Element *, C> MapT;

	MapT elements;

	Element *get_parent(Element *element);

	inline Element *insert_or_get(T object);

public:
	~DisjointSet();

	inline void insert(T object) { (void)insert_or_get(object); }

	void create_union(T a, T b);

	template <class ArrayType>
	void get_representatives(ArrayType &out_representatives) {
		for (typename MapT::Element *itr = elements.front(); itr != nullptr; itr = itr->next()) {
			Element *element = itr->value();
			if (element->parent == element) {
				out_representatives.push_back(element->object);
			}
		}
	}

	template <class ArrayType>
	void get_members(ArrayType &out_members, T representative) {
		typename MapT::Element *rep_itr = elements.find(representative);
		ERR_FAIL_COND(rep_itr == nullptr);

		Element *rep_element = rep_itr->value();
		ERR_FAIL_COND(rep_element->parent != rep_element);

		for (typename MapT::Element *itr = elements.front(); itr != nullptr; itr = itr->next()) {
			Element *parent = get_parent(itr->value());
			if (parent == rep_element) {
				out_members.push_back(itr->key());
			}
		}
	}

};

/* FUNCTIONS */

template <typename T, class C>
DisjointSet<T, C>::~DisjointSet() {
	for (typename MapT::Element *itr = elements.front(); itr != nullptr; itr = itr->next()) {
		itr->value()->~Element();
		std::free(itr->value());
	}
}

template <typename T, class C>
typename DisjointSet<T, C>::Element *DisjointSet<T, C>::get_parent(Element *element) {
	if (element->parent != element) {
		element->parent = get_parent(element->parent);
	}

	return element->parent;
}

template <typename T, class C>
typename DisjointSet<T, C>::Element *DisjointSet<T, C>::insert_or_get(T object) {
	typename MapT::Element *itr = elements.find(object);
	if (itr != nullptr) {
		return itr->value();
	}

	Element *new_element = (Element*)std::malloc(sizeof(Element));
	new(new_element) Element;
	new_element->object = object;
	new_element->parent = new_element;
	elements.insert(object, new_element);

	return new_element;
}

template <typename T, class C>
void DisjointSet<T, C>::create_union(T a, T b) {
	Element *x = insert_or_get(a);
	Element *y = insert_or_get(b);

	Element *x_root = get_parent(x);
	Element *y_root = get_parent(y);

	// Already in the same set
	if (x_root == y_root) {
		return;
	}

	// Not in the same set, merge
	if (x_root->rank < y_root->rank) {
		SWAP(x_root, y_root);
	}

	// Merge y_root into x_root
	y_root->parent = x_root;
	if (x_root->rank == y_root->rank) {
		++x_root->rank;
	}
}

#endif
