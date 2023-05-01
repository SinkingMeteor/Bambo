#include "OpenGL\OpenGLShader.h"

namespace Bambo
{
	OpenGLShader::OpenGLShader() :
		ShaderImplementation(),
		m_id(0)
	{

	}

	OpenGLShader::~OpenGLShader()
	{
		if (m_id) glDeleteProgram(m_id);
	}

	void OpenGLShader::Use()
	{
		glUseProgram(m_id);
	}

	void OpenGLShader::LoadFromFile(const std::string& vertexSourceFile, const std::string& fragmentSourceFile)
	{
		std::ifstream tv(vertexSourceFile.c_str());
		std::stringstream vertexBuffer;
		vertexBuffer << tv.rdbuf();

		std::ifstream tf(fragmentSourceFile.c_str());
		std::stringstream fragmentBuffer;
		fragmentBuffer << tf.rdbuf();

		Compile(vertexBuffer.str().c_str(), fragmentBuffer.str().c_str());
	}

	void OpenGLShader::SetFloat(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(m_id, name), value);
	}

	void OpenGLShader::SetInteger(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(m_id, name), value);
	}

	void OpenGLShader::SetVector2f(const char* name, const glm::vec2& value)
	{
		glUniform2f(glGetUniformLocation(m_id, name), value.x, value.y);
	}

	void OpenGLShader::SetVector3f(const char* name, const glm::vec3& value)
	{
		glUniform3f(glGetUniformLocation(m_id, name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetMatrix4(const char* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, false, static_cast<const float*>(glm::value_ptr(matrix)));
	}

	bool OpenGLShader::CheckErrors(uint32 id, OpenGLShader::CheckType type)
	{
		int32 result{};
		char infoLog[1024];
		switch (type)
		{
		case OpenGLShader::CheckType::ShaderProgram:
			glGetProgramiv(id, GL_LINK_STATUS, &result);
			if (!result)
			{
				glGetProgramInfoLog(id, 1024, nullptr, infoLog);
				Logger::Log("LogShader", Verbosity::Error, "ERROR: Compile-time error: %s", (const char*)infoLog);
				return BAMBO_FALSE;
			}
			break;
		default:
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (!result)
			{
				glGetShaderInfoLog(id, 1024, nullptr, infoLog);
				Logger::Log("LogShader", Verbosity::Error, "ERROR: Compile-time error: %s", (const char*)infoLog);
				return BAMBO_FALSE;
			}
			break;
		}
		return BAMBO_TRUE;
	}

	void OpenGLShader::Compile(const char* vertexSource, const char* fragmentSource)
	{
		GLuint vertexShader{};
		GLuint fragmentShader{};

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		CheckErrors(vertexShader, OpenGLShader::CheckType::VertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		CheckErrors(fragmentShader, OpenGLShader::CheckType::FragmentShader);

		m_id = glCreateProgram();
		glAttachShader(m_id, vertexShader);
		glAttachShader(m_id, fragmentShader);
		glLinkProgram(m_id);
		CheckErrors(m_id, OpenGLShader::CheckType::ShaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
}

