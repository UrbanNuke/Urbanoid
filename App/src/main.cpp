#include <Windows.h>
#include "components/window.h"

static const unsigned int SCREEN_WIDTH = 960;
static const unsigned int SCREEN_HEIGHT = 720;

int main() {
	// comment for debug
	FreeConsole();
	
	Window window("Urbanoid", SCREEN_WIDTH, SCREEN_HEIGHT);
	    
	window.launchGameLoop();
	
    return 0;
}
