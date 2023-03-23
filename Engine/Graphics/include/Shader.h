#pragma once
#include "pch.h"
#include "Graphics.h"
#include "Utils.h"

namespace Bambo 
{
	class BAMBO_API Shader 
	{
		enum class CheckType 
		{
			VertexShader,
			FragmentShader,
			ShaderProgram
		};

	public:
		Shader();
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		~Shader();
		GLuint GetID() const { return m_id; }
		void LoadFromFile(const std::string& vertexSourceFile, const std::string& fragmentSourceFile);
		Shader& Use();
		static void StopUse();
		void SetFloat(const char* name, float value);
		void SetInteger(const char* name, int value);
		void SetVector2f(const char* name, glm::vec2 value);
		void SetVector3f(const char* name, glm::vec3 value);
		void SetMatrix4(const char* name, const glm::mat4& matrix);
	private:
		GLuint m_id;

		bool CheckErrors(uint id, CheckType type);
		void Compile(const char* vertexSource, const char* fragmentSource);

	};
}