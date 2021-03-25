#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"

//#include "EventQueue.h"
//#include "Events.h"

int main(int, char*[]) 
{
	//Helheim::EventQueue<Helheim::AudioMessages> x;
	//UNREFERENCED_PARAMETER(x);

	Helheim::Minigin engine;
	engine.Run();
    return 0;
}