#include "MiniGamePCH.h"
#include "HealthObserver.h"

#include <iostream>

Helheim::HealthObserver::HealthObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2)
	: Observer(pMessageRecieverP1, pMessageRecieverP2)
{}
void Helheim::HealthObserver::OnNotify(Helheim::GameObject*, const OBSERVER_EVENTS&) // pObject - event
{
	std::cout << "Dead \n";
}