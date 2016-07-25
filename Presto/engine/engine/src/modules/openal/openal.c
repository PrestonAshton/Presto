#define OPENAL_WINDOWS_HANDLED
#ifndef OPENAL_WINDOWS_HANDLED
#define AL_NO_PROTOTYPES

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

LPALCCREATECONTEXT DalcCreateContext;
LPALCMAKECONTEXTCURRENT DalcMakeContextCurrent;
LPALCPROCESSCONTEXT DalcProcessContext;
LPALCSUSPENDCONTEXT DalcSuspendContext;
LPALCDESTROYCONTEXT DalcDestroyContext;
LPALCGETCURRENTCONTEXT DalcGetCurrentContext;
LPALCGETCONTEXTSDEVICE DalcGetContextsDevice;
LPALCOPENDEVICE DalcOpenDevice;
LPALCCLOSEDEVICE DalcCloseDevice;
LPALCGETERROR DalcGetError;
LPALCISEXTENSIONPRESENT DalcIsExtensionPresent;
LPALCGETPROCADDRESS DalcGetProcAddress;
LPALCGETENUMVALUE DalcGetEnumValue;
LPALCGETSTRING DalcGetString;
LPALCGETINTEGERV DalcGetIntegerv;
LPALCCAPTUREOPENDEVICE DalcCaptureOpenDevice;
LPALCCAPTURECLOSEDEVICE DalcCaptureCloseDevice;
LPALCCAPTURESTART DalcCaptureStart;
LPALCCAPTURESTOP DalcCaptureStop;
LPALCCAPTURESAMPLES DalcCaptureSamples;

#define alcCreateContext DalcCreateContext
#define alcMakeContextCurrent DalcMakeContextCurrent
#define alcProcessContext DalcProcessContext
#define alcSuspendContext DalcSuspendContext
#define alcDestroyContext DalcDestroyContext
#define alcGetCurrentContext DalcGetCurrentContext
#define alcGetContextsDevice DalcGetContextsDevice
#define alcOpenDevice DalcOpenDevice
#define alcCloseDevice DalcCloseDevice
#define alcGetError DalcGetError
#define alcIsExtensionPresent DalcIsExtensionPresent
#define alcGetProcAddress DalcGetProcAddress
#define alcGetEnumValue DalcGetEnumValue
#define alcGetString DalcGetString
#define alcGetIntegerv DalcGetIntegerv
#define alcCaptureOpenDevice DalcCaptureOpenDevice
#define alcCaptureCloseDevice DalcCaptureCloseDevice
#define alcCaptureStart DalcCaptureStart
#define alcCaptureStop DalcCaptureStop
#define alcCaptureSamples DalcCaptureSamples

LPALENABLE DalEnable;
LPALDISABLE DalDisable;
LPALISENABLED DalIsEnabled;
LPALGETSTRING DalGetString;
LPALGETBOOLEANV DalGetBooleanv;
LPALGETINTEGERV DalGetIntegerv;
LPALGETFLOATV DalGetFloatv;
LPALGETDOUBLEV DalGetDoublev;
LPALGETBOOLEAN DalGetBoolean;
LPALGETINTEGER DalGetInteger;
LPALGETFLOAT DalGetFloat;
LPALGETDOUBLE DalGetDouble;
LPALGETERROR DalGetError;
LPALISEXTENSIONPRESENT DalIsExtensionPresent;
LPALGETPROCADDRESS DalGetProcAddress;
LPALGETENUMVALUE DalGetEnumValue;
LPALLISTENERF DalListenerf;
LPALLISTENER3F DalListener3f;
LPALLISTENERFV DalListenerfv;
LPALLISTENERI DalListeneri;
LPALLISTENER3F DalListener3i;
LPALLISTENERIV DalListeneriv;
LPALGETLISTENERF DalGetListenerf;
LPALGETLISTENER3F DalGetListener3f;
LPALGETLISTENERFV DalGetListenerfv;
LPALGETLISTENERI DalGetListeneri;
LPALGETLISTENER3I DalGetListener3i;
LPALGETLISTENERIV DalGetListeneriv;
LPALGENSOURCES DalGenSources;
LPALDELETESOURCES DalDeleteSources;
LPALISSOURCE DalIsSource;
LPALSOURCEF DalSourcef;
LPALSOURCE3F DalSource3f;
LPALSOURCEFV DalSourcefv;
LPALSOURCEI DalSourcei;
LPALSOURCE3I DalSource3i;
LPALSOURCEIV DalSourceiv;
LPALGETSOURCEF DalGetSourcef;
LPALGETSOURCE3F DalGetSource3f;
LPALGETSOURCEFV DalGetSourcefv;
LPALGETSOURCEI DalGetSourcei;
LPALGETSOURCE3I DalGetSource3i;
LPALGETSOURCEIV DalGetSourceiv;
LPALSOURCEPLAYV DalSourcePlayv;
LPALSOURCESTOPV DalSourceStopv;
LPALSOURCEREWINDV DalSourceRewindv;
LPALSOURCEPAUSEV DalSourcePausev;
LPALSOURCEPLAY DalSourcePlay;
LPALSOURCESTOP DalSourceStop;
LPALSOURCEREWIND DalSourceRewind;
LPALSOURCEPAUSE DalSourcePause;
LPALSOURCEQUEUEBUFFERS DalSourceQueueBuffers;
LPALSOURCEUNQUEUEBUFFERS DalSourceUnqueueBuffers;
LPALGENBUFFERS DalGenBuffers;
LPALDELETEBUFFERS DalDeleteBuffers;
LPALISBUFFER DalIsBuffer;
LPALBUFFERDATA DalBufferData;
LPALBUFFERF DalBufferf;
LPALBUFFER3F DalBuffer3f;
LPALBUFFERFV DalBufferfv;
LPALBUFFERI DalBufferi;
LPALBUFFER3I DalBuffer3i;
LPALBUFFERIV DalBufferiv;
LPALGETBUFFERF DalGetBufferf;
LPALGETBUFFER3F DalGetBuffer3f;
LPALGETBUFFERFV DalGetBufferfv;
LPALGETBUFFERI DalGetBufferi;
LPALGETBUFFER3I DalGetBuffer3i;
LPALGETBUFFERIV DalGetBufferiv;
LPALDOPPLERFACTOR DalDopplerFactor;
LPALDOPPLERVELOCITY DalDopplerVelocity;
LPALSPEEDOFSOUND DalSpeedOfSound;
LPALDISTANCEMODEL DalDistanceModel;

#define alEnable DalEnable
#define alDisable DalDisable
#define alIsEnabled DalIsEnabled
#define alGetString DalGetString
#define alGetBooleanv DalGetBooleanv
#define alGetIntegerv DalGetIntegerv
#define alGetFloatv DalGetFloatv
#define alGetDoublev DalGetDoublev
#define alGetBoolean DalGetBoolean
#define alGetInteger DalGetInteger
#define alGetFloat DalGetFloat
#define alGetDouble DalGetDouble
#define alGetError DalGetError
#define alIsExtensionPresent DalIsExtensionPresent
#define alGetProcAddress DalGetProcAddress
#define alGetEnumValue DalGetEnumValue
#define alListenerf DalListenerf
#define alListener3f DalListener3f
#define alListenerfv DalListenerfv
#define alListeneri DalListeneri
#define alListener3i DalListener3i
#define alListeneriv DalListeneriv
#define alGetListenerf DalGetListenerf
#define alGetListener3f DalGetListener3f
#define alGetListenerfv DalGetListenerfv
#define alGetListeneri DalGetListeneri
#define alGetListener3i DalGetListener3i
#define alGetListeneriv DalGetListeneriv
#define alGenSources DalGenSources
#define alDeleteSources DalDeleteSources
#define alIsSource DalIsSource
#define alSourcef DalSourcef
#define alSource3f DalSource3f
#define alSourcefv DalSourcefv
#define alSourcei DalSourcei
#define alSource3i DalSource3i
#define alSourceiv DalSourceiv
#define alGetSourcef DalGetSourcef
#define alGetSource3f DalGetSource3f
#define alGetSourcefv DalGetSourcefv
#define alGetSourcei DalGetSourcei
#define alGetSource3i DalGetSource3i
#define alGetSourceiv DalGetSourceiv
#define alSourcePlayv DalSourcePlayv
#define alSourceStopv DalSourceStopv
#define alSourceRewindv DalSourceRewindv
#define alSourcePausev DalSourcePausev
#define alSourcePlay DalSourcePlay
#define alSourceStop DalSourceStop
#define alSourceRewind DalSourceRewind
#define alSourcePause DalSourcePause
#define alSourceQueueBuffers DalSourceQueueBuffers
#define alSourceUnqueueBuffers DalSourceUnqueueBuffers
#define alGenBuffers DalGenBuffers
#define alDeleteBuffers DalDeleteBuffers
#define alIsBuffer DalIsBuffer
#define alBufferData DalBufferData
#define alBufferf DalBufferf
#define alBuffer3f DalBuffer3f
#define alBufferfv DalBufferfv
#define alBufferi DalBufferi
#define alBuffer3i DalBuffer3i
#define alBufferiv DalBufferiv
#define alGetBufferf DalGetBufferf
#define alGetBuffer3f DalGetBuffer3f
#define alGetBufferfv DalGetBufferfv
#define alGetBufferi DalGetBufferi
#define alGetBuffer3i DalGetBuffer3i
#define alGetBufferiv DalGetBufferiv
#define alDopplerFactor DalDopplerFactor
#define alDopplerVelocity DalDopplerVelocity
#define alSpeedOfSound DalSpeedOfSound
#define alDistanceModel DalDistanceModel

void InitialiseOpenALFunctions(HANDLE openALDLL)
{
	alcGetProcAddress = GetProcAddress(openALDLL, "alcGetProcAddress");

	alcCreateContext = GetProcAddress(openALDLL, "alcCreateContext");
	alcMakeContextCurrent = GetProcAddress(openALDLL, "alcMakeContextCurrent");
	alcProcessContext = GetProcAddress(openALDLL, "alcProcessContext");
	alcSuspendContext = GetProcAddress(openALDLL, "alcSuspendContext");
	alcDestroyContext = GetProcAddress(openALDLL, "alcDestroyContext");
	alcGetCurrentContext = GetProcAddress(openALDLL, "alcGetCurrentContext");
	alcGetContextsDevice = GetProcAddress(openALDLL, "alcGetContextsDevice");
	alcOpenDevice = GetProcAddress(openALDLL, "alcOpenDevice");
	alcCloseDevice = GetProcAddress(openALDLL, "alcCloseDevice");
	alcGetError = GetProcAddress(openALDLL, "alcGetError");
	alcIsExtensionPresent = GetProcAddress(openALDLL, "alcIsExtensionPresent");
	alcGetEnumValue = GetProcAddress(openALDLL, "alcGetEnumValue");
	alcGetString = GetProcAddress(openALDLL, "alcGetString");
	alcGetIntegerv = GetProcAddress(openALDLL, "alcGetIntegerv");
	alcCaptureOpenDevice = GetProcAddress(openALDLL, "alcCaptureOpenDevice");
	alcCaptureCloseDevice = GetProcAddress(openALDLL, "alcCaptureCloseDevice");
	alcCaptureStart = GetProcAddress(openALDLL, "alcCaptureStart");
	alcCaptureStop = GetProcAddress(openALDLL, "alcCaptureStop");
	alcCaptureSamples = GetProcAddress(openALDLL, "alcCaptureSamples");

	alGetProcAddress = GetProcAddress("alGetProcAddress");
	alEnable = alGetProcAddress("alEnable");
	alDisable = alGetProcAddress("alDisable");
	alIsEnabled = alGetProcAddress("alIsEnabled");
	alGetString = alGetProcAddress("alGetString");
	alGetBooleanv = alGetProcAddress("alGetBooleanv");
	alGetIntegerv = alGetProcAddress("alGetIntegerv");
	alGetFloatv = alGetProcAddress("alGetFloatv");
	alGetDoublev = alGetProcAddress("alGetDoublev");
	alGetBoolean = alGetProcAddress("alGetBoolean");
	alGetInteger = alGetProcAddress("alGetInteger");
	alGetFloat = alGetProcAddress("alGetFloat");
	alGetDouble = alGetProcAddress("alGetDouble");
	alGetError = alGetProcAddress("alGetError");
	alIsExtensionPresent = alGetProcAddress("alIsExtensionPresent");
	alGetEnumValue = alGetProcAddress("alGetEnumValue");
	alListenerf = alGetProcAddress("alListenerf");
	alListener3f = alGetProcAddress("alListener3f");
	alListenerfv = alGetProcAddress("alListenerfv");
	alListeneri = alGetProcAddress("alListeneri");
	alListener3i = alGetProcAddress("alListener3i");
	alListeneriv = alGetProcAddress("alListeneriv");
	alGetListenerf = alGetProcAddress("alGetListenerf");
	alGetListener3f = alGetProcAddress("alGetListener3f");
	alGetListenerfv = alGetProcAddress("alGetListenerfv");
	alGetListeneri = alGetProcAddress("alGetListeneri");
	alGetListener3i = alGetProcAddress("alGetListener3i");
	alGetListeneriv = alGetProcAddress("alGetListeneriv");
	alGenSources = alGetProcAddress("alGenSources");
	alDeleteSources = alGetProcAddress("alDeleteSources");
	alIsSource = alGetProcAddress("alIsSource");
	alSourcef = alGetProcAddress("alSourcef");
	alSource3f = alGetProcAddress("alSource3f");
	alSourcefv = alGetProcAddress("alSourcefv");
	alSourcei = alGetProcAddress("alSourcei");
	alSource3i = alGetProcAddress("alSource3i");
	alSourceiv = alGetProcAddress("alSourceiv");
	alGetSourcef = alGetProcAddress("alGetSourcef");
	alGetSource3f = alGetProcAddress("alGetSource3f");
	alGetSourcefv = alGetProcAddress("alGetSourcefv");
	alGetSourcei = alGetProcAddress("alGetSourcei");
	alGetSource3i = alGetProcAddress("alGetSource3i");
	alGetSourceiv = alGetProcAddress("alGetSourceiv");
	alSourcePlayv = alGetProcAddress("alSourcePlayv");
	alSourceStopv = alGetProcAddress("alSourceStopv");
	alSourceRewindv = alGetProcAddress("alSourceRewindv");
	alSourcePausev = alGetProcAddress("alSourcePausev");
	alSourcePlay = alGetProcAddress("alSourcePlay");
	alSourceStop = alGetProcAddress("alSourceStop");
	alSourceRewind = alGetProcAddress("alSourceRewind");
	alSourcePause = alGetProcAddress("alSourcePause");
	alSourceQueueBuffers = alGetProcAddress("alSourceQueueBuffers");
	alSourceUnqueueBuffers = alGetProcAddress("alSourceUnqueueBuffers");
	alGenBuffers = alGetProcAddress("alGenBuffers");
	alDeleteBuffers = alGetProcAddress("alDeleteBuffers");
	alIsBuffer = alGetProcAddress("alIsBuffer");
	alBufferData = alGetProcAddress("alBufferData");
	alBufferf = alGetProcAddress("alBufferf");
	alBuffer3f = alGetProcAddress("alBuffer3f");
	alBufferfv = alGetProcAddress("alBufferfv");
	alBufferi = alGetProcAddress("alBufferi");
	alBuffer3i = alGetProcAddress("alBuffer3i");
	alBufferiv = alGetProcAddress("alBufferiv");
	alGetBufferf = alGetProcAddress("alGetBufferf");
	alGetBuffer3f = alGetProcAddress("alGetBuffer3f");
	alGetBufferfv = alGetProcAddress("alGetBufferfv");
	alGetBufferi = alGetProcAddress("alGetBufferi");
	alGetBuffer3i = alGetProcAddress("alGetBuffer3i");
	alGetBufferiv = alGetProcAddress("alGetBufferiv");
	alDopplerFactor = alGetProcAddress("alDopplerFactor");
	alDopplerVelocity = alGetProcAddress("alDopplerVelocity");
	alSpeedOfSound = alGetProcAddress("alSpeedOfSound");
	alDistanceModel = alGetProcAddress("alDistanceModel");
}
#else
#ifdef QUEST_ARCHITECTURE_X64
#pragma comment(lib, "Win64/OpenAL32.lib")
#else
#pragma comment(lib, "Win32/OpenAL32.lib")
#endif

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#endif

typedef struct
{
	u16 buffer;
	u16 source;
} SoundInfo;

DEFINE_HASHMAP(SoundInfo);
Hashmap_SoundInfo audioResources;

SoundInfo ALErrorSound;

ALCdevice* device;
ALCcontext* context;

forceinline SoundInfo ALLoadSound(SoundData* soundData)
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

void ALLoadAudioFromFile(const a8* filename)
{
	SoundData data = LoadWaveFile(filename);
	Hashmap_SoundInfoSetByValue(&audioResources, hash(filename), ALLoadSound(&data));
	murder(data.data);
}

void ALSoundPlay(u64 hash)
{
	SoundInfo info = Hashmap_SoundInfoGetValueDefault(&audioResources, hash, ALErrorSound);
	alSourcePlay(info.source);
}

void ALSoundStop(u64 hash)
{
	SoundInfo info = Hashmap_SoundInfoGetValueDefault(&audioResources, hash, ALErrorSound);
	alSourceStop(info.source);
}

void ALSoundPause(u64 hash)
{
	SoundInfo info = Hashmap_SoundInfoGetValueDefault(&audioResources, hash, ALErrorSound);
	alSourceStop(info.source);
}

ALfloat ZeroOrientation[] = { 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f };

void InitialiseOpenAL(void)
{
#ifndef OPENAL_WINDOWS_HANDLED
	HANDLE openALDLL = LoadLibrary(V("OpenAL32.dll"));
	if (openALDLL == NULL)
		return;

	InitialiseOpenALFunctions(openALDLL);
#endif

	device = alcOpenDevice(NULL);
	if (!device)
	{
		MSG(V("No OpenAL compatible devices!"));
		return;
	}

	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);

	alListenerfv(AL_POSITION, &Vector3Zero);
	alListenerfv(AL_VELOCITY, &Vector3Zero);
	alListenerfv(AL_ORIENTATION, ZeroOrientation);

	SoundData data = LoadWaveFile("sound/error.wav");
	ALErrorSound = ALLoadSound(&data);
	Hashmap_SoundInfoSetByValue(&audioResources, hash("error"), ALErrorSound);
	murder(data.data);
}

INITIALIZER(InitialiseOpenALInHandlers);

void InitialiseOpenALInHandlers(void)
{
	InitialiseSoundHandlerFactory();

	SoundHandler openALHandler;
	openALHandler.Cache = &ALLoadAudioFromFile;
	openALHandler.Init = &InitialiseOpenAL;
	openALHandler.Play = &ALSoundPlay;
	openALHandler.Stop = &ALSoundStop;
	openALHandler.Pause = &ALSoundPause;

	Hashmap_SoundHandlerSetByPtr(&g_soundHandlers, hash("openal"), &openALHandler);
}
