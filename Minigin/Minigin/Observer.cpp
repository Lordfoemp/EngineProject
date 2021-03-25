#include "MiniginPCH.h"
#include "Observer.h"

Helheim::Observer::Observer(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2)
	: m_pMessageReceiverP1(pMessageRecieverP1)
	, m_pMessageReceiverP2(pMessageRecieverP2)
{}