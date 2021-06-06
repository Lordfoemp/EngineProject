#pragma once
#include <string>

namespace Helheim
{
	class Scene;
	class QBERT;
	class GameObject;
	class Connection;
	class TextureComponent;
	class Disc final
	{
		public:
			Disc();
			~Disc() = default;

			Disc(const Disc&) = delete;
			Disc(Disc&&) noexcept = delete;
			Disc& operator=(const Disc&) = delete;
			Disc& operator=(Disc&&) noexcept = delete;

			void Initialize(Scene * pCurrentScene, const glm::vec3 & pos, const std::string & folderpath);

			GameObject* GetGameObject() const { return m_pDiscGO; }

		protected:

		private:
			float m_Width;
			float m_Height;
			GameObject* m_pDiscGO;
			TextureComponent* m_pTexture_01;
	};
}