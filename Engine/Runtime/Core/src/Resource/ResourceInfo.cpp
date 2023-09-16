#include "Resource/ResourceInfo.h"

namespace Bambo
{
	void ResourceInfo::LoadInfo(const std::filesystem::path& metaFilePath)
	{
		std::ifstream stream{ metaFilePath };
		BAMBO_ASSERT_S(!stream.fail())

		nlohmann::json rootNode{};
		stream >> rootNode;
		stream.close();

		AssetId = rootNode["assetid"].get<bambo_id>();
		TypeId = rootNode["typeid"].get<bambo_id>();

		std::filesystem::path filePath = metaFilePath;
		filePath.replace_extension();

		FullPath = filePath;
		FileName = filePath.filename();
		Extension = filePath.extension();
	}

	void ResourceInfo::SaveInfo(const std::filesystem::path& filePath)
	{
		std::ofstream stream{ filePath.string() + ".meta" };
		BAMBO_ASSERT_S(!stream.fail())

		nlohmann::json rootNode{};
		rootNode["assetid"] = AssetId;
		rootNode["typeid"] = TypeId;

		stream << rootNode;
		stream.close();
	}

	ResourceInfo ResourceInfo::Create(bambo_id assetId, bambo_id typeId, const std::filesystem::path& fullpath)
	{
		ResourceInfo info{};
		info.AssetId = assetId;
		info.TypeId = typeId;
		info.FullPath = fullpath;
		info.Extension = fullpath.extension();
		info.FileName = fullpath.filename();

		info.SaveInfo(fullpath);

		return info;
	}

}