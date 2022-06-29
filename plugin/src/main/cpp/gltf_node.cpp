/*************************************************************************/
/*  gltf_node.cpp                                                        */
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

#include "gltf_node.h"

void GLTFNode_::_register_methods() {
	register_method("_init", &GLTFNode_::_init);

	register_property<GLTFNode_, int>("parent", &GLTFNode_::set_parent, &GLTFNode_::get_parent, -1); // GLTFNodeIndex
	register_property<GLTFNode_, int>("height", &GLTFNode_::set_height, &GLTFNode_::get_height, 0); // int
	register_property<GLTFNode_, Transform>("xform", &GLTFNode_::set_xform, &GLTFNode_::get_xform, Transform()); // Transform
	register_property<GLTFNode_, int>("mesh", &GLTFNode_::set_mesh, &GLTFNode_::get_mesh, -1); // GLTFMeshIndex
	register_property<GLTFNode_, int>("camera", &GLTFNode_::set_camera, &GLTFNode_::get_camera, -1); // GLTFCameraIndex
	register_property<GLTFNode_, int>("skin", &GLTFNode_::set_skin, &GLTFNode_::get_skin, -1); // GLTFSkinIndex
	register_property<GLTFNode_, int>("skeleton", &GLTFNode_::set_skeleton, &GLTFNode_::get_skeleton, -1); // GLTFSkeletonIndex
	register_property<GLTFNode_, bool>("joint", &GLTFNode_::set_joint, &GLTFNode_::get_joint, false); // bool
	register_property<GLTFNode_, Vector3>("translation", &GLTFNode_::set_translation, &GLTFNode_::get_translation, Vector3(0,0,0)); // Vector3
	register_property<GLTFNode_, Quat>("rotation", &GLTFNode_::set_rotation, &GLTFNode_::get_rotation, Quat()); // Quat
	register_property<GLTFNode_, Vector3>("scale", &GLTFNode_::set_scale, &GLTFNode_::get_scale, Vector3(1,1,1)); // Vector3
	register_property<GLTFNode_, PoolIntArray>("children", &GLTFNode_::set_children, &GLTFNode_::get_children, PoolIntArray()); // Vector<int>
	register_property<GLTFNode_, int>("light", &GLTFNode_::set_light, &GLTFNode_::get_light, -1); // GLTFLightIndex
}

GLTFNodeIndex GLTFNode_::get_parent() {
	return parent;
}

void GLTFNode_::set_parent(GLTFNodeIndex p_parent) {
	parent = p_parent;
}

int GLTFNode_::get_height() {
	return height;
}

void GLTFNode_::set_height(int p_height) {
	height = p_height;
}

Transform GLTFNode_::get_xform() {
	return xform;
}

void GLTFNode_::set_xform(Transform p_xform) {
	xform = p_xform;
}

GLTFMeshIndex GLTFNode_::get_mesh() {
	return mesh;
}

void GLTFNode_::set_mesh(GLTFMeshIndex p_mesh) {
	mesh = p_mesh;
}

GLTFCameraIndex GLTFNode_::get_camera() {
	return camera;
}

void GLTFNode_::set_camera(GLTFCameraIndex p_camera) {
	camera = p_camera;
}

GLTFSkinIndex GLTFNode_::get_skin() {
	return skin;
}

void GLTFNode_::set_skin(GLTFSkinIndex p_skin) {
	skin = p_skin;
}

GLTFSkeletonIndex GLTFNode_::get_skeleton() {
	return skeleton;
}

void GLTFNode_::set_skeleton(GLTFSkeletonIndex p_skeleton) {
	skeleton = p_skeleton;
}

bool GLTFNode_::get_joint() {
	return joint;
}

void GLTFNode_::set_joint(bool p_joint) {
	joint = p_joint;
}

Vector3 GLTFNode_::get_translation() {
	return translation;
}

void GLTFNode_::set_translation(Vector3 p_translation) {
	translation = p_translation;
}

Quat GLTFNode_::get_rotation() {
	return rotation;
}

void GLTFNode_::set_rotation(Quat p_rotation) {
	rotation = p_rotation;
}

Vector3 GLTFNode_::get_scale() {
	return scale;
}

void GLTFNode_::set_scale(Vector3 p_scale) {
	scale = p_scale;
}

PoolIntArray GLTFNode_::get_children() {
	return children;
}

void GLTFNode_::set_children(PoolIntArray p_children) {
	children = p_children;
}

GLTFLightIndex GLTFNode_::get_light() {
	return light;
}

void GLTFNode_::set_light(GLTFLightIndex p_light) {
	light = p_light;
}
