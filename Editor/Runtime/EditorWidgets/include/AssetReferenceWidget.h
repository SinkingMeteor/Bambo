#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"

#include "Widget.h"
#include "Resource/Resource.h"
#include "Resource/ResourceManager.h"

namespace BamboEditor
{
	class AssetReferenceWidget final : public Widget
	{
	public:
		AssetReferenceWidget(Bambo::ResourceManager* resourceManager, Bambo::AssetType assetType, std::size_t assetId = 0);
		std::size_t GetAssetID() const { return m_assetId; }
		void SetAssetID(std::size_t assetId) { m_assetId = assetId; }
		virtual void Draw() override;
	private:
		Bambo::ResourceManager* m_resourceManager;
		Bambo::AssetType m_assetType;
		std::size_t m_assetId;
	};
}