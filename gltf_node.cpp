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

void GLTFNode::_register_methods() {

	register_property<GLTFNode, int>("parent", &GLTFNode::set_parent, &GLTFNode::get_parent, -1); // GLTFNodeIndex
	register_property<GLTFNode, int>("height", &GLTFNode::set_height, &GLTFNode::get_height, 0); // int
	register_property<GLTFNode, Transform>("xform", &GLTFNode::set_xform, &GLTFNode::get_xform, Transform()); // Transform
	register_property<GLTFNode, int>("mesh", &GLTFNode::set_mesh, &GLTFNode::get_mesh, -1); // GLTFMeshIndex
	register_property<GLTFNode, int>("camera", &GLTFNode::set_camera, &GLTFNode::get_camera, -1); // GLTFCameraIndex
	register_property<GLTFNode, int>("skin", &GLTFNode::set_skin, &GLTFNode::get_skin, -1); // GLTFSkinIndex
	register_property<GLTFNode, int>("skeleton", &GLTFNode::set_skeleton, &GLTFNode::get_skeleton, -1); // GLTFSkeletonIndex
	register_property<GLTFNode, bool>("joint", &GLTFNode::set_joint, &GLTFNode::get_joint, false); // bool
	register_property<GLTFNode, Vector3>("translation", &GLTFNode::set_translation, &GLTFNode::get_translation, Vector3(0,0,0)); // Vector3
	register_property<GLTFNode, Quat>("rotation", &GLTFNode::set_rotation, &GLTFNode::get_rotation, Quat()); // Quat
	register_property<GLTFNode, Vector3>("scale", &GLTFNode::set_scale, &GLTFNode::get_scale, Vector3(1,1,1)); // Vector3
	register_property<GLTFNode, PoolIntArray>("children", &GLTFNode::set_children, &GLTFNode::get_children, PoolIntArray()); // Vector<int>
	register_property<GLTFNode, int>("light", &GLTFNode::set_light, &GLTFNode::get_light, -1); // GLTFLightIndex
}

GLTFNodeIndex GLTFNode::get_parent() {
	return parent;
}

void GLTFNode::set_parent(GLTFNodeIndex p_parent) {
	parent = p_parent;
}

int GLTFNode::get_height() {
	return height;
}

void GLTFNode::set_height(int p_height) {
	height = p_height;
}

Transform GLTFNode::get_xform() {
	return xform;
}

void GLTFNode::set_xform(Transform p_xform) {
	xform = p_xform;
}

GLTFMeshIndex GLTFNode::get_mesh() {
	return mesh;
}

void GLTFNode::set_mesh(GLTFMeshIndex p_mesh) {
	mesh = p_mesh;
}

GLTFCameraIndex GLTFNode::get_camera() {
	return camera;
}

void GLTFNode::set_camera(GLTFCameraIndex p_camera) {
	camera = p_camera;
}

GLTFSkinIndex GLTFNode::get_skin() {
	return skin;
}

void GLTFNode::set_skin(GLTFSkinIndex p_skin) {
	skin = p_skin;
}

GLTFSkeletonIndex GLTFNode::get_skeleton() {
	return skeleton;
}

void GLTFNode::set_skeleton(GLTFSkeletonIndex p_skeleton) {
	skeleton = p_skeleton;
}

bool GLTFNode::get_joint() {
	return joint;
}

void GLTFNode::set_joint(bool p_joint) {
	joint = p_joint;
}

Vector3 GLTFNode::get_translation() {
	return translation;
}

void GLTFNode::set_translation(Vector3 p_translation) {
	translation = p_translation;
}

Quat GLTFNode::get_rotation() {
	return rotation;
}

void GLTFNode::set_rotation(Quat p_rotation) {
	rotation = p_rotation;
}

Vector3 GLTFNode::get_scale() {
	return scale;
}

void GLTFNode::set_scale(Vector3 p_scale) {
	scale = p_scale;
}

PoolIntArray GLTFNode::get_children() {
	return children;
}

void GLTFNode::set_children(PoolIntArray p_children) {
	children = p_children;
}

GLTFLightIndex GLTFNode::get_light() {
	return light;
}

void GLTFNode::set_light(GLTFLightIndex p_light) {
	light = p_light;
}
