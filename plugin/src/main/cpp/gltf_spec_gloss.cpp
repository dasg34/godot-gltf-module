/*************************************************************************/
/*  gltf_spec_gloss.cpp                                                  */
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

#include "gltf_spec_gloss.h"

void GLTFSpecGloss_::_register_methods() {
	register_method("_init", &GLTFSpecGloss_::_init);

	register_property<GLTFSpecGloss_, Ref<Image>>("diffuse_img", &GLTFSpecGloss_::set_diffuse_img, &GLTFSpecGloss_::get_diffuse_img, Ref<Image>()); // Ref<Image>
	register_property<GLTFSpecGloss_, Color>("diffuse_factor", &GLTFSpecGloss_::set_diffuse_factor, &GLTFSpecGloss_::get_diffuse_factor, Color(1.0f, 1.0f, 1.0f)); // Color
	register_property<GLTFSpecGloss_, float>("gloss_factor", &GLTFSpecGloss_::set_gloss_factor, &GLTFSpecGloss_::get_gloss_factor, 1.0); // float
	register_property<GLTFSpecGloss_, Color>("specular_factor", &GLTFSpecGloss_::set_specular_factor, &GLTFSpecGloss_::get_specular_factor, Color(1.0f, 1.0f, 1.0f)); // Color
	register_property<GLTFSpecGloss_, Ref<Image>>("spec_gloss_img", &GLTFSpecGloss_::set_spec_gloss_img, &GLTFSpecGloss_::get_spec_gloss_img, Ref<Image>()); // Ref<Image>
}

Ref<Image> GLTFSpecGloss_::get_diffuse_img() {
	return diffuse_img;
}

void GLTFSpecGloss_::set_diffuse_img(Ref<Image> p_diffuse_img) {
	diffuse_img = p_diffuse_img;
}

Color GLTFSpecGloss_::get_diffuse_factor() {
	return diffuse_factor;
}

void GLTFSpecGloss_::set_diffuse_factor(Color p_diffuse_factor) {
	diffuse_factor = p_diffuse_factor;
}

float GLTFSpecGloss_::get_gloss_factor() {
	return gloss_factor;
}

void GLTFSpecGloss_::set_gloss_factor(float p_gloss_factor) {
	gloss_factor = p_gloss_factor;
}

Color GLTFSpecGloss_::get_specular_factor() {
	return specular_factor;
}

void GLTFSpecGloss_::set_specular_factor(Color p_specular_factor) {
	specular_factor = p_specular_factor;
}

Ref<Image> GLTFSpecGloss_::get_spec_gloss_img() {
	return spec_gloss_img;
}

void GLTFSpecGloss_::set_spec_gloss_img(Ref<Image> p_spec_gloss_img) {
	spec_gloss_img = p_spec_gloss_img;
}
