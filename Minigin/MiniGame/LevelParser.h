#pragma once
#include <string>

#include <vector>

class LevelParser final
{
	public:
		LevelParser(const std::string& filePath);
		~LevelParser() = default;

		LevelParser(const LevelParser&) = delete;
		LevelParser(LevelParser&&) noexcept = delete;
		LevelParser& operator=(const LevelParser&) = delete;
		LevelParser& operator=(LevelParser&&) noexcept = delete;

		void ParseLevel(std::vector<glm::vec3>& positions_Cubes, 
						std::vector<glm::vec3>& positions_Discs, 
						std::vector<std::pair<int, std::vector<int>>>& connectionsToCubes, 
						std::vector<std::pair<int, std::vector<int>>>& connectionsToDiscs);

	protected:

	private:
		std::string m_FilePath;
};