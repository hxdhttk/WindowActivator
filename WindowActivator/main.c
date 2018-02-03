#include <Windows.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		printf("Window title is not set!\n");
		exit(-1);
	}

	char* sWindowTitle = argv[1];
	HWND hGameWindow = FindWindow(NULL, sWindowTitle);
	if (hGameWindow != NULL)
	{
		printf("Found target window: %p\n", hGameWindow);
		while (TRUE)
		{
			printf("Sending WM_ACTIVE message to the target window.\n");
			LRESULT lRes = SendMessage(hGameWindow, WM_ACTIVATE, WA_CLICKACTIVE, NULL);
			printf("SendMessage result: %lld\n", lRes);
			if (lRes != 0)
			{
				printf("SendMessage result: %lld\n", lRes);
				printf("Maybe we encountered an error, exiting.\n");
				exit(-1);
			}
			Sleep(500);
		}
	}

	printf("Cannot find target window, exiting...");
	exit(-1);
}
