#pragma once
#include <SDL_mixer.h>

namespace dae
{
	class SoundManager
	{
		public:
			SoundManager();
			~SoundManager();
			SoundManager(const SoundManager& obj) = delete;
			SoundManager& operator=(const SoundManager& obj) = delete;

			void Update();

			void PlaySound(const int choice);
		protected:

		private:
			void Initialize();

			Mix_Music* m_pMusic;
			Mix_Chunk* m_pSFX;
	};
}
