#ifndef QUEST_GRAPHICS_GLRENDERPATH_H
#define QUEST_GRAPHICS_GLRENDERPATH_H

#include <Quest/Graphics/RenderSystem.h>
#include <Quest/Modules/OpenGL/RenderComponent.h>

DEFINE_RENDER_SYSTEM(GLRenderSystem, GLRenderComponent, g_glRenderSystem);

void GLRenderSystemInterfaceCreate(EntityId id, u64 meshName, u64 materialName);

#endif
