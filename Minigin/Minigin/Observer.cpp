#include "MiniginPCH.h"
#include "Observer.h"
#include "Component.h"

Helheim::Observer::Observer()
	: m_pMessageReceiverP1(nullptr)
	, m_pMessageReceiverP2(nullptr)
	, m_pOwningComponent(nullptr)
{}
Helheim::Observer::Observer(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2)
	: m_pMessageReceiverP1(pMessageRecieverP1)
	, m_pMessageReceiverP2(pMessageRecieverP2)
	, m_pOwningComponent(nullptr)
{}