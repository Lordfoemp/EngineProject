#include "MiniGamePCH.h"
#include "LevelParser.h"

#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

LevelParser::LevelParser(const std::string& filePath)
	: m_FilePath(filePath)
{}

void LevelParser::ParseLevel(std::vector<glm::vec3>& positions_Cubes, std::vector<glm::vec3>& positions_Discs, std::vector<std::pair<int, std::vector<int>>>& connectionsToCubes, std::vector<std::pair<int, std::vector<int>>>& connectionsToDiscs)
{
	std::ifstream levelFile;
	levelFile.open(m_FilePath);
	if (levelFile.is_open())
	{
		std::string output;
		while (!levelFile.eof())
		{
			while (std::getline(levelFile, output))
			{
				// Cube positions
				if (output.substr(0, 2) == "CP")
				{
					std::string coordinate{ output.substr(3) };
					std::istringstream ss(coordinate);

					char comma{};
					float x{};
					float y{};
					float z{};
					ss >> x >> comma >> y >> comma >> z;
					positions_Cubes.push_back({ x, y, z });
				}
				// Disc positions
				if (output.substr(0, 2) == "DP")
				{
					std::string coordinate{ output.substr(3) };
					std::istringstream ss(coordinate);

					char comma{};
					float x{};
					float y{};
					float z{};
					ss >> x >> comma >> y >> comma >> z;
					positions_Discs.push_back({ x, y, z });
				}
				// Cube connections
				if (output.substr(0, 2) == "CC")
				{
					std::string coordinate{ output.substr(3) };
					std::istringstream ss(coordinate);

					char comma{}, stripe{};
					int cube{};
					int c0{}, c1{}, c2{}, c3{};
					ss >> cube >> stripe >> c0 >> comma >> c1 >> comma >> c2 >> comma >> c3;
					std::vector<int> connecs{c0, c1, c2, c3};
					
					std::vector<int>::iterator newEnd = std::remove_if(connecs.begin(), connecs.end(), [](int const& i) { return i == -1; });
					connecs.erase(newEnd, connecs.end());
					
					connectionsToCubes.push_back(std::pair<int, std::vector<int>>(cube, connecs));
				}
				// Disc connections
				if (output.substr(0, 2) == "DC")
				{
					std::string coordinate{ output.substr(3) };
					std::istringstream ss(coordinate);

					char comma{}, stripe{};
					int cube{};
					int c0{}, c1{}, c2{}, c3{};
					ss >> cube >> stripe >> c0 >> comma >> c1 >> comma >> c2 >> comma >> c3;
					std::vector<int> connecs{ c0, c1, c2, c3 };

					std::vector<int>::iterator newEnd = std::remove_if(connecs.begin(), connecs.end(), [](int const& i) { return i == -1; });
					connecs.erase(newEnd, connecs.end());

					connectionsToDiscs.push_back(std::pair<int, std::vector<int>>(cube, connecs));
				}
			}
		}
	}
	levelFile.close();
}