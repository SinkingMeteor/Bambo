#pragma once
#include "pch.h"
#include "Utils.h"
namespace Bambo 
{
	class Shader 
	{
		enum class CheckType 
		{
			VertexShader,
			FragmentShader,
			ShaderProgram
		};

	public:
		Shader();
		~Shader();
		uint GetID() const { return m_id; }
		void LoadFromFile(const char* vertexSourceFile, const char* fragmentSourceFile);
		Shader& Use();
		void SetFloat(const char* name, float value);
		void SetInteger(const char* name, int value);
		void SetVector2f(const char* name, glm::vec2 value);
		void SetVector3f(const char* name, glm::vec3 value);
		void SetMatrix4(const char* name, const glm::mat4& matrix);
	private:
		uint m_id;

		bool CheckErrors(uint id, CheckType type);
		void Compile(const char* vertexSource, const char* fragmentSource);

	};
}