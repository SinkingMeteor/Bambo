#include "Texture2D.h"
#include "Utils.h"
#include "Engine.h"
namespace Bambo
{
	Texture2D::Texture2D(Engine* engine, const std::size_t assetId) :
		Resource(assetId, engine),
		m_textureImplementation(),
		m_textureRects()
	{
		m_textureImplementation = TextureImplementation::CreateTexture(m_engine->GetRenderManager()->GetCurrentRenderAPI());
	}

	void Texture2D::AddSubTex(const RectUInt& rect, const TextureBuffer& buffer)
	{
		m_textureImplementation->AddSubTex(rect, buffer);
	}

	void Texture2D::AddSubTex(const RectUInt& rect, const uint8* data, TexChannelsAmount channels)
	{
		m_textureImplementation->AddSubTex(rect, data, channels);
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
			m_textureRects.push_back(RectInt{ 0, texHeight, texWidth, texHeight});
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

		for (int32 x = texWidth; x >= 0; x -= xStep)
		{
			for (int32 y = texHeight; y >= 0; y -= yStep)
			{
				m_textureRects.push_back(RectInt{ x, y, xStep, yStep });
			}
		}
	}

	void Texture2D::LoadFromBuffer(const TextureBuffer& buffer)
	{
		m_textureRects.clear();
		m_textureImplementation->LoadFromBuffer(buffer);

		int32 texWidth = m_textureImplementation->GetTextureWidth();
		int32 texHeight = m_textureImplementation->GetTextureHeight();
		m_textureRects.push_back(RectInt{ 0, texHeight, texWidth, texHeight });
	}

}