#include "MiniGamePCH.h"
#include "CubeObserver.h"

#include <iostream>

#include "Cube.h"

Helheim::CubeObserver::CubeObserver(Cube* pOwnerCube, Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2)
	: Observer(pMessageRecieverP1, pMessageRecieverP2)
	, m_pOwnerCube(pOwnerCube)
{}
void Helheim::CubeObserver::OnNotify(Helheim::GameObject*, const OBSERVER_EVENTS& ) // pObject - event
{
	std::cout << "Extra score jeej \n";

	
}