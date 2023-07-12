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
}

int main()
{
	Player player1{ Point{ 10, 25 }, Point{ 30, 125 }};
	Player player2{ Point{ 10, 25 }, Point{ 30, 125 }};
	Player player3{ Point{ 10, 25 }, Point{ 30, 125 }};

	PlayerArray arr{};
	arr.Players.push_back(player1);
	arr.Players.push_back(player2);
	arr.Players.push_back(player3);

	rttr::instance inst{ player1 };

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