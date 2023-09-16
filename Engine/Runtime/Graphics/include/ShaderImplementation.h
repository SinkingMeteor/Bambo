#pragma once
#include "Essentials.h"

namespace Bambo
{
	class BAMBO_API ShaderImplementation
	{
	public:
		ShaderImplementation() = default;
		ShaderImplementation(const ShaderImplementation&) = delete;
		ShaderImplementation& operator=(const ShaderImplementation&) = delete;
		virtual ~ShaderImplementation() {}

		virtual void Use() = 0;
		virtual void LoadFromFile(const std::string& sourceFile) = 0;
		virtual void SetFloat(const char* name, float value) = 0;
		virtual void SetInteger(const char* name, int value) = 0;
		virtual void SetVector2f(const char* name, const glm::vec2& value) = 0;
		virtual void SetVector3f(const char* name, const glm::vec3& value) = 0;
		virtual void SetMatrix4(const char* name, const glm::mat4& matrix) = 0;

		static std::unique_ptr<ShaderImplementation> CreateInternalShader();
	};
}