/*************************************************************************/
/*  gltf_buffer_view.cpp                                                 */
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

#include "gltf_buffer_view.h"

void GLTFBufferView::_register_methods() {
	register_method("_init", &GLTFBufferView::_init);

	register_property<GLTFBufferView, int>("buffer", &GLTFBufferView::set_buffer, &GLTFBufferView::get_buffer, -1); // GLTFBufferIndex
	register_property<GLTFBufferView, int>("byte_offset", &GLTFBufferView::set_byte_offset, &GLTFBufferView::get_byte_offset, 0); // int
	register_property<GLTFBufferView, int>("byte_length", &GLTFBufferView::set_byte_length, &GLTFBufferView::get_byte_length, 0); // int
	register_property<GLTFBufferView, int>("byte_stride", &GLTFBufferView::set_byte_stride, &GLTFBufferView::get_byte_stride, -1); // int
	register_property<GLTFBufferView, bool>("indices", &GLTFBufferView::set_indices, &GLTFBufferView::get_indices, false); // bool
}

GLTFBufferIndex GLTFBufferView::get_buffer() {
	return buffer;
}

void GLTFBufferView::set_buffer(GLTFBufferIndex p_buffer) {
	buffer = p_buffer;
}

int GLTFBufferView::get_byte_offset() {
	return byte_offset;
}

void GLTFBufferView::set_byte_offset(int p_byte_offset) {
	byte_offset = p_byte_offset;
}

int GLTFBufferView::get_byte_length() {
	return byte_length;
}

void GLTFBufferView::set_byte_length(int p_byte_length) {
	byte_length = p_byte_length;
}

int GLTFBufferView::get_byte_stride() {
	return byte_stride;
}

void GLTFBufferView::set_byte_stride(int p_byte_stride) {
	byte_stride = p_byte_stride;
}

bool GLTFBufferView::get_indices() {
	return indices;
}

void GLTFBufferView::set_indices(bool p_indices) {
	indices = p_indices;
}
