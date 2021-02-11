#pragma once

namespace Helheim
{
	class Component
	{
		public:
			Component() = default;
			virtual ~Component() = default;

			Component(const Component&) = delete;
			Component(Component&&) noexcept = delete;
			Component& operator=(const Component&) = delete;
			Component& operator=(Component&&) noexcept = delete;

		protected:
			virtual void Initialize() = 0;
			virtual void Update() = 0;
			virtual void Draw() = 0;
			
		private:

	};
}