/*************************************************************************/
/*  editor_scene_importer_gltf.cpp                                       */
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

#include "gltf_state.h"
#include "editor_scene_importer_gltf.h"

#include <EditorSceneImporter.hpp>
#include <PackedScene.hpp>
#include <Spatial.hpp>
#include <AnimationPlayer.hpp>


const static int IMPORT_USE_NAMED_SKIN_BINDS = 4096; // missing in enum



void EditorSceneImporterGLTF::_register_methods() {
	register_method("_init", &EditorSceneImporterGLTF::_init);
	register_method("_get_import_flags", &EditorSceneImporterGLTF::_get_import_flags);
	register_method("_get_extensions", &EditorSceneImporterGLTF::_get_extensions);
	register_method("_import_scene", &EditorSceneImporterGLTF::_import_scene);
	register_method("_import_animation", &EditorSceneImporterGLTF::_import_animation);
}

int64_t EditorSceneImporterGLTF::_get_import_flags() const {
	return EditorSceneImporter::IMPORT_SCENE | EditorSceneImporter::IMPORT_ANIMATION;
}

Array EditorSceneImporterGLTF::_get_extensions() const {
	Array r_extensions;
	r_extensions.push_back(String("gltf"));
	r_extensions.push_back(String("glb"));
	return r_extensions;
}

Node *EditorSceneImporterGLTF::_import_scene(String p_path,
		uint32_t p_flags, int p_bake_fps) {
	Ref<PackedSceneGLTF> importer = class_by_name("PackedSceneGLTF")->new_();
	Ref<GLTFState> null_gltfref;
	return importer->import_gltf_scene(p_path, p_flags, p_bake_fps, null_gltfref);
}

Ref<Animation> EditorSceneImporterGLTF::_import_animation(String p_path,
		uint32_t p_flags,
		int p_bake_fps) {
	return Ref<Animation>();
}

void PackedSceneGLTF::_register_methods() {
	register_method("_init", &PackedSceneGLTF::_init);
	register_method("export_gltf", &PackedSceneGLTF::export_gltf);
	register_method("pack_gltf", &PackedSceneGLTF::pack_gltf);
	register_method("import_gltf_scene", &PackedSceneGLTF::import_gltf_scene);
}

Node *PackedSceneGLTF::import_gltf_scene(String p_path, uint32_t p_flags, float p_bake_fps, Ref<GLTFState> r_state) {
	Error err = Error::FAILED;
	PoolStringArray deps;
	return import_scene(p_path, p_flags, p_bake_fps, &deps, &err, r_state);
}

Node *PackedSceneGLTF::import_scene(const String &p_path, uint32_t p_flags,
		int p_bake_fps,
		PoolStringArray *r_missing_deps,
		Error *r_err,
		Ref<GLTFState> r_state) {
	if (r_state == Ref<GLTFState>()) {
		r_state = class_by_name("GLTFState")->new_();
	}
	r_state->use_named_skin_binds =
			p_flags & IMPORT_USE_NAMED_SKIN_BINDS;

	Ref<GLTFDocument> gltf_document;
	gltf_document = class_by_name("GLTFDocument")->new_();
	Error err = gltf_document->parse(r_state, p_path);
	*r_err = err;
	ERR_FAIL_COND_V(err != Error::OK, nullptr);

	Spatial *root = Spatial::_new();
	for (int32_t root_i = 0; root_i < r_state->root_nodes.size(); root_i++) {
		gltf_document->_generate_scene_node(r_state, root, root, r_state->root_nodes[root_i]);
	}
	gltf_document->_process_mesh_instances(r_state, root);
	if (r_state->animations.size()) {
		AnimationPlayer *ap = AnimationPlayer::_new();
		root->add_child(ap);
		ap->set_owner(root);
		for (int i = 0; i < r_state->animations.size(); i++) {
			gltf_document->_import_animation(r_state, ap, i, p_bake_fps);
		}
	}

	return root;
}

void PackedSceneGLTF::pack_gltf(String p_path, int32_t p_flags,
		real_t p_bake_fps, Ref<GLTFState> r_state) {
	Error err = Error::FAILED;
	PoolStringArray deps;
	Node *root = import_scene(p_path, p_flags, p_bake_fps, &deps, &err, r_state);
	ERR_FAIL_COND(err != Error::OK);
	pack(root);
}

void PackedSceneGLTF::save_scene(Node *p_node, const String &p_path,
		const String &p_src_path, uint32_t p_flags,
		int p_bake_fps, PoolStringArray *r_missing_deps,
		Error *r_err) {
	Error err = Error::FAILED;
	if (r_err) {
		*r_err = err;
	}
	Ref<GLTFDocument> gltf_document;
	gltf_document = class_by_name("GLTFDocument")->new_();
	Ref<GLTFState> state;
	state = class_by_name("GLTFState")->new_();
	err = gltf_document->serialize(state, p_node, p_path);
	if (r_err) {
		*r_err = err;
	}
}

void PackedSceneGLTF::_build_parent_hierachy(Ref<GLTFState> state) {
	// build the hierarchy
	for (GLTFNodeIndex node_i = 0; node_i < state->nodes.size(); node_i++) {
		for (int j = 0; j < state->nodes[node_i]->children.size(); j++) {
			GLTFNodeIndex child_i = state->nodes[node_i]->children[j];
			ERR_FAIL_INDEX(child_i, state->nodes.size());
			if (state->nodes.write[child_i]->parent != -1) {
				continue;
			}
			state->nodes.write[child_i]->parent = node_i;
		}
	}
}

int32_t PackedSceneGLTF::export_gltf(Node *p_root, String p_path,
		int32_t p_flags,
		real_t p_bake_fps) {
	ERR_FAIL_COND_V(!p_root, (int32_t)Error::FAILED);
	PoolStringArray deps;
	Error err;
	String path = p_path;
	int32_t flags = p_flags;
	real_t baked_fps = p_bake_fps;
	Ref<PackedSceneGLTF> exporter;
	exporter = class_by_name("PackedSceneGLTF")->new_();
	exporter->save_scene(p_root, path, "", flags, baked_fps, &deps, &err);
	if (err != Error::OK) {
		return (int32_t)err;
	}
	return (int32_t)Error::OK;
}
