/*************************************************************************/
/*  gltf_state.cpp                                                       */
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

#include <Array.hpp>
#include "gltf_state.h"

void GLTFState_::_register_methods() {
	register_method("_init", &GLTFState_::_init);
	register_method("get_scene_node", &GLTFState_::get_scene_node);
	register_method("get_animation_players_count", &GLTFState_::get_animation_players_count);
	register_method("get_animation_player", &GLTFState_::get_animation_player);

	register_property<GLTFState_, Dictionary>("json", &GLTFState_::set_json, &GLTFState_::get_json, Dictionary()); // Dictionary
	register_property<GLTFState_, int>("major_version", &GLTFState_::set_major_version, &GLTFState_::get_major_version, 0); // int
	register_property<GLTFState_, int>("minor_version", &GLTFState_::set_minor_version, &GLTFState_::get_minor_version, 0); // int
	register_property<GLTFState_, PoolByteArray>("glb_data", &GLTFState_::set_glb_data, &GLTFState_::get_glb_data, PoolByteArray()); // Vector<uint8_t>
	register_property<GLTFState_, bool>("use_named_skin_binds", &GLTFState_::set_use_named_skin_binds, &GLTFState_::get_use_named_skin_binds, false); // bool
	register_property<GLTFState_, Array>("nodes", &GLTFState_::set_nodes, &GLTFState_::get_nodes, Array()); // Vector<Ref<GLTFNode_>>
	register_property<GLTFState_, Array>("buffers", &GLTFState_::set_buffers, &GLTFState_::get_buffers, Array()); // Vector<Vector<uint8_t>
	register_property<GLTFState_, Array>("buffer_views", &GLTFState_::set_buffer_views, &GLTFState_::get_buffer_views, Array()); // Vector<Ref<GLTFBufferView_>>
	register_property<GLTFState_, Array>("accessors", &GLTFState_::set_accessors, &GLTFState_::get_accessors, Array()); // Vector<Ref<GLTFAccessor_>>
	register_property<GLTFState_, Array>("meshes", &GLTFState_::set_meshes, &GLTFState_::get_meshes, Array()); // Vector<Ref<GLTFMesh_>>
	register_property<GLTFState_, Array>("materials", &GLTFState_::set_materials, &GLTFState_::get_materials, Array()); // Vector<Ref<Material>
	register_property<GLTFState_, String>("scene_name", &GLTFState_::set_scene_name, &GLTFState_::get_scene_name, String()); // String
	register_property<GLTFState_, Array>("root_nodes", &GLTFState_::set_root_nodes, &GLTFState_::get_root_nodes, Array()); // Vector<int>
	register_property<GLTFState_, Array>("textures", &GLTFState_::set_textures, &GLTFState_::get_textures, Array()); // Vector<Ref<GLTFTexture_>>
	register_property<GLTFState_, Array>("images", &GLTFState_::set_images, &GLTFState_::get_images, Array()); // Vector<Ref<Texture>
	register_property<GLTFState_, Array>("skins", &GLTFState_::set_skins, &GLTFState_::get_skins, Array()); // Vector<Ref<GLTFSkin_>>
	register_property<GLTFState_, Array>("cameras", &GLTFState_::set_cameras, &GLTFState_::get_cameras, Array()); // Vector<Ref<GLTFCamera_>>
	register_property<GLTFState_, Array>("lights", &GLTFState_::set_lights, &GLTFState_::get_lights, Array()); // Vector<Ref<GLTFLight_>>
	register_property<GLTFState_, Array>("unique_names", &GLTFState_::set_unique_names, &GLTFState_::get_unique_names, Array()); // Set<String>
	register_property<GLTFState_, Array>("unique_animation_names", &GLTFState_::set_unique_animation_names, &GLTFState_::get_unique_animation_names, Array()); // Set<String>
	register_property<GLTFState_, Array>("skeletons", &GLTFState_::set_skeletons, &GLTFState_::get_skeletons, Array()); // Vector<Ref<GLTFSkeleton_>>
	register_property<GLTFState_, Dictionary>("skeleton_to_node", &GLTFState_::set_skeleton_to_node, &GLTFState_::get_skeleton_to_node, Dictionary()); // Map<GLTFSkeletonIndex,
	register_property<GLTFState_, Array>("animations", &GLTFState_::set_animations, &GLTFState_::get_animations, Array()); // Vector<Ref<GLTFAnimation_>>
}

Dictionary GLTFState_::get_json() {
	return json;
}

void GLTFState_::set_json(Dictionary p_json) {
	json = p_json;
}

int GLTFState_::get_major_version() {
	return major_version;
}

void GLTFState_::set_major_version(int p_major_version) {
	major_version = p_major_version;
}

int GLTFState_::get_minor_version() {
	return minor_version;
}

void GLTFState_::set_minor_version(int p_minor_version) {
	minor_version = p_minor_version;
}

PoolByteArray GLTFState_::get_glb_data() {
	return glb_data;
}

void GLTFState_::set_glb_data(PoolByteArray p_glb_data) {
	glb_data = p_glb_data;
}

bool GLTFState_::get_use_named_skin_binds() {
	return use_named_skin_binds;
}

void GLTFState_::set_use_named_skin_binds(bool p_use_named_skin_binds) {
	use_named_skin_binds = p_use_named_skin_binds;
}

Array GLTFState_::get_nodes() {
	return GLTFDocument_::to_array(nodes);
}

void GLTFState_::set_nodes(Array p_nodes) {
	GLTFDocument_::set_from_array(nodes, p_nodes);
}

Array GLTFState_::get_buffers() {
	return GLTFDocument_::to_array(buffers);
}

void GLTFState_::set_buffers(Array p_buffers) {
	GLTFDocument_::set_from_array(buffers, p_buffers);
}

Array GLTFState_::get_buffer_views() {
	return GLTFDocument_::to_array(buffer_views);
}

void GLTFState_::set_buffer_views(Array p_buffer_views) {
	GLTFDocument_::set_from_array(buffer_views, p_buffer_views);
}

Array GLTFState_::get_accessors() {
	return GLTFDocument_::to_array(accessors);
}

void GLTFState_::set_accessors(Array p_accessors) {
	GLTFDocument_::set_from_array(accessors, p_accessors);
}

Array GLTFState_::get_meshes() {
	return GLTFDocument_::to_array(meshes);
}

void GLTFState_::set_meshes(Array p_meshes) {
	GLTFDocument_::set_from_array(meshes, p_meshes);
}

Array GLTFState_::get_materials() {
	return GLTFDocument_::to_array(materials);
}

void GLTFState_::set_materials(Array p_materials) {
	GLTFDocument_::set_from_array(materials, p_materials);
}

String GLTFState_::get_scene_name() {
	return scene_name;
}

void GLTFState_::set_scene_name(String p_scene_name) {
	scene_name = p_scene_name;
}

Array GLTFState_::get_root_nodes() {
	return GLTFDocument_::to_array(root_nodes);
}

void GLTFState_::set_root_nodes(Array p_root_nodes) {
	GLTFDocument_::set_from_array(root_nodes, p_root_nodes);
}

Array GLTFState_::get_textures() {
	return GLTFDocument_::to_array(textures);
}

void GLTFState_::set_textures(Array p_textures) {
	GLTFDocument_::set_from_array(textures, p_textures);
}

Array GLTFState_::get_images() {
	return GLTFDocument_::to_array(images);
}

void GLTFState_::set_images(Array p_images) {
	GLTFDocument_::set_from_array(images, p_images);
}

Array GLTFState_::get_skins() {
	return GLTFDocument_::to_array(skins);
}

void GLTFState_::set_skins(Array p_skins) {
	GLTFDocument_::set_from_array(skins, p_skins);
}

Array GLTFState_::get_cameras() {
	return GLTFDocument_::to_array(cameras);
}

void GLTFState_::set_cameras(Array p_cameras) {
	GLTFDocument_::set_from_array(cameras, p_cameras);
}

Array GLTFState_::get_lights() {
	return GLTFDocument_::to_array(lights);
}

void GLTFState_::set_lights(Array p_lights) {
	GLTFDocument_::set_from_array(lights, p_lights);
}

Array GLTFState_::get_unique_names() {
	return GLTFDocument_::to_array(unique_names);
}

void GLTFState_::set_unique_names(Array p_unique_names) {
	GLTFDocument_::set_from_array(unique_names, p_unique_names);
}

Array GLTFState_::get_unique_animation_names() {
	return GLTFDocument_::to_array(unique_animation_names);
}

void GLTFState_::set_unique_animation_names(Array p_unique_animation_names) {
	GLTFDocument_::set_from_array(unique_animation_names, p_unique_animation_names);
}

Array GLTFState_::get_skeletons() {
	return GLTFDocument_::to_array(skeletons);
}

void GLTFState_::set_skeletons(Array p_skeletons) {
	GLTFDocument_::set_from_array(skeletons, p_skeletons);
}

Dictionary GLTFState_::get_skeleton_to_node() {
	return GLTFDocument_::to_dict(skeleton_to_node);
}

void GLTFState_::set_skeleton_to_node(Dictionary p_skeleton_to_node) {
	GLTFDocument_::set_from_dict(skeleton_to_node, p_skeleton_to_node);
}

Array GLTFState_::get_animations() {
	return GLTFDocument_::to_array(animations);
}

void GLTFState_::set_animations(Array p_animations) {
	GLTFDocument_::set_from_array(animations, p_animations);
}

Node *GLTFState_::get_scene_node(GLTFNodeIndex idx) {
	if (!scene_nodes.has(idx)) {
		return nullptr;
	}
	return scene_nodes[idx];
}

int GLTFState_::get_animation_players_count(int idx) {
	return animation_players.size();
}

AnimationPlayer *GLTFState_::get_animation_player(int idx) {
	ERR_FAIL_INDEX_V(idx, animation_players.size(), nullptr);
	return animation_players[idx];
}
