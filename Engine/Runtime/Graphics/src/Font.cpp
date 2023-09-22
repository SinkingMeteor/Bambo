#include "Font.h"
#include "RenderManager.h"
#include "FontImplementation.h"

namespace Bambo
{
	Font::Font(std::size_t instanceID) :
		Resource(instanceID),
		m_fontImplementation()
	{
		m_fontImplementation = FontImplementation::CreateBamboFont();
	}

	void Font::LoadFromFile(const std::string& fontFile)
	{
		m_fontImplementation->LoadFromFile(fontFile);
	}

}