#pragma once
#include "Core/Essentials.h"
#include "Graphics/Rect.h"
#include "Graphics/Camera.h"

namespace Bambo
{
	struct BAMBO_API CameraComponent final : public Component
	{
		COMPONENT_BODY(CameraComponent)

		Camera Camera;

		CameraComponent() = default;

		virtual void Serialize(nlohmann::json& node) override
		{
			node["name"] = "CameraComponent";
			node["aspectRatio"] = Camera.GetAspectRatio();
			node["projType"] = static_cast<int32>(Camera.GetProjectionType());

			node["orthoSize"] = Camera.GetOrthographicSize();
			node["orthoNear"] = Camera.GetOrthoNear();
			node["orthoFar"] = Camera.GetOrthoFar();

			node["fov"] = Camera.GetFieldOfView();
			node["perspectiveNear"] = Camera.GetPespectiveNear();
			node["perspectiveFar"] = Camera.GetPespectiveFar();

		}

		virtual void Deserialize(nlohmann::json& node) override
		{
			Camera.SetProjectionType((node["projType"].get<CameraProjectionType>()));
			Camera.SetOrthographicSize(node["orthoSize"].get<float>());
			Camera.SetOrthographicNear(node["orthoNear"].get<float>());
			Camera.SetOrthographicFar(node["orthoFar"].get<float>());
			Camera.SetAspectRatio(node["aspectRatio"].get<float>());

			Camera.SetFieldOfView(node["fov"].get<float>());
			Camera.SetPerspectiveNear(node["perspectiveNear"].get<float>());
			Camera.SetPerspectiveFar(node["perspectiveFar"].get<float>());
		}
	};


}