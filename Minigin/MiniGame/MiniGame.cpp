#include "MiniGamePCH.h"

#include "DemoGame.h"
#include "QBertGame.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

//#define Demo
#define QBERT

int main()
{
    #ifdef Demo
    Helheim::DemoGame DEMOgame;
    DEMOgame.Initialize();
    DEMOgame.GameLoop();
    #endif // Demo
    
    #ifdef QBERT
    Helheim::QBertGame QBERTgame;
    QBERTgame.Initialize();
    QBERTgame.GameLoop();
    #endif // QBERT

    return 0;
}