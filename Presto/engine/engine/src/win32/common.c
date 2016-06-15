void ForceAssert(const vchar* assertionText, const vchar* customMessage, const char* file, int lineNumber)
{
	vchar outputMessage[256] = V("");
	Vsprintf(outputMessage + Vstrlen(outputMessage), 256 - Vstrlen(outputMessage), V("%s\n\n%S:%d"), assertionText, file, lineNumber);
	if (customMessage != NULL)
		Vsprintf(outputMessage + Vstrlen(outputMessage), 256 - Vstrlen(outputMessage), V("\n\nNotes:\n%s"), customMessage);
	Vsprintf(outputMessage + Vstrlen(outputMessage), 256 - Vstrlen(outputMessage), V("\n\nPress TRY AGAIN to break"));

	OutputDebugString(outputMessage);
	i8 choice = MessageBox(NULL, outputMessage, V("Assertion Failed!"), MB_CANCELTRYCONTINUE | MB_ICONEXCLAMATION );
	if (choice == IDCANCEL)
		exit(-1);
	if (choice == IDTRYAGAIN)
		DebugBreak();
}
