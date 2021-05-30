#include "MiniGamePCH.h"

//#include <Minigin.h>
#include "DemoGame.h"
#include "QBertGame.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

int main()
{
    //Helheim::DemoGame DEMOgame;
    //DEMOgame.Initialize();
    //DEMOgame.GameLoop();

    Helheim::QBertGame QBERTgame;
    QBERTgame.Initialize();
    QBERTgame.GameLoop();

    //Helheim::Minigin engine;
    //engine.Run();

    return 0;
}