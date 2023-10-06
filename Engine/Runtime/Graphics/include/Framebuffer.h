#pragma once
#include "pch.h"
#include "RenderAPI.h"

namespace Bambo
{
	enum class FramebufferTextureType
	{
		None = 0,
		Color,
		Depth
	};

	class BAMBO_API Framebuffer
	{
	public:
		virtual ~Framebuffer() {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32 GetCurrentTextureWidth() const = 0;
		virtual uint32 GetCurrentTextureHeight() const = 0;
		virtual uint32 GetTextureID(uint32 index = 0) const = 0;
		virtual void Resize(uint32 width, uint32 height) = 0;
		virtual int32 ReadPixel(uint32 attachmentIndex, int32 x, int32 y) = 0;

		static SPtr<Framebuffer> Create(RenderAPI renderApi, const std::vector<FramebufferTextureType>& textureTypes, uint32 textureWidth, uint32 textureHeight);
	};
}