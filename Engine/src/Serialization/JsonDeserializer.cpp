#include "Serialization/JsonSerializer.h"

namespace
{
	void FromJsonInternal(const rttr::instance& instance, nlohmann::json& jsonNode);

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
		rttr::variant extractedValue = DeserializePrimitive(node);
		const bool isConverted = extractedValue.convert(type);
		if (!isConverted && node.is_object())
		{
			rttr::constructor ctor = type.get_constructor();
			for (auto& item : type.get_constructors())
			{
				if (item.get_instantiated_type() == type)
				{
					ctor = item;
				}
			}
			extractedValue = ctor.invoke();
			FromJsonInternal(extractedValue, node);
		}
		return extractedValue;
	}

	void DeserializeArray(rttr::variant_sequential_view& view, nlohmann::json& node)
	{
		view.set_size(node.size());
		const rttr::type arrayValueType = view.get_rank_type(1);

		for (std::size_t i = 0; i < node.size(); ++i)
		{
			nlohmann::json& jsonIndexValue = node[i];
			if (jsonIndexValue.is_array())
			{
				auto subArrayView = view.get_value(i).create_sequential_view();
				DeserializeArray(subArrayView, jsonIndexValue);
			}
			else if (jsonIndexValue.is_object())
			{
				rttr::variant varTmp = view.get_value(i);
				rttr::variant wrappedVar = varTmp.extract_wrapped_value();
				FromJsonInternal(wrappedVar, jsonIndexValue);
				view.set_value(i, wrappedVar);
			}
			else
			{
				rttr::variant extractedValue = DeserializePrimitive(jsonIndexValue);
				if (extractedValue.convert(arrayValueType))
					view.set_value(i, extractedValue);
			}
		}
	}

	void DeserializeAssociativeContainer(rttr::variant_associative_view& view, nlohmann::json& node)
	{
		for (std::size_t i = 0; i < node.size(); ++i)
		{
			nlohmann::json& jsonIndexValue = node[i];
			if (jsonIndexValue.is_object())
			{
				auto keyNodeIt = jsonIndexValue.find("key");
				auto valueNodeIt = jsonIndexValue.find("value");

				if (keyNodeIt != jsonIndexValue.end() && valueNodeIt != jsonIndexValue.end())
				{
					rttr::variant keyVariant = DeserializeValue(view.get_key_type(), *keyNodeIt);
					rttr::variant valueVariant = DeserializeValue(view.get_value_type(), *valueNodeIt);
					if (keyVariant.is_valid() && valueVariant.is_valid())
					{
						view.insert(keyVariant, valueVariant);
					}
				}
			}
			else
			{
				rttr::variant extractedValue = DeserializePrimitive(jsonIndexValue);
				if (extractedValue && extractedValue.convert(view.get_key_type()))
				{
					view.insert(extractedValue);
				}
			}
		}
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
				rttr::variant var{};
				if (valueType.is_sequential_container())
				{
					var = prop.get_value(currentInst);
					rttr::variant_sequential_view view = var.create_sequential_view();
					DeserializeArray(view, propNode);
				}
				else if (valueType.is_associative_container())
				{
					var = prop.get_value(currentInst);
					rttr::variant_associative_view view = var.create_associative_view();
					DeserializeAssociativeContainer(view, propNode);
				}

				prop.set_value(currentInst, var);
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