/*************************************************************************/
/*  editor_scene_importer_gltf.h                                         */
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

#ifndef EDITOR_SCENE_IMPORTER_GLTF_H
#define EDITOR_SCENE_IMPORTER_GLTF_H

#include <PoolArrays.hpp>
#include <EditorSceneImporter.hpp>
#include <CSGShape.hpp>
#include <GridMap.hpp>
#include <MeshInstance.hpp>
#include <MultiMeshInstance.hpp>
#include <Skeleton.hpp>
#include <Spatial.hpp>
#include <Animation.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
#include <SurfaceTool.hpp>

#include "gltf_document.h"
#include "gltf_state.h"
#include "list.h"
using namespace godot;

class EditorSceneImporterGLTF : public EditorSceneImporter {
	GODOT_CLASS(EditorSceneImporterGLTF, EditorSceneImporter);

public:
	static void _register_methods();
	void _init() {}

public:
	int64_t _get_import_flags() const;
	Array _get_extensions() const;
	Node *_import_scene(String p_path, uint32_t p_flags,
			int p_bake_fps);
	Ref<Animation> _import_animation(String p_path,
			uint32_t p_flags, int p_bake_fps);
};

class PackedSceneGLTF : public PackedScene {
	GODOT_CLASS(PackedSceneGLTF, PackedScene);

public:
	static void _register_methods();
	void _init() {}

public:
	void save_scene(Node *p_node, const String &p_path, const String &p_src_path,
			uint32_t p_flags, int p_bake_fps,
			PoolStringArray *r_missing_deps, Error *r_err = NULL);
	void _build_parent_hierachy(Ref<GLTFState> state);
	int32_t export_gltf(Node *p_root, String p_path, int32_t p_flags = 0,
			real_t p_bake_fps = 1000.0f);
	Node *import_scene(const String &p_path, const PoolByteArray bytes, uint32_t p_flags,
			int p_bake_fps,
			PoolStringArray *r_missing_deps,
			Error *r_err,
			Ref<GLTFState> r_state);
	Node *import_gltf_scene(String p_path, const PoolByteArray bytes, uint32_t p_flags, float p_bake_fps, Ref<GLTFState> r_state = Ref<GLTFState>());
	void pack_gltf(String p_path, int32_t p_flags = 0,
			real_t p_bake_fps = 1000.0f, Ref<GLTFState> r_state = Ref<GLTFState>());
};
#endif // EDITOR_SCENE_IMPORTER_GLTF_H
