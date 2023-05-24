#pragma once
#include "Main/Module.h"

namespace BamboEditor
{
	class EditorModule : public Bambo::Module
	{
	public:
		EditorModule() = default;
		virtual int32 GetModuleName() const override { return 'EDTM'; }
	};
}