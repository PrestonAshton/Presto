Image LoadBMP(const a8* path)
{
	Image image = { 0 };

	u8* header = conjure(54);
	u32 dataPos;
	u32 imageSize;

	u8* fileData = ReadEntireFile(path);
	copyMemory(fileData, header, 54);

	dataPos = *(u32*)&(header[0x0A]);
	imageSize = *(u32*)&(header[0x22]);
	image.width = *(u32*)&(header[0x12]);
	image.height = *(u32*)&(header[0x16]);
	image.format = RGB;

	if (imageSize == 0)
		imageSize = image.width * image.height * RGB;

	if (dataPos == 0)
		dataPos = 54;

	image.pixels = spawn(imageSize);

	copyMemory(fileData + dataPos, image.pixels, imageSize);

	/*u8 tempRGB = 0;
	for (u32 i = 0; i < imageSize; i += RGB)
	{
		tempRGB = image.pixels[i];
		image.pixels[i] = image.pixels[i + 2];
		image.pixels[i + 2] = tempRGB;
	}*/

	//ImageFlipVertically(&image);

	murder(fileData);

	return image;
}

Image ImageLoadFromFile(const a8* path)
{
	// Multiple types in future.
	// Our own file type! :o
	// BMP for now.
	// TODO: Multiple file types!
	return LoadBMP(path);
}

void ImageFlipVertically(Image* image)
{
	// Pitch is width * bitdepth;
	usize pitch = (usize)image->width * (usize)image->format;
	u32 halfRows = image->height / 2;

	u8* rowBuffer = conjure(pitch); // no need to * sizeof as its u8 (bytes)

	for (u32 i = 0; i < halfRows; i++)
	{
		u8* row = image->pixels + (i * image->width) * (usize)image->format;
		u8* oppositeRow = image->pixels + ((image->height - i - 1) * image->width) * (usize)image->format;

		copyMemory(row, rowBuffer, pitch);
		copyMemory(oppositeRow, row, pitch);
		copyMemory(rowBuffer, oppositeRow, pitch);
	}
}