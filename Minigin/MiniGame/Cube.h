#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace Helheim
{
	class Scene;
	class GameObject;
	class TextureComponent;
	class Cube final
	{
		public:
			Cube();
			~Cube() = default;

			Cube(const Cube&) = delete;
			Cube(Cube&&) noexcept = delete;
			Cube& operator=(const Cube&) = delete;
			Cube& operator=(Cube&&) noexcept = delete;

			void Initialize(Scene* pCurrentScene, const glm::vec3& pos);

		protected:

		private:
			bool m_IsColored;
			GameObject* m_pCubeGO;
			TextureComponent* m_pTexture_Base;
			TextureComponent* m_pTexture_Colored;
	};
}
