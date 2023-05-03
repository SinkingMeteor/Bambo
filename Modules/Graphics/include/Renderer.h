#pragma once
#include "pch.h"
#include "RenderConfig.h"
#include "VertexArrayObject.h"
#include "RendererImplementation.h"
#include "Camera.h"
namespace Bambo
{
	class BAMBO_API Renderer
	{
	public:
		Renderer();
		Renderer(const Renderer& renderer) = delete;
		Renderer& operator=(const Renderer& renderer) = delete;
		virtual ~Renderer() {}

		virtual void Initialize();
		void SetCamera(SPtr<Camera> camera) { m_camera = camera; }
	protected:
		WPtr<Camera> m_camera;

		void RenderInternal(const SPtr<VertexArrayObject> vao, uint32 vertexAmount);
	};
}