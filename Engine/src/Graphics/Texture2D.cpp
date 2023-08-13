#include "Graphics/Texture2D.h"

namespace Bambo 
{
	Texture2D::Texture2D(const std::size_t assetId) :
		m_assetId(assetId),
		m_textureImplementation(),
		m_textureRects()
	{
		m_textureImplementation = TextureImplementation::CreateTexture();
	}

	void Texture2D::LoadFromFile(const std::filesystem::path& filePath)
	{
		m_textureRects.clear();
		m_textureImplementation->LoadFromFile(filePath.string());

		std::filesystem::path metaPath = filePath.string() + ".meta";
		int32 texWidth = m_textureImplementation->GetTextureWidth();
		int32 texHeight = m_textureImplementation->GetTextureHeight();

		if (!std::filesystem::exists(metaPath))
		{
			m_textureRects.push_back(RectInt{0, 0, texWidth, texHeight});
			return;
		}

		std::ifstream texMetaFile{ metaPath };
		BAMBO_ASSERT_S(!texMetaFile.fail())

		nlohmann::json metaNode{};
		metaNode << texMetaFile;
		texMetaFile.close();

		int32 rowsNum = 1;
		int32 columnsNum = 1;

		if (!metaNode["rowsnum"].is_null())
		{
			rowsNum = metaNode["rowsnum"].get<int32>();
		}
		if (!metaNode["columnsnum"].is_null())
		{
			columnsNum = metaNode["columnsnum"].get<int32>();
		}

		const int32 xStep = texWidth / columnsNum;
		const int32 yStep = texHeight / rowsNum;
		m_textureRects.reserve(xStep * yStep);

		for (int32 x = 0; x < columnsNum; ++x)
		{
			for (int32 y = 0; y < rowsNum; ++y)
			{
				m_textureRects.push_back(RectInt{ xStep * x, yStep * y, xStep, yStep });
			}
		}
	}

}