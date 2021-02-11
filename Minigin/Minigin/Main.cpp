#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"

int main(int, char*[]) 
{
	int* test = new int();
	UNREFERENCED_PARAMETER(test);

	// Detect mem leaks
	#if defined(DEBUG) | defined(_DEBUG)
		int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		flag |= _CRTDBG_LEAK_CHECK_DF;
		_CrtSetDbgFlag(flag);
	#endif

	dae::Minigin engine;
	engine.Run();	

    return 0;
}