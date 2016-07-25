#ifndef QUEST_ENGINE_ENGINE_H
#define QUEST_ENGINE_ENGINE_H

#include <Quest/Common/BasicDefinitions.h>

#ifdef QUEST_EXPORTS

#include <Quest/Containers.h>
#include <Quest/Graphics/Image.h>
#include <Quest/Graphics/MeshData.h>
#include <Quest/Graphics/EntityWorld.h>

typedef struct
{
	vchar* name;
	vchar* pathname;
} GameInfo;

typedef struct
{
	struct
	{
		void(*AddFromFile)(const a8* path);
		void(*AddFromData)(const u64 name, const MeshData* data);
	} mesh;
	struct
	{
		void(*CreateFromFile)(const a8* path);
		void(*CreateFromData)(const u64 name, Image image);
	} texture;
	struct
	{
		void(*CreateFromFile)(const a8* path);
		void(*CreateFromData)(const u64 name, const u64 diffuseName, const u64 normalName, Colour32 colour, f32 specularExponent);
	} material;
	struct
	{
		void(*Create)(EntityId id, u64 meshName, u64 materialName);
	} renderSystem;
	void(*Init)();
	void(*Render)();
} Renderer;

DEFINE_CONTAINER_SET(Renderer);
Hashmap_Renderer g_renderers = { 0 };
Renderer g_renderer = { 0 };

typedef struct
{
	void(*Cache)(const a8* path);
	void(*Play)(u64 name);
	void(*Stop)(u64 name);
	void(*Pause)(u64 name);
	void(*Init)();
} SoundHandler;

DEFINE_CONTAINER_SET(SoundHandler);
Hashmap_SoundHandler g_soundHandlers = { 0 };
SoundHandler g_soundHandler = { 0 };

typedef struct
{
	// Render factory is a hashmap of string -> function ptrs for starting a renderer.
	GameInfo gameinfo;
	vchar* exePath;
	vchar* gamePath;
	//RenderEngine renderEngine;
	b8 isRunning;
} EngineGlobals;

EngineGlobals engineGlobals;

#endif

DEFINE_EXTERNAL_INTERFACE_FUNCTION(ClientUpdate, void, void);
DEFINE_INTERFACE_FUNCTION(StartEngine, b8, const vchar*, const vchar*);

void RenderStub(void);

void EngineUpdate(void);

void SetRenderer(const a8* args);


#endif
