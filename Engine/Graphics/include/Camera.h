#pragma once
#include "pch.h"
#include "glm.hpp"
#include "Rect.h"
#include "Transform.h"
#include "CommonMath.h"
#include "Interfaces/ITransformable.h"
namespace Bambo
{
	class BAMBO_API Camera : public ITransformable
	{
	public:
		Camera();
		Camera(const RectFloat& cameraRect);
		Camera(const glm::vec2& center, const glm::vec2& size);
		Camera(const Camera& camera) = delete;
		Camera& operator=(const Camera& camera) = delete;
		void SetRect(const RectFloat& cameraRect);
		void Reset(const RectFloat& cameraRect);
		glm::vec2 GetCameraCenter() const;
		glm::vec2 GetCameraSize() const;
		RectFloat GetCameraRect() const;
		void Zoom(float factor);
		virtual Transform& GetTransform() override;
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjViewMatrix() const;
	private:
		glm::vec2 GetHalfOfCameraSize() const { return glm::vec2{ m_size.x * 0.5f, m_size.y * 0.5f }; }

		mutable Transform m_transform;
		mutable Matrix m_projViewMatrix;
		glm::vec2 m_size;
	};
}