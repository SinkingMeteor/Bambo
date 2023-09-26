#pragma once
#include "pch.h"
#include "Rect.h"
#include "TextureBuffer.h"
namespace Bambo
{
	class BAMBO_API TextureImplementation
	{
	public:
		TextureImplementation() = default;
		TextureImplementation(const TextureImplementation&) = delete;
		TextureImplementation& operator=(const TextureImplementation&) = delete;
		virtual ~TextureImplementation() {}

		virtual void LoadFromFile(const std::string& file) = 0;
		virtual void LoadFromBuffer(const TextureBuffer& buffer) = 0;
		virtual RectInt GetTextureRect() const = 0;
		virtual void Use() const = 0;
		virtual uint32 GetID() const = 0;
		virtual int32 GetTextureWidth() = 0;
		virtual int32 GetTextureHeight() = 0;
		virtual void AddSubTex(const RectUInt& rect, const TextureBuffer& buffer) = 0;
		virtual void AddSubTex(const RectUInt& rect, const uint8* data, TexChannelsAmount channels) = 0;

		static std::unique_ptr<TextureImplementation> CreateTexture();
	};
}