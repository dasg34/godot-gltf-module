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

void GLTFState::_register_methods() {
	register_method("get_scene_node", &GLTFState::get_scene_node);

	register_property<GLTFState, Dictionary>("json", &GLTFState::set_json, &GLTFState::get_json, Dictionary()); // Dictionary
	register_property<GLTFState, int>("major_version", &GLTFState::set_major_version, &GLTFState::get_major_version, 0); // int
	register_property<GLTFState, int>("minor_version", &GLTFState::set_minor_version, &GLTFState::get_minor_version, 0); // int
	register_property<GLTFState, PoolByteArray>("glb_data", &GLTFState::set_glb_data, &GLTFState::get_glb_data, PoolByteArray()); // Vector<uint8_t>
	register_property<GLTFState, bool>("use_named_skin_binds", &GLTFState::set_use_named_skin_binds, &GLTFState::get_use_named_skin_binds, false); // bool
	register_property<GLTFState, Array>("nodes", &GLTFState::set_nodes, &GLTFState::get_nodes, Array()); // Vector<Ref<GLTFNode>>
	register_property<GLTFState, Array>("buffers", &GLTFState::set_buffers, &GLTFState::get_buffers, Array()); // Vector<Vector<uint8_t>
	register_property<GLTFState, Array>("buffer_views", &GLTFState::set_buffer_views, &GLTFState::get_buffer_views, Array()); // Vector<Ref<GLTFBufferView>>
	register_property<GLTFState, Array>("accessors", &GLTFState::set_accessors, &GLTFState::get_accessors, Array()); // Vector<Ref<GLTFAccessor>>
	register_property<GLTFState, Array>("meshes", &GLTFState::set_meshes, &GLTFState::get_meshes, Array()); // Vector<Ref<GLTFMesh>>
	register_property<GLTFState, Array>("materials", &GLTFState::set_materials, &GLTFState::get_materials, Array()); // Vector<Ref<Material>
	register_property<GLTFState, String>("scene_name", &GLTFState::set_scene_name, &GLTFState::get_scene_name, String()); // String
	register_property<GLTFState, Array>("root_nodes", &GLTFState::set_root_nodes, &GLTFState::get_root_nodes, Array()); // Vector<int>
	register_property<GLTFState, Array>("textures", &GLTFState::set_textures, &GLTFState::get_textures, Array()); // Vector<Ref<GLTFTexture>>
	register_property<GLTFState, Array>("images", &GLTFState::set_images, &GLTFState::get_images, Array()); // Vector<Ref<Texture>
	register_property<GLTFState, Array>("skins", &GLTFState::set_skins, &GLTFState::get_skins, Array()); // Vector<Ref<GLTFSkin>>
	register_property<GLTFState, Array>("cameras", &GLTFState::set_cameras, &GLTFState::get_cameras, Array()); // Vector<Ref<GLTFCamera>>
	register_property<GLTFState, Array>("lights", &GLTFState::set_lights, &GLTFState::get_lights, Array()); // Vector<Ref<GLTFLight>>
	register_property<GLTFState, Array>("unique_names", &GLTFState::set_unique_names, &GLTFState::get_unique_names, Array()); // Set<String>
	register_property<GLTFState, Array>("unique_animation_names", &GLTFState::set_unique_animation_names, &GLTFState::get_unique_animation_names, Array()); // Set<String>
	register_property<GLTFState, Array>("skeletons", &GLTFState::set_skeletons, &GLTFState::get_skeletons, Array()); // Vector<Ref<GLTFSkeleton>>
	register_property<GLTFState, Dictionary>("skeleton_to_node", &GLTFState::set_skeleton_to_node, &GLTFState::get_skeleton_to_node, Dictionary()); // Map<GLTFSkeletonIndex,
	register_property<GLTFState, Array>("animations", &GLTFState::set_animations, &GLTFState::get_animations, Array()); // Vector<Ref<GLTFAnimation>>
}

Dictionary GLTFState::get_json() {
	return json;
}

void GLTFState::set_json(Dictionary p_json) {
	json = p_json;
}

int GLTFState::get_major_version() {
	return major_version;
}

void GLTFState::set_major_version(int p_major_version) {
	major_version = p_major_version;
}

int GLTFState::get_minor_version() {
	return minor_version;
}

void GLTFState::set_minor_version(int p_minor_version) {
	minor_version = p_minor_version;
}

PoolByteArray GLTFState::get_glb_data() {
	return glb_data;
}

void GLTFState::set_glb_data(PoolByteArray p_glb_data) {
	glb_data = p_glb_data;
}

bool GLTFState::get_use_named_skin_binds() {
	return use_named_skin_binds;
}

void GLTFState::set_use_named_skin_binds(bool p_use_named_skin_binds) {
	use_named_skin_binds = p_use_named_skin_binds;
}

Array GLTFState::get_nodes() {
	return GLTFDocument::to_array(nodes);
}

void GLTFState::set_nodes(Array p_nodes) {
	GLTFDocument::set_from_array(nodes, p_nodes);
}

Array GLTFState::get_buffers() {
	return GLTFDocument::to_array(buffers);
}

void GLTFState::set_buffers(Array p_buffers) {
	GLTFDocument::set_from_array(buffers, p_buffers);
}

Array GLTFState::get_buffer_views() {
	return GLTFDocument::to_array(buffer_views);
}

void GLTFState::set_buffer_views(Array p_buffer_views) {
	GLTFDocument::set_from_array(buffer_views, p_buffer_views);
}

Array GLTFState::get_accessors() {
	return GLTFDocument::to_array(accessors);
}

void GLTFState::set_accessors(Array p_accessors) {
	GLTFDocument::set_from_array(accessors, p_accessors);
}

Array GLTFState::get_meshes() {
	return GLTFDocument::to_array(meshes);
}

void GLTFState::set_meshes(Array p_meshes) {
	GLTFDocument::set_from_array(meshes, p_meshes);
}

Array GLTFState::get_materials() {
	return GLTFDocument::to_array(materials);
}

void GLTFState::set_materials(Array p_materials) {
	GLTFDocument::set_from_array(materials, p_materials);
}

String GLTFState::get_scene_name() {
	return scene_name;
}

void GLTFState::set_scene_name(String p_scene_name) {
	scene_name = p_scene_name;
}

Array GLTFState::get_root_nodes() {
	return GLTFDocument::to_array(root_nodes);
}

void GLTFState::set_root_nodes(Array p_root_nodes) {
	GLTFDocument::set_from_array(root_nodes, p_root_nodes);
}

Array GLTFState::get_textures() {
	return GLTFDocument::to_array(textures);
}

void GLTFState::set_textures(Array p_textures) {
	GLTFDocument::set_from_array(textures, p_textures);
}

Array GLTFState::get_images() {
	return GLTFDocument::to_array(images);
}

void GLTFState::set_images(Array p_images) {
	GLTFDocument::set_from_array(images, p_images);
}

Array GLTFState::get_skins() {
	return GLTFDocument::to_array(skins);
}

void GLTFState::set_skins(Array p_skins) {
	GLTFDocument::set_from_array(skins, p_skins);
}

Array GLTFState::get_cameras() {
	return GLTFDocument::to_array(cameras);
}

void GLTFState::set_cameras(Array p_cameras) {
	GLTFDocument::set_from_array(cameras, p_cameras);
}

Array GLTFState::get_lights() {
	return GLTFDocument::to_array(lights);
}

void GLTFState::set_lights(Array p_lights) {
	GLTFDocument::set_from_array(lights, p_lights);
}

Array GLTFState::get_unique_names() {
	return GLTFDocument::to_array(unique_names);
}

void GLTFState::set_unique_names(Array p_unique_names) {
	GLTFDocument::set_from_array(unique_names, p_unique_names);
}

Array GLTFState::get_unique_animation_names() {
	return GLTFDocument::to_array(unique_animation_names);
}

void GLTFState::set_unique_animation_names(Array p_unique_animation_names) {
	GLTFDocument::set_from_array(unique_animation_names, p_unique_animation_names);
}

Array GLTFState::get_skeletons() {
	return GLTFDocument::to_array(skeletons);
}

void GLTFState::set_skeletons(Array p_skeletons) {
	GLTFDocument::set_from_array(skeletons, p_skeletons);
}

Dictionary GLTFState::get_skeleton_to_node() {
	return GLTFDocument::to_dict(skeleton_to_node);
}

void GLTFState::set_skeleton_to_node(Dictionary p_skeleton_to_node) {
	GLTFDocument::set_from_dict(skeleton_to_node, p_skeleton_to_node);
}

Array GLTFState::get_animations() {
	return GLTFDocument::to_array(animations);
}

void GLTFState::set_animations(Array p_animations) {
	GLTFDocument::set_from_array(animations, p_animations);
}

Node *GLTFState::get_scene_node(GLTFNodeIndex idx) {
	if (!scene_nodes.has(idx)) {
		return nullptr;
	}
	return scene_nodes[idx];
}

int GLTFState::get_animation_players_count(int idx) {
	return animation_players.size();
}

AnimationPlayer *GLTFState::get_animation_player(int idx) {
	ERR_FAIL_INDEX_V(idx, animation_players.size(), nullptr);
	return animation_players[idx];
}
