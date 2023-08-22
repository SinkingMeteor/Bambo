#pragma once
#include "pch.h"
#include "RenderConfig.h"
#include "VertexArrayObject.h"
#include "RendererImplementation.h"
#include "Shader.h"
#include "Camera.h"
namespace Bambo
{
	class BAMBO_API Renderer
	{
	public:
		Renderer(const Renderer& renderer) = delete;
		Renderer& operator=(const Renderer& renderer) = delete;
		virtual void Render(std::vector<glm::mat4>& globalTransforms) = 0;
		virtual ~Renderer() {}
		void SetDefaultShader(SPtr<Shader> defaultShader) { m_defaultShader = defaultShader; }
		void SetProjViewMatrix(const glm::mat4& projViewMatrix) { m_projViewMatrix = projViewMatrix; }
	protected:
		WPtr<Shader> m_defaultShader;
		glm::mat4 m_projViewMatrix;

		Renderer();
		void RenderInternal(const SPtr<VertexArrayObject> vao, uint32 vertexAmount);
	};
}