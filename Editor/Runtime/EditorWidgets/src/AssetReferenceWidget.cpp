#include "AssetReferenceWidget.h"
#include "Resource/ResourceManager.h"
namespace
{
	std::string ASSET_NONE = "NULL ASSET";

}

namespace BamboEditor
{
	AssetReferenceWidget::AssetReferenceWidget(Bambo::AssetType assetType, std::size_t assetId) :
		m_assetType(assetType),
		m_assetId(assetId)
	{}

	void AssetReferenceWidget::Draw()
	{
		std::string assetName = ASSET_NONE;

		if (m_assetId)
		{
			Bambo::ResourceInfo* info = Bambo::ResourceManager::Get()->GetResourceMetaFile(m_assetId);
			if (info)
			{
				assetName = info->FileName.string();
			}
		}

		ImGui::Button(assetName.c_str());
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssignAsset");
			if (payload != nullptr)
			{
				m_assetId = *static_cast<std::size_t*>(payload->Data);
			}

			ImGui::EndDragDropTarget();
		}
	}
}
