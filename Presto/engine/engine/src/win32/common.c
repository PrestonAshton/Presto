#define MsgLength 512

void ForceAssert(const vchar* assertionText, const vchar* customMessage, const char* file, int lineNumber, b8* ignore)
{
	vchar assertMessage[MsgLength] = V("");
	if (customMessage != NULL)
		Vsprintf(assertMessage, MsgLength, V("Assert! %S:%d -> %s; %s"), file, lineNumber, assertionText, customMessage);
	else
		Vsprintf(assertMessage, MsgLength, V("Assert! %S:%d -> %s"), file, lineNumber, assertionText);

	WARN(assertMessage);

	if (*ignore == true)
	{
		vchar outputMessage[MsgLength] = V("");
		Vsprintf(outputMessage, MsgLength, V("%s\n\n%S:%d"), assertionText, file, lineNumber);
		if (customMessage != NULL)
			Vsprintf(outputMessage, MsgLength, V("%s\n\nNotes:\n%s"), outputMessage, customMessage);
		Vsprintf(outputMessage, MsgLength, V("%s\n\nPress TRY AGAIN to break."), outputMessage);
		Vsprintf(outputMessage, MsgLength, V("%s\nPress CANCEL to ignore this assert."), outputMessage);

		i8 choice = MessageBox(NULL, outputMessage, V("Assertion Failed!"), MB_CANCELTRYCONTINUE | MB_ICONEXCLAMATION);
		if (choice == IDCANCEL)
			*ignore = true;
		if (choice == IDTRYAGAIN)
			DebugBreak();
	}
}
