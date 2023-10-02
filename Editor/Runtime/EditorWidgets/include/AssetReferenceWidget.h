#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"

#include "Widget.h"
#include "Resource/Resource.h"

namespace BamboEditor
{
	class AssetReferenceWidget final : public Widget
	{
	public:
		AssetReferenceWidget(Bambo::AssetType assetType, std::size_t assetId = 0);
		std::size_t GetAssetID() const { return m_assetId; }
		void SetAssetID(std::size_t assetId) { m_assetId = assetId; }
		virtual void Draw() override;
	private:
		Bambo::AssetType m_assetType;
		std::size_t m_assetId;
	};
}