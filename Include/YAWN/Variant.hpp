#pragma once 

#include "Map.hpp"
#include "Array.hpp"
#include "Config.hpp"
#include "Memory.hpp"
#include "String.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix4.hpp"
#include "TypeTraits.hpp"

namespace YAWN {
    enum class VariantType : uint8 {
        Null,
        Boolean,
        Integer,
        FloatingPoint,
        String,
        Color,
        Vector2,
        Vector3,
        Vector4,
        Matrix4,
        Array,
        Map
    };

    class Variant {
    public:
        static Variant MakeArray();

        static Variant MakeMap();

    public:
        Variant();

        Variant(decltype(nullptr));

        Variant(bool value);

        Variant(int32 value);

        Variant(int64 value);

        Variant(float value);

        Variant(double value);

        Variant(const char* value);

        Variant(const String& value);

        Variant(const Color& value);

        Variant(const Vector2& value);

        Variant(const Vector3& value);

        Variant(const Vector4& value);

        Variant(const Matrix4& value);

        Variant(const Array<Variant>& value);

        Variant(const Map<String, Variant>& value);

        Variant(const Variant& variant);

        Variant(Variant&& variant) noexcept;

        ~Variant();

        Variant& operator=(const Variant& variant);

        Variant& operator=(Variant&& variant) noexcept;

        Variant& operator[](usize index);

        const Variant& operator[](usize index) const;

        Variant& operator[](const String& key);

        const Variant& operator[](const String& key) const;

        operator bool() const;

        operator int32() const;

        operator int64() const;

        operator float() const;

        operator double() const;

        operator const String& () const;

        operator const Color& () const;

        operator const Vector2& () const;

        operator const Vector3& () const;

        operator const Vector4& () const;

        operator const Matrix4& () const;

        operator const Array<Variant>& () const;

        operator const Map<String, Variant>& () const;

        void Reset();

        VariantType Type() const;

    private:
        VariantType _type = VariantType::Null;
        AlignedUnion<bool, int64, double, String, Color, Vector2, Vector3, Vector4, Matrix4, Array<Variant>, Map<String, Variant>> _data;
    };
}
