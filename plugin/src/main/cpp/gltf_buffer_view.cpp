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

void GLTFBufferView_::_register_methods() {
	register_method("_init", &GLTFBufferView_::_init);

	register_property<GLTFBufferView_, int>("buffer", &GLTFBufferView_::set_buffer, &GLTFBufferView_::get_buffer, -1); // GLTFBufferIndex
	register_property<GLTFBufferView_, int>("byte_offset", &GLTFBufferView_::set_byte_offset, &GLTFBufferView_::get_byte_offset, 0); // int
	register_property<GLTFBufferView_, int>("byte_length", &GLTFBufferView_::set_byte_length, &GLTFBufferView_::get_byte_length, 0); // int
	register_property<GLTFBufferView_, int>("byte_stride", &GLTFBufferView_::set_byte_stride, &GLTFBufferView_::get_byte_stride, -1); // int
	register_property<GLTFBufferView_, bool>("indices", &GLTFBufferView_::set_indices, &GLTFBufferView_::get_indices, false); // bool
}

GLTFBufferIndex GLTFBufferView_::get_buffer() {
	return buffer;
}

void GLTFBufferView_::set_buffer(GLTFBufferIndex p_buffer) {
	buffer = p_buffer;
}

int GLTFBufferView_::get_byte_offset() {
	return byte_offset;
}

void GLTFBufferView_::set_byte_offset(int p_byte_offset) {
	byte_offset = p_byte_offset;
}

int GLTFBufferView_::get_byte_length() {
	return byte_length;
}

void GLTFBufferView_::set_byte_length(int p_byte_length) {
	byte_length = p_byte_length;
}

int GLTFBufferView_::get_byte_stride() {
	return byte_stride;
}

void GLTFBufferView_::set_byte_stride(int p_byte_stride) {
	byte_stride = p_byte_stride;
}

bool GLTFBufferView_::get_indices() {
	return indices;
}

void GLTFBufferView_::set_indices(bool p_indices) {
	indices = p_indices;
}
