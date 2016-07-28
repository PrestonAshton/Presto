LARGE_INTEGER g_timeFrequency = { 0 };

LARGE_INTEGER TimeGetFrequency(void)
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}

void TimeInit(void)
{
	g_timeFrequency = TimeGetFrequency();
}

forceinline Time TimeNow(void)
{
	HANDLE currentThread = GetCurrentThread();
	DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	SetThreadAffinityMask(currentThread, previousMask);
	return TimeFromMicroseconds(1000000 * time.QuadPart / g_timeFrequency.QuadPart);
}

forceinline void TimeSleep(Time time)
{
	if (TimeAsMicroseconds(time) <= 0)
		return;

	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	timeBeginPeriod(tc.wPeriodMin);

	Sleep(TimeAsMilliseconds(time));

	timeBeginPeriod(tc.wPeriodMin);
}