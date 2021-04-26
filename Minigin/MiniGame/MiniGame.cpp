
//#include <Minigin.h>
#include "QBertGame.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

int main()
{
    Helheim::QBertGame QBERTgame;
    QBERTgame.Initialize();
    QBERTgame.GameLoop();

    //Helheim::Minigin engine;
    //engine.Run();
    return 0;
}