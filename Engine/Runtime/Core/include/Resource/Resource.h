#pragma once
#include "Essentials.h"
#include "Resource/ResourceInfo.h"
namespace Bambo
{
#define RESOURCE_BODY(ResourceTypename, EnumType) public:\
virtual std::size_t GetAssetTypeID() const override { return ResourceTypename::GetStaticID(); } \
static std::size_t GetStaticID() { return (std::size_t)EnumType; }

enum class AssetType
{
	None = 0,
	Texture2D,
	Shader,
	Audio,
	World,
	Font
};

class Resource
{
public:
	Resource(const Resource&) = delete;
	Resource& operator=(const Resource&) = delete;

	virtual std::size_t GetAssetTypeID() const = 0;
	virtual std::size_t GetAssetInstanceID() const { return m_instanceID; }

	virtual bool IsValid() const { return m_instanceID != 0u && GetAssetTypeID() != 0; }

protected:
	std::size_t m_instanceID;

	Resource(std::size_t instanceID) : m_instanceID(instanceID) {}
};
}