/*************************************************************************/
/*  register_types.cpp                                                   */
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

#include <Godot.hpp>

#include "editor_scene_importer_gltf.h"
#include "gltf_accessor.h"
#include "gltf_animation.h"
#include "gltf_buffer_view.h"
#include "gltf_camera.h"
#include "gltf_document.h"
#include "gltf_light.h"
#include "gltf_mesh.h"
#include "gltf_node.h"
#include "gltf_skeleton.h"
#include "gltf_skin.h"
#include "gltf_spec_gloss.h"
#include "gltf_state.h"
#include "gltf_texture.h"

extern "C" void GDN_EXPORT godot_gltf_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gltf_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_gltf_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

	register_tool_class<EditorSceneImporterGLTF_>();
	register_tool_class<GLTFMesh_>();
	register_tool_class<GLTFSpecGloss_>();
	register_tool_class<GLTFNode_>();
	register_tool_class<GLTFAnimation_>();
	register_tool_class<GLTFBufferView_>();
	register_tool_class<GLTFAccessor_>();
	register_tool_class<GLTFTexture_>();
	register_tool_class<GLTFSkeleton_>();
	register_tool_class<GLTFSkin_>();
	register_tool_class<GLTFCamera_>();
	register_tool_class<GLTFLight_>();
	register_tool_class<GLTFState_>();
	register_tool_class<GLTFDocument_>();
	register_tool_class<PackedSceneGLTF_>();

	// Ref<EditorSceneImporterGLTF_> import_gltf;
	// import_gltf.instance();
	// ResourceImporterScene::get_singleton()->add_importer(import_gltf);
}