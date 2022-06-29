/*************************************************************************/
/*  gltf_skeleton.cpp                                                    */
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

#include "gltf_skeleton.h"

void GLTFSkeleton_::_register_methods() {
	register_method("_init", &GLTFSkeleton_::_init);
	register_method("get_godot_skeleton", &GLTFSkeleton_::get_godot_skeleton);
	register_method("get_bone_attachment_count", &GLTFSkeleton_::get_bone_attachment_count);
	register_method("get_bone_attachment", &GLTFSkeleton_::get_bone_attachment);

	register_property<GLTFSkeleton_, PoolIntArray>("joints", &GLTFSkeleton_::set_joints, &GLTFSkeleton_::get_joints, PoolIntArray()); // PoolVector<GLTFNodeIndex>
	register_property<GLTFSkeleton_, PoolIntArray>("roots", &GLTFSkeleton_::set_roots, &GLTFSkeleton_::get_roots, PoolIntArray()); // PoolVector<GLTFNodeIndex>
	register_property<GLTFSkeleton_, Array>("unique_names", &GLTFSkeleton_::set_unique_names, &GLTFSkeleton_::get_unique_names, Array()); // Set<String>
	register_property<GLTFSkeleton_, Dictionary>("godot_bone_node", &GLTFSkeleton_::set_godot_bone_node, &GLTFSkeleton_::get_godot_bone_node, Dictionary()); // Map<int32_t,
}

PoolIntArray GLTFSkeleton_::get_joints() {
	return joints;
}

void GLTFSkeleton_::set_joints(PoolIntArray p_joints) {
	joints = p_joints;
}

PoolIntArray GLTFSkeleton_::get_roots() {
	return roots;
}

void GLTFSkeleton_::set_roots(PoolIntArray p_roots) {
	roots = p_roots;
}

Skeleton *GLTFSkeleton_::get_godot_skeleton() {
	return godot_skeleton;
}

Array GLTFSkeleton_::get_unique_names() {
	return GLTFDocument_::to_array(unique_names);
}

void GLTFSkeleton_::set_unique_names(Array p_unique_names) {
	GLTFDocument_::set_from_array(unique_names, p_unique_names);
}

Dictionary GLTFSkeleton_::get_godot_bone_node() {
	return GLTFDocument_::to_dict(godot_bone_node);
}

void GLTFSkeleton_::set_godot_bone_node(Dictionary p_indict) {
	GLTFDocument_::set_from_dict(godot_bone_node, p_indict);
}

BoneAttachment *GLTFSkeleton_::get_bone_attachment(int idx) {
	ERR_FAIL_INDEX_V(idx, bone_attachments.size(), nullptr);
	return bone_attachments[idx];
}

int32_t GLTFSkeleton_::get_bone_attachment_count() {
	return bone_attachments.size();
}
