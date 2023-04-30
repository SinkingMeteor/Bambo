#pragma once
#include "pch.h"
#include "Rect.h"
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
		virtual void Use() const = 0;
		virtual RectInt GetTextureRect() const = 0;

		static std::unique_ptr<TextureImplementation> CreateTexture();
	};
}