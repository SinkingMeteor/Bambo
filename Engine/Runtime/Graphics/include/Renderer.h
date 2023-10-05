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
		virtual ~Renderer() {}
		void SetDefaultShader(SPtr<Shader> defaultShader) { m_defaultShader = defaultShader; }
	protected:
		WPtr<Shader> m_defaultShader;

		Renderer();
		void RenderInternal(const SPtr<VertexArrayObject> vao, uint32 vertexAmount, RenderPrimitive primitive);
	};
}