#include <GameMap.hpp>

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ResourceManager.hpp>

std::string getSpriteName(int i)
{
	switch (i)
	{
	case 1:
		return "ground_texture_corner_L"; //"Siradan Platform";
	case 2:
		return "ground_texture_middle"; // orta cimen
	case 3:
		return "ground_texture_corner_R"; // Sag cimen
	case 4:
		return "ground_texture_soil"; // Sol cimen
	case 5:
		return "key1"; // 
	case 6:
		return "key2"; // 
	case 7:
		return "keywhole"; // SU
	case 8:
		return "sarkit";
	case 9:
		return "spikes";
	case 10:
		return "platform_corner_L"; //"platform_L_M";
	case 11:
		return "platform_corner_R";
	case 12:
		return "platform_mid";
	case 13:
		return "wall_wine";
	case 14:
		return "wall_texture";
	case 15:
		return "asit7";
	case 16:
		return "door1";
	default:
		return "";
	}
}

/* ************************ [v] PRIVATE FUNCTIONS [v] *********************** */
void
	GameMap::init(
		std::vector<std::vector<unsigned int>>	tileData,
		unsigned int							levelWidth,
		unsigned int							levelHeight
	)
{

	unsigned int	height		= tileData.size();
	unsigned int	width		= tileData[0].size();
	//float			unit_width	= levelWidth / static_cast<float>(width), unit_height = levelHeight / height;
	float			unit_width  = 100.0f;
	float			unit_height = 100.0f;

	for (unsigned int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			if (tileData[y][x] > 0 && tileData[y][x] < 16)
			{
				glm::vec2 pos(unit_width * x, unit_height * y);
				std::string spriteName = getSpriteName(tileData[y][x]);
				glm::vec2 size = ResourceManager::getTexture(spriteName).getSize();
				Wall wall(pos, ResourceManager::getTexture(spriteName).getSize(), spriteName, glm::vec3(0.8f, 0.8f, 0.7f));
				wall.setSolid(true);
				this->walls.push_back(wall);
			}
			else if (tileData[y][x] == 16)
			{
				glm::vec2 pos(unit_width * x, unit_height * y);
				std::string spriteName = "door1";
				glm::vec2 size = ResourceManager::getTexture(spriteName).getSize();
				Wall wall1(pos, ResourceManager::getTexture(spriteName).getSize(), spriteName, glm::vec3(0.8f, 0.8f, 0.7f));
				wall1.setSolid(true);
				this->walls.push_back(wall1);

				spriteName = "door2";
				size = ResourceManager::getTexture(spriteName).getSize();
				Wall wall2(pos, ResourceManager::getTexture(spriteName).getSize(), spriteName, glm::vec3(0.8f, 0.8f, 0.7f));
				wall2.setSolid(true);
				this->walls.push_back(wall2);

				spriteName = "door3";
				size = ResourceManager::getTexture(spriteName).getSize();
				Wall wall3(pos, ResourceManager::getTexture(spriteName).getSize(), spriteName, glm::vec3(0.8f, 0.8f, 0.7f));
				wall3.setSolid(true);
				this->walls.push_back(wall3);
			}
			else if (tileData[y][x] == 100)
			{
				//glm::vec2 playerPos = glm::vec2(levelWidth / 2.0f - _playerSize.x / 2.0f, (levelHeight * 2) - _playerSize.y);
				std::cout << "Player position: " << unit_width * x << " " << unit_height * y << std::endl;
				glm::vec2 playerPos = glm::vec2(unit_width * x, unit_height * y + 60);
				_player = new Player(playerPos, ResourceManager::getTexture("player").getSize(), "player");
				_player->setSolid(true);
			}
			else if (tileData[y][x] == 200)
			{
				glm::vec2 enemyWowoPos(unit_width * x, unit_height * y);
				_enemyWowo = new Wowo(enemyWowoPos, ResourceManager::getTexture("wowo").getSize(), "wowo", glm::vec3(1.0f));
				_enemyWowo->setSolid(true);
			}
		}
	}
}
/* ************************ [^] PRIVATE FUNCTIONS [^] *********************** */

/* ******************* [v] CONSTRUCTOR AND DESTRUCTOR [v] ******************* */

GameMap::GameMap(void){}

GameMap::~GameMap()
{
}
/* ******************* [^] CONSTRUCTOR AND DESTRUCTOR [^] ******************* */

/* **************************** [v] GETTERS [v] ***************************** */
GameObject GameMap::getGameObject(int index)
{
	return this->objects[index];
}

bool GameMap::isCompleted()
{
	for (GameObject &tile : this->objects)
		if (!tile.isSolid() && !tile.isDestroyed())
			return false;
	return true;
}
/* **************************** [^] GETTERS [^] ***************************** */

/* **************************** [v] SETTERS [v] ***************************** */
void GameMap::addGameObject(GameObject obj)
{
	this->objects.push_back(obj);
}
/* **************************** [^] SETTERS [^] ***************************** */

/* **************************** [v] FUNCTIONS [v] *************************** */
void
	GameMap::load(
		const char *file,
		unsigned int levelWidth,
		unsigned int levelHeight
	)
{
	// clear old data
	this->objects.clear();
	// load from file
	unsigned int tileCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode) // read each word separated by spaces
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
	}
}

void GameMap::draw(SpriteRenderer &renderer)
{
	for (Wall &tile : this->walls)
		if (!tile.isDestroyed())
			tile.draw(renderer);
}
/* **************************** [^] FUNCTIONS [^] *************************** */
