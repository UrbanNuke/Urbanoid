#include <Windows.h>
#include "components/window.h"

static const unsigned int SCREEN_WIDTH = 960;
static const unsigned int SCREEN_HEIGHT = 720;

#ifdef _DEBUG
#define URBANOID_CONSOLE
#else
#define URBANOID_CONSOLE FreeConsole()
#endif

int main() {
	URBANOID_CONSOLE;
	
	Window window("Urbanoid", SCREEN_WIDTH, SCREEN_HEIGHT);
	    
	window.launchGameLoop();
	
    return 0;
}
