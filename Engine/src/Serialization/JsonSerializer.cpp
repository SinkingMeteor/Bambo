#include "Serialization/JsonSerializer.h"


namespace
{
    void ToJsonInternal(const rttr::instance& instance, nlohmann::json& jsonNode);
    bool SerializePrimitive(const rttr::type& type, const rttr::variant& variant, nlohmann::json& jsonNode);
    bool SerializeVariant(const rttr::variant& variant, nlohmann::json& jsonNode);

    void SerializeSequentialContainer(const rttr::variant_sequential_view& view, nlohmann::json& jsonNode)
    {
        jsonNode = nlohmann::json::array({});

        for (const auto& item : view)
        {
            if (item.is_sequential_container())
            {
                jsonNode.push_back(nlohmann::json::array());
                SerializeSequentialContainer(item.create_sequential_view(), jsonNode.back());
            }
            else
            {
                rttr::variant wrappedVariant = item.extract_wrapped_value();
                rttr::type valueType = wrappedVariant.get_type();
                jsonNode.push_back({});

                if (valueType.is_arithmetic() || valueType == rttr::type::get<std::string>() || valueType.is_enumeration())
                {
                    SerializePrimitive(valueType, wrappedVariant, jsonNode.back());
                }
                else 
                {
                    ToJsonInternal(wrappedVariant, jsonNode.back());
                }
            }
        }
    }

    void SerializeAssociativeContainer(const rttr::variant_associative_view& view, nlohmann::json& jsonNode)
    {
        static const rttr::string_view key_name("key");
        static const rttr::string_view value_name("value");

        jsonNode = nlohmann::json::array({});

        if (view.is_key_only_type())
        {
            for (auto& item : view)
            {
                SerializeVariant(item.first, jsonNode);
            }
        }
        else
        {
            for (auto& item : view)
            {
                jsonNode.push_back({});
                SerializeVariant(item.first, jsonNode.back()[key_name.data()]);
                SerializeVariant(item.second, jsonNode.back()[value_name.data()]);
            }
        }

    }

    bool SerializePrimitive(const rttr::type& type, const rttr::variant& variant, nlohmann::json& jsonNode)
    {
        bool isArray = jsonNode.is_array();

        if (type.is_arithmetic())
        {
            if (type == rttr::type::get<bool>())
                isArray ? jsonNode.push_back(variant.to_bool()) : jsonNode = variant.to_bool();
            else if (type == rttr::type::get<char>())
                isArray ? jsonNode.push_back(variant.to_bool()) : jsonNode = variant.to_bool();
            else if (type == rttr::type::get<int8_t>())
                isArray ? jsonNode.push_back(variant.to_int8()) : jsonNode = variant.to_int8();
            else if (type == rttr::type::get<int16_t>())
                isArray ? jsonNode.push_back(variant.to_int16()) : jsonNode = variant.to_int16();
            else if (type == rttr::type::get<int32_t>())
                isArray ? jsonNode.push_back(variant.to_int32()) : jsonNode = variant.to_int32();
            else if (type == rttr::type::get<int64_t>())
                isArray ? jsonNode.push_back(variant.to_int64()) : jsonNode = variant.to_int64();
            else if (type == rttr::type::get<uint8_t>())
                isArray ? jsonNode.push_back(variant.to_uint8()) : jsonNode = variant.to_uint8();
            else if (type == rttr::type::get<uint16_t>())
                isArray ? jsonNode.push_back(variant.to_uint16()) : jsonNode = variant.to_uint16();
            else if (type == rttr::type::get<uint32_t>())
                isArray ? jsonNode.push_back(variant.to_uint32()) : jsonNode = variant.to_uint32();
            else if (type == rttr::type::get<uint64_t>())
                isArray ? jsonNode.push_back(variant.to_uint64()) : jsonNode = variant.to_uint64();
            else if (type == rttr::type::get<float>())
                isArray ? jsonNode.push_back(variant.to_double()) : jsonNode = variant.to_double();
            else if (type == rttr::type::get<double>())
                isArray ? jsonNode.push_back(variant.to_double()) : jsonNode = variant.to_double();
            return true;
        }
        
        if (type.is_enumeration())
        {
            bool ok = false;
            std::string result = variant.to_string(&ok);
            if (ok)
            {
                isArray ? jsonNode.push_back(variant.to_string()) : jsonNode = variant.to_string();
            }
            else
            {
                ok = false;
                auto value = variant.to_uint64(&ok);
                if (ok)
                    isArray ? jsonNode.push_back(variant.to_uint64()) : jsonNode = variant.to_uint64();
                else
                    isArray ? jsonNode.push_back(variant.to_uint64()) : jsonNode = "";
            }
            return true;
        }
        
        if (type == rttr::type::get<std::string>())
        {
            isArray ? jsonNode.push_back(variant.to_string()) : jsonNode = variant.to_string();
            return true;
        }
        
        return false;
    }

    bool SerializeVariant(const rttr::variant& variant, nlohmann::json& jsonNode)
    {
        bool isArray = jsonNode.is_array();

        rttr::type variantType = variant.get_type();
        rttr::type wrappedType = variantType;
        if (variantType.is_wrapper())
        {
            wrappedType = variantType.get_wrapped_type();
        }
        bool isWrapped = variantType != wrappedType;

        if (SerializePrimitive(isWrapped ? wrappedType : variantType, isWrapped ? variant.extract_wrapped_value() : variant, jsonNode))
        {
            return true;
        }
        if (variant.is_sequential_container())
        {
            SerializeSequentialContainer(variant.create_sequential_view(), jsonNode);
            return true;
        }
        if (variant.is_associative_container())
        {
            SerializeAssociativeContainer(variant.create_associative_view(), jsonNode);
            return true;
        }

        auto childProps = isWrapped ? wrappedType.get_properties() : variantType.get_properties();
        if (!childProps.empty())
        {
            if (isArray)
            {
                jsonNode.push_back({});
                ToJsonInternal(variant, jsonNode.back());
            }
            else
            {
                ToJsonInternal(variant, jsonNode);
            }
        }
        else
        {
            bool ok = false;
            std::string text = variant.to_string(&ok);
            if (!ok)
            {
                isArray ? jsonNode.push_back(text) : jsonNode = text;
                return false;
            }

            isArray ? jsonNode.push_back(text) : jsonNode = text;
        }
    }

	void ToJsonInternal(const rttr::instance& instance, nlohmann::json& jsonNode)
	{
		rttr::instance currentInstance = instance.get_type().get_raw_type().is_wrapper() ? instance.get_wrapped_instance() : instance;

        auto propList = currentInstance.get_derived_type().get_properties();
        for (auto prop : propList)
        {
            if (prop.get_metadata("NO_SERIALIZE"))
                continue;

            rttr::variant propValue = prop.get_value(currentInstance);
            if (!propValue)
                continue;

            if (jsonNode.is_array())
            {
                if (!SerializeVariant(propValue, jsonNode))
                {
                    Bambo::Logger::Get()->Log("JsonSerializerLog", Bambo::Verbosity::Error, "Can't serialize property with name %s", jsonNode);
                }
            }
            else
            {
                const rttr::string_view name = prop.get_name();

                if (!SerializeVariant(propValue, jsonNode[name.data()]))
                {
                    Bambo::Logger::Get()->Log("JsonSerializerLog", Bambo::Verbosity::Error, "Can't serialize property with name %s", name.data());
                }
            }
        }
	}
}

namespace Bambo
{
	void ToJson(rttr::instance& instance, nlohmann::json& jsonNode)
	{
		if (!instance.is_valid())
		{
			return;
		}

		ToJsonInternal(instance, jsonNode);
	}
}
