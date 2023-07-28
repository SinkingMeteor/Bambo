#pragma once
#include "engpch.h"
#include "glm.hpp"
#include "Rect.h"
#include "Camera.h"

namespace Bambo
{
	struct BAMBO_API CameraComponent final : public Component
	{
		Camera Camera;

		CameraComponent() = default;
		CameraComponent(const CameraComponent& camera) = default;

		virtual void Serialize(nlohmann::json& node) override
		{
			node["name"] = "CameraComponent";
			node["aspectRatio"] = Camera.GetAspectRatio();
			node["projType"] = static_cast<int32>(Camera.GetProjectionType());

			node["orthoSize"] = Camera.GetOrthographicSize();
			node["orthoNear"] = Camera.GetOrthoNear();
			node["orthoFar"] = Camera.GetOrthoFar();

			node["fov"] = Camera.GetFieldOfView();
			node["perpectiveNear"] = Camera.GetPespectiveNear();
			node["perpectiveFar"] = Camera.GetPespectiveFar();

		}

		virtual void Deserialize(nlohmann::json& node) override
		{
			Camera.SetAspectRatio(node["aspectRatio"].get<float>());
			Camera.SetProjectionType((node["projType"].get<CameraProjectionType>()));
			Camera.SetOrthographicSize(node["orthoSize"].get<float>());
			Camera.SetOrthographicNear(node["orthoNear"].get<float>());
			Camera.SetOrthographicFar(node["orthoFar"].get<float>());
			
			Camera.SetFieldOfView(node["fov"].get<float>());
			Camera.SetPerspectiveNear(node["perspectiveNear"].get<float>());
			Camera.SetPerspectiveFar(node["perspectiveFar"].get<float>());
		}
	};


}