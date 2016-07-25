#ifndef QUEST_AUDIO_WAVE_H
#define QUEST_AUDIO_WAVE_H

#include <Quest/Common.h>
#include <Quest/Utility/Filesystem.h>
#include <Quest/Utility/Console.h>

typedef struct
{
	u32 chunkSize;
	u16 formatType;
	u16 channels;
	u32 sampleRate;
	u32 averageBytesPerSecond;
	u16 bytesPerSample;
	u16 bitsPerSample;
	u32 dataSize;
	u8* data;
#ifdef QUEST_ARCHITECTURE_x32
	u32 padding;
#endif
} SoundData;

#define InvalidSoundData (SoundData) { 0 }

forceinline SoundData LoadWaveFile(const a8* filename)
{
	a8 fileType[5];
	u32 size;
	a8 waveChunk[5];
	a8 format[5];
	a8 dataHeader[5];

	SoundData data = { 0 };

	a8* ourFile = (a8*)ReadEntireFile(filename);

	if (!ourFile)
		return data;

	a8* originalPtr = ourFile;

	copyMemory(ourFile, &fileType[0], 4); ourFile += 4;
	copyMemory(ourFile, &size, 4); ourFile += 4;
	copyMemory(ourFile, &waveChunk[0], 4); ourFile += 4;
	copyMemory(ourFile, &format[0], 4); ourFile += 4;

	fileType[4] = '\0';
	waveChunk[4] = '\0';
	format[4] = '\0';

	if (strcmp(fileType, "RIFF"))
		WARN(V("Invalid wave file: is not RIFF type!"));

	if (strcmp(waveChunk, "WAVE"))
		WARN(V("Invalid wave file: is not WAVE type!"));

	if (strcmp(format, "fmt "))
		WARN(V("Invalid wave file: is not FMT type!"));

	copyMemory(ourFile, &(data.chunkSize), 4); ourFile += 4;
	copyMemory(ourFile, &(data.formatType), 2); ourFile += 2;
	copyMemory(ourFile, &(data.channels), 2); ourFile += 2;
	copyMemory(ourFile, &(data.sampleRate), 4); ourFile += 4;
	copyMemory(ourFile, &(data.averageBytesPerSecond), 4); ourFile += 4;
	copyMemory(ourFile, &(data.bytesPerSample), 2); ourFile += 2;
	copyMemory(ourFile, &(data.bitsPerSample), 2); ourFile += 2;

	copyMemory(ourFile, &dataHeader[0], 4); ourFile += 4;
	dataHeader[4] = '\0';

	if (strcmp(dataHeader, "data"))
		WARN(V("Invalid wave file: Cannot find data header!"));

	copyMemory(ourFile, &(data.dataSize), 4); ourFile += 4;

	data.data = (u8*)spawn(data.dataSize);

	copyMemory(ourFile, data.data, data.dataSize);

	murder(originalPtr);

	return data;
}

#endif
