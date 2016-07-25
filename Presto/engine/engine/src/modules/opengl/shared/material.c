extern Hashmap_GLMaterial g_glMaterials = { 0 };

void GLMaterialAddFromData(const u64 name, const u64 diffuseName, const u64 normalName, Colour32 colour, f32 specularExponent)
{
	GLMaterial material;
	material.diffuseMap = Hashmap_GLTextureGetValue(&g_glTextures, diffuseName);
	material.normalMap = Hashmap_GLTextureGetValue(&g_glTextures, normalName);
	material.diffuseColour = colour;
	material.specularExponent = specularExponent;

	Hashmap_GLMaterialSetByPtr(&g_glMaterials, name, &material);
}