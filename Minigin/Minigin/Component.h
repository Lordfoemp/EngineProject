#pragma once

namespace dae
{ 
	class GameObject; 
}
namespace Helheim
{
	class Component
	{
		public:
			Component(std::shared_ptr<dae::GameObject>& pParentObject, const bool canRenderComponent);
			virtual ~Component() = default;

			Component(const Component&) = delete;
			Component(Component&&) noexcept = delete;
			Component& operator=(const Component&) = delete;
			Component& operator=(Component&&) noexcept = delete;

			virtual void Initialize() = 0;
			virtual void Update() = 0;
			
			bool GetCanRenderComponent() const { return m_CanRenderComponent; }

		protected:
			std::shared_ptr<dae::GameObject> m_pParentObject;			
			std::shared_ptr<dae::GameObject> GetParentObject() const { return m_pParentObject; }

		private:
			bool m_CanRenderComponent;
	};
}