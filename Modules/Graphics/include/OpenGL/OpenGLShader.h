#pragma once
#include "pch.h"
#include "Graphics.h"
#include "ShaderImplementation.h"
namespace Bambo
{
	class BAMBO_API OpenGLShader final : public ShaderImplementation
	{
	public:
		OpenGLShader();
		virtual ~OpenGLShader();
		virtual void Use() override;
		virtual void LoadFromFile(const std::string& vertexSourceFile, const std::string& fragmentSourceFile) override;
		virtual void SetFloat(const char* name, float value) override;
		virtual void SetInteger(const char* name, int value) override;
		virtual void SetVector2f(const char* name, const glm::vec2& value) override;
		virtual void SetVector3f(const char* name, const glm::vec3& value) override;
		virtual void SetMatrix4(const char* name, const glm::mat4& matrix) override;
	private:
		enum class CheckType
		{
			VertexShader,
			FragmentShader,
			ShaderProgram
		};

		GLuint m_id;

		bool CheckErrors(uint id, CheckType type);
		void Compile(const char* vertexSource, const char* fragmentSource);

	};
}