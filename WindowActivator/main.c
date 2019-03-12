#include <Windows.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		printf("Window title is not set!\n");
		exit(-1);
	}

	char* sWindowTitle = NULL;
	int iSleepInterval = 500;

	if (argc == 2)
	{
		sWindowTitle = argv[1];
	}

	if (argc == 3)
	{
		sWindowTitle = argv[1];
		iSleepInterval = atoi(argv[2]);
	}

	HWND hGameWindow = FindWindow(NULL, sWindowTitle);
	if (hGameWindow != NULL)
	{
		printf("Found target window: %p\n", hGameWindow);

		printf("Start sending WM_ACTIVE message to the target window");
		while (TRUE)
		{
			LRESULT lRes = SendMessage(hGameWindow, WM_ACTIVATE, WA_CLICKACTIVE, NULL);
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