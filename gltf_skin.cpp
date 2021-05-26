/*************************************************************************/
/*  gltf_skin.cpp                                                        */
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

#include "gltf_skin.h"
#include <Skin.hpp>

void GLTFSkin::_register_methods() {
	register_method("_init", &GLTFSkin::_init);

	register_property<GLTFSkin, int>("skin_root", &GLTFSkin::set_skin_root, &GLTFSkin::get_skin_root, -1); // GLTFNodeIndex
	register_property<GLTFSkin, PoolIntArray>("joints_original", &GLTFSkin::set_joints_original, &GLTFSkin::get_joints_original, PoolIntArray()); // Vector<GLTFNodeIndex>
	register_property<GLTFSkin, Array>("inverse_binds", &GLTFSkin::set_inverse_binds, &GLTFSkin::get_inverse_binds, Array()); // Vector<Transform>
	register_property<GLTFSkin, PoolIntArray>("joints", &GLTFSkin::set_joints, &GLTFSkin::get_joints, PoolIntArray()); // Vector<GLTFNodeIndex>
	register_property<GLTFSkin, PoolIntArray>("non_joints", &GLTFSkin::set_non_joints, &GLTFSkin::get_non_joints, PoolIntArray()); // Vector<GLTFNodeIndex>
	register_property<GLTFSkin, PoolIntArray>("roots", &GLTFSkin::set_roots, &GLTFSkin::get_roots, PoolIntArray()); // Vector<GLTFNodeIndex>
	register_property<GLTFSkin, int>("skeleton", &GLTFSkin::set_skeleton, &GLTFSkin::get_skeleton, -1); // int
	register_property<GLTFSkin, Dictionary>("joint_i_to_bone_i", &GLTFSkin::set_joint_i_to_bone_i, &GLTFSkin::get_joint_i_to_bone_i, Dictionary()); // Map<int,
	register_property<GLTFSkin, Dictionary>("joint_i_to_name", &GLTFSkin::set_joint_i_to_name, &GLTFSkin::get_joint_i_to_name, Dictionary()); // Map<int,
	register_property<GLTFSkin, Ref<Skin>>("godot_skin", &GLTFSkin::set_godot_skin, &GLTFSkin::get_godot_skin, Ref<Skin>()); // Ref<Skin>
}

GLTFNodeIndex GLTFSkin::get_skin_root() {
	return skin_root;
}

void GLTFSkin::set_skin_root(GLTFNodeIndex p_skin_root) {
	skin_root = p_skin_root;
}

PoolIntArray GLTFSkin::get_joints_original() {
	return joints_original;
}

void GLTFSkin::set_joints_original(PoolIntArray p_joints_original) {
	joints_original = p_joints_original;
}

Array GLTFSkin::get_inverse_binds() {
	return GLTFDocument::to_array(inverse_binds);
}

void GLTFSkin::set_inverse_binds(Array p_inverse_binds) {
	GLTFDocument::set_from_array(inverse_binds, p_inverse_binds);
}

PoolIntArray GLTFSkin::get_joints() {
	PoolIntArray ret;
	ret.resize(joints.size());
	PoolIntArray::Write wr = ret.write();
	int *ptr = wr.ptr();
	for (int i = 0; i < joints.size(); i++) {
		ptr[i] = joints[i];
	}
	return ret;
}

void GLTFSkin::set_joints(PoolIntArray p_joints) {
	joints.resize(0);
	joints.append_array(p_joints);
}

PoolIntArray GLTFSkin::get_non_joints() {
	PoolIntArray ret;
	ret.resize(non_joints.size());
	PoolIntArray::Write wr = ret.write();
	int *ptr = wr.ptr();
	for (int i = 0; i < non_joints.size(); i++) {
		ptr[i] = non_joints[i];
	}
	return ret;
}

void GLTFSkin::set_non_joints(PoolIntArray p_non_joints) {
	non_joints.resize(0);
	non_joints.append_array(p_non_joints);
}

PoolIntArray GLTFSkin::get_roots() {
	return roots;
}

void GLTFSkin::set_roots(PoolIntArray p_roots) {
	roots = p_roots;
}

int GLTFSkin::get_skeleton() {
	return skeleton;
}

void GLTFSkin::set_skeleton(int p_skeleton) {
	skeleton = p_skeleton;
}

Dictionary GLTFSkin::get_joint_i_to_bone_i() {
	return GLTFDocument::to_dict(joint_i_to_bone_i);
}

void GLTFSkin::set_joint_i_to_bone_i(Dictionary p_joint_i_to_bone_i) {
	GLTFDocument::set_from_dict(joint_i_to_bone_i, p_joint_i_to_bone_i);
}

Dictionary GLTFSkin::get_joint_i_to_name() {
	Dictionary ret;
	Map<int, String>::Element *elem = joint_i_to_name.front();
	while (elem) {
		ret[elem->key()] = String(elem->value());
		elem = elem->next();
	}
	return ret;
}

void GLTFSkin::set_joint_i_to_name(Dictionary p_joint_i_to_name) {
	joint_i_to_name = Map<int, String>();
	Array keys = p_joint_i_to_name.keys();
	for (int i = 0; i < keys.size(); i++) {
		joint_i_to_name[keys[i]] = p_joint_i_to_name[keys[i]];
	}
}

Ref<Skin> GLTFSkin::get_godot_skin() {
	return godot_skin;
}

void GLTFSkin::set_godot_skin(Ref<Skin> p_godot_skin) {
	godot_skin = p_godot_skin;
}
