#include "Graphics/Shader.h"

namespace Bambo 
{
	Shader::Shader() :
		m_id(0)
	{

	}

	Shader::~Shader()
	{
		if (m_id) glDeleteProgram(m_id);
	}

	Shader& Shader::Use()
	{
		glUseProgram(m_id);
		return *this;
	}

	void Shader::StopUse()
	{
		glUseProgram(0);
	}

	void Shader::LoadFromFile(const std::string& vertexSourceFile, const std::string& fragmentSourceFile) 
	{
		std::ifstream tv(vertexSourceFile.c_str());
		std::stringstream vertexBuffer;
		vertexBuffer << tv.rdbuf();

		std::ifstream tf(fragmentSourceFile.c_str());
		std::stringstream fragmentBuffer;
		fragmentBuffer << tf.rdbuf();

		Compile(vertexBuffer.str().c_str(), fragmentBuffer.str().c_str());
	}

	void Shader::Compile(const char* vertexSource, const char* fragmentSource)
	{
		GLuint vertexShader{};
		GLuint fragmentShader{};

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		CheckErrors(vertexShader, Shader::CheckType::VertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		CheckErrors(fragmentShader, Shader::CheckType::FragmentShader);

		m_id = glCreateProgram();
		glAttachShader(m_id, vertexShader);
		glAttachShader(m_id, fragmentShader);
		glLinkProgram(m_id);
		CheckErrors(m_id, Shader::CheckType::ShaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}


	void Shader::SetFloat(const char* name, float value) 
	{
		glUniform1f(glGetUniformLocation(m_id, name), value);
	}

	void Shader::SetInteger(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(m_id, name), value);
	}

	void Shader::SetVector2f(const char* name, glm::vec2 value)
	{
		glUniform2f(glGetUniformLocation(m_id, name), value.x, value.y);
	}

	void Shader::SetVector3f(const char* name, glm::vec3 value)
	{
		glUniform3f(glGetUniformLocation(m_id, name), value.x, value.y, value.z);
	}

	void Shader::SetMatrix4(const char* name, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, false, static_cast<const float*>(glm::value_ptr(value)));
	}

	bool Shader::CheckErrors(uint id, Shader::CheckType checkType) 
	{
		int result{};
		char infoLog[1024];
		switch (checkType) 
		{
		case Shader::CheckType::ShaderProgram:
			glGetProgramiv(id, GL_LINK_STATUS, &result);
			if (!result) 
			{
				glGetProgramInfoLog(id, 1024, nullptr, infoLog);
				Log("LogShader", "ERROR: Compile-time error: %s", (const char*)infoLog);
				return BAMBO_FALSE;
			}
			break;
		default:
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (!result)
			{
				glGetShaderInfoLog(id, 1024, nullptr, infoLog);
				Log("LogShader", "ERROR: Compile-time error: %s", (const char*)infoLog);
				return BAMBO_FALSE;
			}
			break;
		}
		return BAMBO_TRUE;
	}
}