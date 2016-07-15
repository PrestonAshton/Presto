#ifndef QUEST_GRAPHICS_IMAGE_H
#define QUEST_GRAPHICS_IMAGE_H

#include <Quest/Common.h>
#include <Quest/Graphics/Colour.h>

typedef enum
{
	None = 0,
	Greyscale = 1,
	GreyscaleAlpha = 2,
	RGB = 3,
	RGBA = 4,

	NumFormats
} ImageFormat;

typedef struct
{
	u8* pixels; // usize ptr (64 or 32)
	//<-- 64 bits | 8 bytes -- 32 bits | 4 bytes -->

	u16 width;
	u16 height;
	u8 format;
	u8 padding_1[3];
	//<-- 64 bits | 8 bytes -->
#ifdef QUEST_ARCHITECTURE_X32
	u32 padding_2;
	// Align to 128 bits due to size of pointer on architecture
#endif
} Image;

// <-- Image | 128 bits | 16 bytes -->
// Test this.
STATIC_ASSERT(sizeof(Image) == 16, Size_Of_Image);

Image ImageLoadFromFile(const vchar* filename);

forceinline Colour24* ImageGetPixel(Image* image, u16 x, u16 y)
{
	return (Colour24*)(image->pixels + ((usize)(y * image->width + x) * (usize)(image->format)));
}
forceinline void ImageSetPixel(Image* image, u16 x, u16 y, Colour24 pixel)
{
	*ImageGetPixel(image, x, y) = pixel;
}

void ImageFlipVertically(Image* image);

#endif
