#pragma once 

#include "Map.hpp"
#include "String.hpp"
#include "Managed.hpp"
#include "Variant.hpp"
#include "TypeInfo.hpp"
#include "TypeTraits.hpp"

namespace YAWN {
    class TypeField {
    public:
        void (*Setter)(void*, const Variant&) = nullptr;
        void (*Getter)(const void*, Variant&) = nullptr;
    };

    class Type {
    public:
        Map<String, TypeField> Fields;
    };

    class TypeDB {
    public:
        template<typename T>
        static Type& Fetch() {
            constexpr usize typeId = TypeId<T>();
            return _types[typeId];
        }

    private:
        static Map<usize, Type> _types;
    };

    template<typename T>
    class Meta {
    public:
        template<auto VField>
        Meta<T>& Field(const String& name) {
            TypeField field;
            field.Setter = [](void* pointer, const Variant& value) {
                (((T*)pointer)->*VField) = value;
            };
            field.Getter = [](const void* pointer, Variant& value) {
                value = (((const T*)pointer)->*VField);
            };
            _type.Fields.Add(name, field);
            return *this;
        }

        template<auto VSetter, auto VGetter>
        Meta<T>& Field(const String& name) {
            TypeField field;
            field.Setter = [](void* pointer, const Variant& value) {
                (((T*)pointer)->*VSetter)(value);
            };
            field.Getter = [](const void* pointer, Variant& value) {
                value = (((const T*)pointer)->*VGetter)();
            };
            _type.Fields.Add(name, field);
            return *this;
        }

    private:
        Type& _type = TypeDB::Fetch<T>();
    };
}
