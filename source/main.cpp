#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include <iostream>


int main(int argc, char* argv[]) {
	
	bool alreadyRun = false;
	char disabled[] = "sdmc:/luma/0004013000002F02.ips";
	char enabled[] = "sdmc:/luma/sysmodules/0004013000002F02.ips";
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();
		
		
		//check whether script executed yet & try enabling patch
		if (!alreadyRun && rename(disabled, enabled) == 0) {
			alreadyRun = true;
			std::cout << "Patch successfully enabled\n";
		}
		//now try disabling
		else if (!alreadyRun && rename(enabled, disabled) == 0) {
			alreadyRun = true;
			std::cout << "Patch successfully disabled\n";
		}
		//error msg if neither works
		else if (!alreadyRun) {
			perror("Error moving file");
			alreadyRun = true;
		}
	 //pause until user input
	 getchar();
	
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
	}
	
	gfxExit();
	return 0;
}
