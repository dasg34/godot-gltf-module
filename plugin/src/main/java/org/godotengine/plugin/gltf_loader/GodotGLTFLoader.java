package org.godotengine.plugin.gltf_loader;

import android.app.Activity;
import android.util.Log;
import android.view.View;

import androidx.annotation.NonNull;

import org.godotengine.godot.Godot;
import org.godotengine.godot.plugin.GodotPlugin;
import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Set;

public class GodotGLTFLoader extends GodotPlugin {

	public GodotGLTFLoader(Godot godot) {
		super(godot);
	}

    static {
        System.loadLibrary("godot_gltf_loader");
    }

	@Override
	public View onMainCreate(Activity activity) {

		return null;
	}

	@NonNull
	@Override
	public String getPluginName() {
		return "GodotGLTFLoader";
	}

/*
    @NonNull
    @Override
    public List<String> getPluginMethods() {
        return new ArrayList<>(Collections.singletonList("ARCoreInitialize"));
    }
*/
    @NotNull
    @Override
    protected Set<String> getPluginGDNativeLibrariesPaths() {
        return Collections.singleton("addons/godot_gltf_loader/godot_gltf_loader.gdnlib");
    }
}
