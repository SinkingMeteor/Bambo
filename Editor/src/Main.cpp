#include <memory>
#include "Main/Engine.h"
#include "EditorModule.h"
#include "Essentials.h"
#include "Serialization/JsonSerializer.h"

struct Point
{
	int32 X;
	int32 Y;
};

struct Player
{
	Point XPoint;
	Point YPoint;
};

struct PlayerArray
{
	std::vector<Player> Players{};
};

struct PlayerMap
{
	std::unordered_map<int32, Player> Players{};
};

RTTR_REGISTRATION
{
	rttr::registration::class_<Point>("Point")
		.property("X", &Point::X)
		.property("Y", &Point::Y);

	rttr::registration::class_<Player>("Player")
		.property("XPoint", &Player::XPoint)
		.property("YPoint", &Player::YPoint);

	rttr::registration::class_<PlayerArray>("PlayerArray")
		.property("Players", &PlayerArray::Players);

	rttr::registration::class_<PlayerMap>("PlayerMap")
		.property("Players", &PlayerMap::Players);
}

int main()
{
	Player player1{ Point{ 10, 25 }, Point{ 30, 125 }};
	Player player2{ Point{ 11, 26 }, Point{ 31, 126 }};
	Player player3{ Point{ 12, 29 }, Point{ 32, 128 }};

	PlayerArray arr{};
	arr.Players.push_back(player1);
	arr.Players.push_back(player2);
	arr.Players.push_back(player3);

	PlayerMap map{};
	map.Players[0] = player1;
	map.Players[1] = player2;
	map.Players[2] = player3;

	rttr::instance inst{ map };

	nlohmann::json rootJson{};
	std::ofstream stream{ "E:/TestFile.json" };

	Bambo::ToJson(inst, rootJson);

	stream << rootJson;
	stream.close();

	Bambo::Engine engine{};
	engine.Initialize();
	engine.AddModule(std::make_unique<BamboEditor::EditorModule>());
	engine.Run();
	return 0;

}