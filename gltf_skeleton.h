/*************************************************************************/
/*  gltf_skeleton.h                                                      */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
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

#ifndef GLTF_SKELETON_H
#define GLTF_SKELETON_H

#include "core/resource.h"
#include "core/variant/variant_conversion.h"
#include "gltf_document.h"

class GLTFSkeleton : public Resource {
	GDCLASS(GLTFSkeleton, Resource);

protected:
	static void _bind_methods();

public:
	// The *synthesized* skeletons joints
	Vector<GLTFNodeIndex> joints;

	// The roots of the skeleton. If there are multiple, each root must have the
	// same parent (ie roots are siblings)
	Vector<GLTFNodeIndex> roots;

	// The created Skeleton for the scene
	Skeleton *godot_skeleton;

	// Set of unique bone names for the skeleton
	Set<String> unique_names;

	Map<int32_t, GLTFNodeIndex> godot_bone_node;

	Vector<BoneAttachment *> bone_attachments;


	Vector<GLTFNodeIndex> get_joints() {
		return this->joints;
	}
	void set_joints(Vector<GLTFNodeIndex> p_joints) {
		this->joints = p_joints;
	}


	Vector<GLTFNodeIndex> get_roots() {
		return this->roots;
	}
	void set_roots(Vector<GLTFNodeIndex> p_roots) {
		this->roots = p_roots;
	}


	Skeleton *get_godot_skeleton() {
	 	return this->godot_skeleton;
	}


	Array get_unique_names() {
		return VariantConversion::to_array(this->unique_names);
	}
	void set_unique_names(Array p_unique_names) {
		VariantConversion::set_from_array(this->unique_names, p_unique_names);
	}


	Dictionary get_godot_bone_node() {
		return VariantConversion::to_dict(this->godot_bone_node);
	}
	void set_godot_bone_node(Dictionary p_indict) {
		VariantConversion::set_from_dict(this->godot_bone_node, p_indict);
	}


	int get_bone_attachment_count() {
		return this->bone_attachments.size();
	}
	BoneAttachment * get_bone_attachment(int idx) {
		ERR_FAIL_INDEX_V(idx, this->bone_attachments.size(), nullptr);
		return this->bone_attachments[idx];
	}


	GLTFSkeleton() :
			godot_skeleton(nullptr) {}
};
#endif
