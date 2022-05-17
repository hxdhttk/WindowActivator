#include <Windows.h>
#include <stdio.h>

int wmain(int argc, wchar_t** argv)
{
	if (argc == 1)
	{
		printf("Window title is not set!\n");
		exit(-1);
	}

	wchar_t* sWindowTitle = NULL;
	int iSleepInterval = 500;

	if (argc == 2)
	{
		sWindowTitle = argv[1];
	}

	if (argc == 3)
	{
		sWindowTitle = argv[1];
		iSleepInterval = _wtoi(argv[2]);
	}

	HWND hGameWindow = FindWindowW(NULL, sWindowTitle);
	if (hGameWindow != NULL)
	{
		printf("Found target window: %p\n", hGameWindow);

		printf("Start sending WM_ACTIVE message to the target window");
		while (TRUE)
		{
			LRESULT lRes = SendMessageW(hGameWindow, WM_ACTIVATE, WA_CLICKACTIVE, NULL);
			if (lRes != 0)
			{
				printf("SendMessage result: %lld\n", lRes);
				printf("Maybe we encountered an error, exiting.\n");
				exit(-1);
			}

			Sleep(iSleepInterval);
		}
	}

	printf("Cannot find target window, exiting...");
	exit(-1);
}