#pragma once

struct _TTF_Font;
namespace Helheim
{
	class Font
	{
		public:
			explicit Font(const std::string& fullPath, unsigned int size);
			~Font();

			Font(const Font &) = delete;
			Font(Font &&) = delete;
			Font & operator= (const Font &) = delete;
			Font & operator= (const Font &&) = delete;
			
			_TTF_Font* GetFont() const { return m_pFont; }

		private:
			_TTF_Font* m_pFont;
			unsigned int m_Size;
	};
}