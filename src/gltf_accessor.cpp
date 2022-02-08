/*************************************************************************/
/*  gltf_accessor.cpp                                                    */
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

#include "gltf_accessor.h"

void GLTFAccessor::_register_methods() {
	register_method("_init", &GLTFAccessor::_init);

	register_property<GLTFAccessor, int>("buffer_view", &GLTFAccessor::set_buffer_view, &GLTFAccessor::get_buffer_view, 0); // GLTFBufferViewIndex
	register_property<GLTFAccessor, int>("byte_offset", &GLTFAccessor::set_byte_offset, &GLTFAccessor::get_byte_offset, 0); // int
	register_property<GLTFAccessor, int>("component_type", &GLTFAccessor::set_component_type, &GLTFAccessor::get_component_type, 0); // int
	register_property<GLTFAccessor, bool>("normalized", &GLTFAccessor::set_normalized, &GLTFAccessor::get_normalized, false); // bool
	register_property<GLTFAccessor, int>("count", &GLTFAccessor::set_count, &GLTFAccessor::get_count, 0); // int
	register_property<GLTFAccessor, int>("type", &GLTFAccessor::set_type, &GLTFAccessor::get_type, 0); // GLTFDocument::GLTFType
	register_property<GLTFAccessor, PoolRealArray>("min", &GLTFAccessor::set_min, &GLTFAccessor::get_min, PoolRealArray()); // Vector<real_t>
	register_property<GLTFAccessor, PoolRealArray>("max", &GLTFAccessor::set_max, &GLTFAccessor::get_max, PoolRealArray()); // Vector<real_t>
	register_property<GLTFAccessor, int>("sparse_count", &GLTFAccessor::set_sparse_count, &GLTFAccessor::get_sparse_count, 0); // int
	register_property<GLTFAccessor, int>("sparse_indices_buffer_view", &GLTFAccessor::set_sparse_indices_buffer_view, &GLTFAccessor::get_sparse_indices_buffer_view, 0); // int
	register_property<GLTFAccessor, int>("sparse_indices_byte_offset", &GLTFAccessor::set_sparse_indices_byte_offset, &GLTFAccessor::get_sparse_indices_byte_offset, 0); // int
	register_property<GLTFAccessor, int>("sparse_indices_component_type", &GLTFAccessor::set_sparse_indices_component_type, &GLTFAccessor::get_sparse_indices_component_type, 0); // int
	register_property<GLTFAccessor, int>("sparse_values_buffer_view", &GLTFAccessor::set_sparse_values_buffer_view, &GLTFAccessor::get_sparse_values_buffer_view, 0); // int
	register_property<GLTFAccessor, int>("sparse_values_byte_offset", &GLTFAccessor::set_sparse_values_byte_offset, &GLTFAccessor::get_sparse_values_byte_offset, 0); // int
}

GLTFBufferViewIndex GLTFAccessor::get_buffer_view() {
	return buffer_view;
}

void GLTFAccessor::set_buffer_view(GLTFBufferViewIndex p_buffer_view) {
	buffer_view = p_buffer_view;
}

int GLTFAccessor::get_byte_offset() {
	return byte_offset;
}

void GLTFAccessor::set_byte_offset(int p_byte_offset) {
	byte_offset = p_byte_offset;
}

int GLTFAccessor::get_component_type() {
	return component_type;
}

void GLTFAccessor::set_component_type(int p_component_type) {
	component_type = p_component_type;
}

bool GLTFAccessor::get_normalized() {
	return normalized;
}

void GLTFAccessor::set_normalized(bool p_normalized) {
	normalized = p_normalized;
}

int GLTFAccessor::get_count() {
	return count;
}

void GLTFAccessor::set_count(int p_count) {
	count = p_count;
}

int GLTFAccessor::get_type() {
	return (int)type;
}

void GLTFAccessor::set_type(int p_type) {
	type = (GLTFDocument::GLTFType)p_type; // TODO: Register enum
}

PoolRealArray GLTFAccessor::get_min() {
	return min;
}

void GLTFAccessor::set_min(PoolRealArray p_min) {
	min = p_min;
}

PoolRealArray GLTFAccessor::get_max() {
	return max;
}

void GLTFAccessor::set_max(PoolRealArray p_max) {
	max = p_max;
}

int GLTFAccessor::get_sparse_count() {
	return sparse_count;
}

void GLTFAccessor::set_sparse_count(int p_sparse_count) {
	sparse_count = p_sparse_count;
}

int GLTFAccessor::get_sparse_indices_buffer_view() {
	return sparse_indices_buffer_view;
}

void GLTFAccessor::set_sparse_indices_buffer_view(int p_sparse_indices_buffer_view) {
	sparse_indices_buffer_view = p_sparse_indices_buffer_view;
}

int GLTFAccessor::get_sparse_indices_byte_offset() {
	return sparse_indices_byte_offset;
}

void GLTFAccessor::set_sparse_indices_byte_offset(int p_sparse_indices_byte_offset) {
	sparse_indices_byte_offset = p_sparse_indices_byte_offset;
}

int GLTFAccessor::get_sparse_indices_component_type() {
	return sparse_indices_component_type;
}

void GLTFAccessor::set_sparse_indices_component_type(int p_sparse_indices_component_type) {
	sparse_indices_component_type = p_sparse_indices_component_type;
}

int GLTFAccessor::get_sparse_values_buffer_view() {
	return sparse_values_buffer_view;
}

void GLTFAccessor::set_sparse_values_buffer_view(int p_sparse_values_buffer_view) {
	sparse_values_buffer_view = p_sparse_values_buffer_view;
}

int GLTFAccessor::get_sparse_values_byte_offset() {
	return sparse_values_byte_offset;
}

void GLTFAccessor::set_sparse_values_byte_offset(int p_sparse_values_byte_offset) {
	sparse_values_byte_offset = p_sparse_values_byte_offset;
}
