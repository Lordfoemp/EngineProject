#include "MiniGamePCH.h"
#include "QBERTComponent.h"

#include <GameObject.h>
#include "JumpComponent.h"
#include <TextureComponent.h>
#include "ColliderComponent.h"
#include <TransformComponent.h>

Helheim::QBERTComponent::QBERTComponent(Helheim::GameObject* pParentObject)
						: Component(pParentObject, false)
{}

void Helheim::QBERTComponent::Initialize(Scene* )	//pParentScene
{}
void Helheim::QBERTComponent::PostInitialize(Scene*)	//pParentScene
{
	m_pTextureComponent = m_pParentObject->GetComponent<TextureComponent>();
	m_pJumpComponent = m_pParentObject->GetComponent<JumpComponent>();

	m_pTextureComponent->UpdateRenderSettings(16, 16, int(StartPositionsTexture::LEFT_DOWN));
}
void Helheim::QBERTComponent::Update(const float )	//elapsedSec
{

}
void Helheim::QBERTComponent::FixedUpdate(const float )	//timeEachUpdate
{

}

void Helheim::QBERTComponent::SetJumpingSprite(const bool jumpLeft, const bool jumpUp)
{
	// Jump Left
	bool jumpLeftDown{ jumpLeft && !jumpUp };
	if (jumpLeftDown)
		m_pTextureComponent->UpdateRenderSettings(16, 16, int(StartPositionsTexture::LEFT_DOWN));
	bool jumpLeftUp{ jumpLeft && jumpUp };
	if (jumpLeftUp)
		m_pTextureComponent->UpdateRenderSettings(16, 16, int(StartPositionsTexture::LEFT_UP));
	// Jump Right
	bool jumpRightDown{ !jumpLeft && !jumpUp };
	if (jumpRightDown)
		m_pTextureComponent->UpdateRenderSettings(16, 16, int(StartPositionsTexture::RIGHT_DOWN));
	bool jumpRightUp{ !jumpLeft && jumpUp };
	if (jumpRightUp)
		m_pTextureComponent->UpdateRenderSettings(16, 16, int(StartPositionsTexture::RIGHT_UP));
}

void Helheim::QBERTComponent::Reset(const glm::vec3& cubeStartPosition)
{
	m_pParentObject->GetComponent<ColliderComponent>()->Reset();
	m_pParentObject->GetComponent<JumpComponent>()->ResetCurrentCubeIndex();
	m_pParentObject->GetComponent<JumpComponent>()->ResetCurrentDiscIndex();
	m_pParentObject->GetComponent<ColliderComponent>()->SetTargetCubeIndex(0);
	m_pParentObject->GetComponent<TransformComponent>()->SetPosition(cubeStartPosition.x + 10, cubeStartPosition.y - 20, cubeStartPosition.z);

}