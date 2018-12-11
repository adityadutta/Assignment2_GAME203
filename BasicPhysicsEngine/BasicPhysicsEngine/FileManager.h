//#ifndef FILEMANAGER_H
//#define FILEMANAGER_H
//#include<SDL.h>
//#include<memory>
//#include"UI.h"
//#include"Body.h"
//#include "json.hpp"
//#include <fstream>
//#include<string>
//
//using json = nlohmann::json;
//
//class FileManager
//{
//private:
//	FileManager();
//	std::shared_ptr<UI> currentUI;
//public:
//	static FileManager* instance;
//	//singleton of the factory
//	FileManager* getInstance()
//	{
//		if (instance == nullptr) {
//			instance = new FileManager();
//
//		}
//		return instance;
//	}
//
//	void Load(std::string _fileName, std::vector<Body*> &coins, std::vector<Body*> &enemies, std::vector<Body*> &platforms) {
//		//Creates a json variable
//		json j;
//
//		//Opening and reading from a json file
//		std::ifstream i("savedata2.json");
//		i >> j;
//
//		//Iterates through the json data
//		for (json::iterator it = j.begin(); it != j.end(); ++it) {
//			//std::cout << j[it.key()] << std::endl;
//			if (j[it.key()]["type"] == "Coin") {
//				AddToList(coins, new Body("Sprites/coin.png", 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
//			}
//			if (j[it.key()]["type"] == "Enemies") {
//				AddToList(enemies, new Body("Sprites/GoombaWalk1.png", 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
//			}
//			if (j[it.key()]["type"] == "Terrain") {
//				AddToList(platforms, new Body("Sprites/Block.png", 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
//			}
//		}
//
//		//Closes the file
//		i.close();
//	}
//
//	inline void AddToList(std::vector<Body*> &list, Body * body)
//	{
//		list.push_back(body);
//	}
//
//};
//
//#endif //!FILEMANAGER_H