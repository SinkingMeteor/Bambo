#pragma once
#include "pch.h"
#include "Graphics.h"
#include "ShaderImplementation.h"

namespace Bambo 
{
	class BAMBO_API Shader final
	{

	public:
		Shader();
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		void Use() { m_shaderImplementation->Use(); }
		void LoadFromFile(const std::string& vertexSourceFile, const std::string& fragmentSourceFile) { m_shaderImplementation->LoadFromFile(vertexSourceFile, fragmentSourceFile); }
		void SetFloat(const char* name, float value) { m_shaderImplementation->SetFloat(name, value); }
		void SetInteger(const char* name, int value) { m_shaderImplementation->SetInteger(name, value); }
		void SetVector2f(const char* name, const glm::vec2& value) { m_shaderImplementation->SetVector2f(name, value); }
		void SetVector3f(const char* name, const glm::vec3& value) { m_shaderImplementation->SetVector3f(name, value); }
		void SetMatrix4(const char* name, const glm::mat4& matrix) { m_shaderImplementation->SetMatrix4(name, matrix); }
	private:
		std::unique_ptr<ShaderImplementation> m_shaderImplementation;
	};
}