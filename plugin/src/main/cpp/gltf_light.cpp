/*************************************************************************/
/*  gltf_light.cpp                                                       */
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

#include "gltf_light.h"

void GLTFLight_::_register_methods() {
	register_method("_init", &GLTFLight_::_init);

	register_property<GLTFLight_, Color>("color", &GLTFLight_::set_color, &GLTFLight_::get_color, Color()); // Color
	register_property<GLTFLight_, float>("intensity", &GLTFLight_::set_intensity, &GLTFLight_::get_intensity, 0); // float
	register_property<GLTFLight_, String>("type", &GLTFLight_::set_type, &GLTFLight_::get_type, String()); // String
	register_property<GLTFLight_, float>("range", &GLTFLight_::set_range, &GLTFLight_::get_range, 0); // float
	register_property<GLTFLight_, float>("inner_cone_angle", &GLTFLight_::set_inner_cone_angle, &GLTFLight_::get_inner_cone_angle, 0); // float
	register_property<GLTFLight_, float>("outer_cone_angle", &GLTFLight_::set_outer_cone_angle, &GLTFLight_::get_outer_cone_angle, 0); // float
}

Color GLTFLight_::get_color() {
	return color;
}

void GLTFLight_::set_color(Color p_color) {
	color = p_color;
}

float GLTFLight_::get_intensity() {
	return intensity;
}

void GLTFLight_::set_intensity(float p_intensity) {
	intensity = p_intensity;
}

String GLTFLight_::get_type() {
	return type;
}

void GLTFLight_::set_type(String p_type) {
	type = p_type;
}

float GLTFLight_::get_range() {
	return range;
}

void GLTFLight_::set_range(float p_range) {
	range = p_range;
}

float GLTFLight_::get_inner_cone_angle() {
	return inner_cone_angle;
}

void GLTFLight_::set_inner_cone_angle(float p_inner_cone_angle) {
	inner_cone_angle = p_inner_cone_angle;
}

float GLTFLight_::get_outer_cone_angle() {
	return outer_cone_angle;
}

void GLTFLight_::set_outer_cone_angle(float p_outer_cone_angle) {
	outer_cone_angle = p_outer_cone_angle;
}
