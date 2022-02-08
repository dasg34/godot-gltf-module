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

void GLTFSkeleton::_register_methods() {
	register_method("_init", &GLTFSkeleton::_init);
	register_method("get_godot_skeleton", &GLTFSkeleton::get_godot_skeleton);
	register_method("get_bone_attachment_count", &GLTFSkeleton::get_bone_attachment_count);
	register_method("get_bone_attachment", &GLTFSkeleton::get_bone_attachment);

	register_property<GLTFSkeleton, PoolIntArray>("joints", &GLTFSkeleton::set_joints, &GLTFSkeleton::get_joints, PoolIntArray()); // PoolVector<GLTFNodeIndex>
	register_property<GLTFSkeleton, PoolIntArray>("roots", &GLTFSkeleton::set_roots, &GLTFSkeleton::get_roots, PoolIntArray()); // PoolVector<GLTFNodeIndex>
	register_property<GLTFSkeleton, Array>("unique_names", &GLTFSkeleton::set_unique_names, &GLTFSkeleton::get_unique_names, Array()); // Set<String>
	register_property<GLTFSkeleton, Dictionary>("godot_bone_node", &GLTFSkeleton::set_godot_bone_node, &GLTFSkeleton::get_godot_bone_node, Dictionary()); // Map<int32_t,
}

PoolIntArray GLTFSkeleton::get_joints() {
	return joints;
}

void GLTFSkeleton::set_joints(PoolIntArray p_joints) {
	joints = p_joints;
}

PoolIntArray GLTFSkeleton::get_roots() {
	return roots;
}

void GLTFSkeleton::set_roots(PoolIntArray p_roots) {
	roots = p_roots;
}

Skeleton *GLTFSkeleton::get_godot_skeleton() {
	return godot_skeleton;
}

Array GLTFSkeleton::get_unique_names() {
	return GLTFDocument::to_array(unique_names);
}

void GLTFSkeleton::set_unique_names(Array p_unique_names) {
	GLTFDocument::set_from_array(unique_names, p_unique_names);
}

Dictionary GLTFSkeleton::get_godot_bone_node() {
	return GLTFDocument::to_dict(godot_bone_node);
}

void GLTFSkeleton::set_godot_bone_node(Dictionary p_indict) {
	GLTFDocument::set_from_dict(godot_bone_node, p_indict);
}

BoneAttachment *GLTFSkeleton::get_bone_attachment(int idx) {
	ERR_FAIL_INDEX_V(idx, bone_attachments.size(), nullptr);
	return bone_attachments[idx];
}

int32_t GLTFSkeleton::get_bone_attachment_count() {
	return bone_attachments.size();
}
