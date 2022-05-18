#include <Windows.h>
#include <stdio.h>

#define OPKIND_ACT 0
#define OPKIND_TOP 1

int wmain(int argc, wchar_t** argv)
{
	if (argc == 2)
	{
		printf("Window title is not set!\n");
		exit(-1);
	}

	wchar_t* sOp = NULL;
	wchar_t* sWindowTitle = NULL;
	int iSleepInterval = 500;

	if (argc == 3)
	{
		sOp = argv[1];
		sWindowTitle = argv[2];
	}

	if (argc >= 4)
	{
		sOp = argv[1];
		sWindowTitle = argv[2];
		iSleepInterval = _wtoi(argv[3]);
	}

	int opKind = OPKIND_ACT;
	if (sOp != NULL) {
		if (lstrcmpiW(sOp, L"act") == 0)
		{
			printf("Start sending WM_ACTIVE message to the target window\n");
			opKind = OPKIND_ACT;
		}
		else if (lstrcmpiW(sOp, L"top") == 0)
		{
			printf("Start bring the target window to top\n");
			opKind = OPKIND_TOP;
		}
		else
		{
			wprintf(L"Unknown OpKind: %s\n", sOp);
			exit(-1);
		}
	}
	else {
		printf("OpKind is NULL\n");
		exit(-1);
	}

	HWND hGameWindow = FindWindowW(NULL, sWindowTitle);
	if (hGameWindow != NULL)
	{
		printf("Found target window: %p\n", hGameWindow);
		LRESULT lRes = 0;
		BOOL succ = FALSE;
		while (TRUE)
		{
			if (opKind == OPKIND_ACT)
			{
				lRes = SendMessageW(hGameWindow, WM_ACTIVATE, WA_CLICKACTIVE, NULL);
				succ = lRes == 0;
			}
			else if (opKind == OPKIND_TOP)
			{
				succ = BringWindowToTop(hGameWindow);
			}

			if (!succ)
			{
				printf("Maybe we encountered an error, exiting...\n");
				exit(-1);
			}

			Sleep(iSleepInterval);
		}
	}

	printf("Cannot find target window, exiting...\n");
	exit(-1);
}