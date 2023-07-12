#include "Serialization/JsonSerializer.h"

namespace
{
	rttr::variant DeserializePrimitive(nlohmann::json& node)
	{
		if (node.is_null()) return rttr::variant{};
		if (node.is_boolean()) return node.get<bool>();
		if (node.is_number_integer()) return node.get<int32>();
		if (node.is_number_unsigned()) return node.get<uint32>();
		if (node.is_number_float()) return node.get<double>();
		if (node.is_string()) return node.get<std::string>();

		return rttr::variant{};
	}

	rttr::variant DeserializeValue(const rttr::type& type, nlohmann::json& node)
	{

	}

	void FromJsonInternal(const rttr::instance& instance, nlohmann::json& jsonNode)
	{
		rttr::instance currentInst = instance.get_type().get_raw_type().is_wrapper() ? instance.get_wrapped_instance() : instance;
		const auto propList = currentInst.get_derived_type().get_properties();

		for (auto prop : propList)
		{
			nlohmann::json propNode = jsonNode[prop.get_name().data()];
			if (propNode.is_null())
				continue;

			const rttr::type valueType = prop.get_type();
			
			if (propNode.is_array())
			{
				BAMBO_ASSERT_S(false)
			}
			else if (propNode.is_object())
			{
				rttr::variant variant = prop.get_value(currentInst);
				FromJsonInternal(variant, propNode);
				prop.set_value(currentInst, variant);
			}
			else
			{
				rttr::variant extractedValue = DeserializePrimitive(propNode);
				if (extractedValue.convert(valueType))
				{
					prop.set_value(currentInst, extractedValue);
				}
			}
		}
	}
}

namespace Bambo
{
	bool FromJson(rttr::instance& instance, nlohmann::json& jsonNode)
	{
		FromJsonInternal(instance, jsonNode);
		return true;
	}
}