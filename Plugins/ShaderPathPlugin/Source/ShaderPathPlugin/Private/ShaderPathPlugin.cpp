// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShaderPathPlugin.h"

#define LOCTEXT_NAMESPACE "FShaderPathPluginModule"

void FShaderPathPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FString ShaderDir=FPaths::Combine(FPaths::ProjectDir(), TEXT("/Shaders"));
	AddShaderSourceDirectoryMapping("/Project/Shaders", ShaderDir);
}

void FShaderPathPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShaderPathPluginModule, ShaderPathPlugin)