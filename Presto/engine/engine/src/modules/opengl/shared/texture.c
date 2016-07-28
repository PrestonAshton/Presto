forceinline u8 GLTextureGetInternalFormat(u8 format, b8 srgb)
{
	switch (format)
	{
		/*case Greyscale:
			return GL_LUMINANCE;
		case GreyscaleAlpha:
			return GL_LUMINANCE;*/
	case RGB:
	{
		if (srgb)
			return GL_SRGB;
		else
			return GL_RGB;
	}	break;
	case RGBA:
	{
		if (srgb)
			return GL_SRGB_ALPHA;
		else
			return GL_RGBA;
	} break;
	}

	return 0;
}

void GLTextureAddFromFile(const a8* path)
{
	Hashmap_GLTextureSetByValue(&g_glTextures, hash(path), GLTextureLoadFromFile(path));
}

void GLTextureAddFromData(u64 name, Image image)
{
	Hashmap_GLTextureSetByValue(&g_glTextures, name, GLTextureLoadFromImage(image));
}

forceinline GLTexture GLTextureLoadFromFile(const a8* path)
{
	return GLTextureLoadFromImage(ImageLoadFromFile(path));
}

forceinline GLTexture GLTextureLoadFromImage(Image image)
{
	GLTexture texture = { 0 };
	glGenTextures(1, &(texture.object));

	glBindTexture(GL_TEXTURE_2D, texture.object);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GLTextureGetInternalFormat(image.format, true), image.width, image.height, 0, GLTextureGetInternalFormat(image.format, false), GL_UNSIGNED_BYTE, image.pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}