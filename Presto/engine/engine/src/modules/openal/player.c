#ifdef QUEST_ARCHITECTURE_X64
#pragma comment(lib, "Win64/OpenAL32.lib")
#else
#pragma comment(lib, "Win32/OpenAL32.lib")
#endif

typedef struct
{
	u16 buffer;
	u16 source;
} SoundInfo;

typedef struct
{
	ALCdevice* device;
	ALCcontext* context;
} OpenALGlobals;

OpenALGlobals openALGlobals;

void InitialiseOpenAL();
SoundInfo LoadSound(SoundData* soundData);
void SoundPlay(SoundInfo info, Vector3* position, f32 volume);
void SoundStop(SoundInfo info);
void SoundVolume(SoundInfo info, f32 volume);
void SoundPosition(SoundInfo info, Vector3* position);


#include <Quest/Containers.h>

DEFINE_HASHMAP(SoundInfo);

Hashmap_SoundInfo AudioResources;

forceinline void LoadAudioFromFile(const vchar* filename)
{
	Vector3 stuff2 = { 0, 0, 0 };
	SoundData data = LoadWaveFile(filename);

	Hashmap_SoundInfoSetByValue(&AudioResources, hash(filename), LoadSound(&data));
	murder(data.data);
}

forceinline SoundInfo GetAudio(u64 key)
{
	return Hashmap_SoundInfoGetValue(&AudioResources, key);
}

static b8 soundPossible = false;

INITIALIZER(InitialiseOpenAL);

void InitialiseOpenAL()
{
	openALGlobals.device = alcOpenDevice(NULL);
	if (!openALGlobals.device)
	{
		MSG("No audio outputs! No sound will be played.");
		return;
	}

	openALGlobals.context = alcCreateContext(openALGlobals.device, NULL);
	alcMakeContextCurrent(openALGlobals.context);

	InitialiseSoundHandlerFactory();
	SoundHandler openAL;
	openAL.AddFromFile = &LoadAudioFromFile;
	Hashmap_RendererSetByPtr(&g_renderers, hash("opengl"), &glRenderer);
}

SoundInfo LoadSound(SoundData* soundData)
{
	ALuint format = 0;
	SoundInfo sound = { 0 };

	alGenBuffers(1, &(sound.buffer));
	alGenSources(1, &(sound.source));

	if (soundData->bitsPerSample == 8)
	{
		if (soundData->channels == 1)
			format = AL_FORMAT_MONO8;
		if (soundData->channels == 2)
			format = AL_FORMAT_STEREO8;
	}

	if (soundData->bitsPerSample == 16)
	{
		if (soundData->channels == 1)
			format = AL_FORMAT_MONO16;
		if (soundData->channels == 2)
			format = AL_FORMAT_STEREO16;
	}

	alBufferData(sound.buffer, format, soundData->data, soundData->dataSize, soundData->sampleRate);
	alSourcei(sound.source, AL_BUFFER, sound.buffer);
	alSourcef(sound.source, AL_PITCH, 1.0f);
	alSourcef(sound.source, AL_GAIN, 1.0f);

	return sound;
}

forceinline void SoundStop(SoundInfo info)
{
	alSourceStop(info.source);
}

forceinline void SoundPosition(SoundInfo info, Vector3* position)
{
	// TODO: GET PLAYER POSITION HERE!!!!
	ALfloat listenerPosition[] = { 0.0f, 0.0f, 0.0f };
	ALfloat orientation[] = { 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f };

	alListenerfv(AL_POSITION, listenerPosition);
	alListenerfv(AL_VELOCITY, listenerPosition);
	alListenerfv(AL_ORIENTATION, orientation);

	alSourcefv(info.source, AL_POSITION, position);
	alSourcefv(info.source, AL_VELOCITY, position);
	alSourcei(info.source, AL_LOOPING, false);
}

forceinline void SoundVolume(SoundInfo info, f32 volume)
{
	alSourcef(info.source, AL_GAIN, volume);
}

forceinline void SoundPlay(SoundInfo info, Vector3* position, f32 volume)
{
	// TODO: GET PLAYER POSITION HERE!!!!
	SoundPosition(info, position);
	SoundVolume(info, volume);

	alSourcePlay(info.source);
}