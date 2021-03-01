#include "MiniginPCH.h"
#include "Observer.h"

Helheim::Observer::Observer(const std::shared_ptr<dae::GameObject>& pMessageRecieverP1, const std::shared_ptr<dae::GameObject>& pMessageRecieverP2)
	: m_pMessageReceiverP1(pMessageRecieverP1)
	, m_pMessageReceiverP2(pMessageRecieverP2)
{}