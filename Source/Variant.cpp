#include <YAWN/Variant.hpp>

using namespace YAWN;

Variant Variant::MakeArray() {
    Variant variant;
    variant._type = VariantType::Array;
    ConstructAt(variant._data.Data<Array<Variant>>());
    return variant;
}

Variant Variant::MakeMap() {
    Variant variant;
    variant._type = VariantType::Map;
    ConstructAt(variant._data.Data<Map<String, Variant>>());
    return variant;
}

Variant::Variant()
    : _type(VariantType::Null), _data() {
}

Variant::Variant(decltype(nullptr))
    : _type(VariantType::Null), _data() {
}

Variant::Variant(bool value)
    : _type(VariantType::Boolean) {
    ConstructAt(_data.Data<bool>(), value);
}

Variant::Variant(int32 value)
    : _type(VariantType::Integer) {
    ConstructAt(_data.Data<int64>(), value);
}

Variant::Variant(int64 value)
    : _type(VariantType::Integer) {
    ConstructAt(_data.Data<int64>(), value);
}

Variant::Variant(float value)
    : _type(VariantType::FloatingPoint) {
    ConstructAt(_data.Data<double>(), value);
}

Variant::Variant(double value)
    : _type(VariantType::FloatingPoint) {
    ConstructAt(_data.Data<double>(), value);
}

Variant::Variant(const char* value)
    : _type(VariantType::String) {
    ConstructAt(_data.Data<String>(), value);
}

Variant::Variant(const String& value)
    : _type(VariantType::String) {
    ConstructAt(_data.Data<String>(), value);
}

Variant::Variant(const Color& value)
    : _type(VariantType::Color) {
    ConstructAt(_data.Data<Color>(), value);
}

Variant::Variant(const Vector2& value)
    : _type(VariantType::Vector2) {
    ConstructAt(_data.Data<Vector2>(), value);
}

Variant::Variant(const Vector3& value)
    : _type(VariantType::Vector3) {
    ConstructAt(_data.Data<Vector3>(), value);
}

Variant::Variant(const Vector4& value)
    : _type(VariantType::Vector4) {
    ConstructAt(_data.Data<Vector4>(), value);
}

Variant::Variant(const Matrix4& value)
    : _type(VariantType::Matrix4) {
    ConstructAt(_data.Data<Matrix4>(), value);
}

Variant::Variant(const Array<Variant>& value)
    : _type(VariantType::Array) {
    ConstructAt(_data.Data<Array<Variant>>(), value);
}

Variant::Variant(const Map<String, Variant>& value)
    : _type(VariantType::Map) {
    ConstructAt(_data.Data<Map<String, Variant>>(), value);
}

Variant::Variant(const Variant& variant)
    : _type(variant._type), _data() {
    switch (_type) {
        case VariantType::Boolean: ConstructAt(_data.Data<bool>(), (bool)variant); break;
        case VariantType::Integer: ConstructAt(_data.Data<int64>(), (int64)variant); break;
        case VariantType::FloatingPoint: ConstructAt(_data.Data<double>(), (double)variant); break;
        case VariantType::String: ConstructAt(_data.Data<String>(), (String)variant); break;
        case VariantType::Color: ConstructAt(_data.Data<Color>(), (Color)variant); break;
        case VariantType::Vector2: ConstructAt(_data.Data<Vector2>(), (Vector2)variant); break;
        case VariantType::Vector3: ConstructAt(_data.Data<Vector3>(), (Vector3)variant); break;
        case VariantType::Vector4: ConstructAt(_data.Data<Vector4>(), (Vector4)variant); break;
        case VariantType::Matrix4: ConstructAt(_data.Data<Matrix4>(), (Matrix4)variant); break;
        case VariantType::Array: ConstructAt(_data.Data<Array<Variant>>(), (Array<Variant>)variant); break;
        case VariantType::Map: ConstructAt(_data.Data<Map<String, Variant>>(), (Map<String, Variant>)variant); break;
    }
}

Variant::Variant(Variant&& variant) noexcept
    : _type(variant._type), _data(variant._data) {
    variant._type = VariantType::Null;
}

Variant::~Variant() {
    Reset();
}

Variant& Variant::operator=(const Variant& variant) {
    Reset();

    _type = variant._type;

    switch (_type) {
        case VariantType::Boolean: ConstructAt(_data.Data<bool>(), (bool)variant); break;
        case VariantType::Integer: ConstructAt(_data.Data<int64>(), (int64)variant); break;
        case VariantType::FloatingPoint: ConstructAt(_data.Data<double>(), (double)variant); break;
        case VariantType::String: ConstructAt(_data.Data<String>(), (String)variant); break;
        case VariantType::Color: ConstructAt(_data.Data<Color>(), (Color)variant); break;
        case VariantType::Vector2: ConstructAt(_data.Data<Vector2>(), (Vector2)variant); break;
        case VariantType::Vector3: ConstructAt(_data.Data<Vector3>(), (Vector3)variant); break;
        case VariantType::Vector4: ConstructAt(_data.Data<Vector4>(), (Vector4)variant); break;
        case VariantType::Matrix4: ConstructAt(_data.Data<Matrix4>(), (Matrix4)variant); break;
        case VariantType::Array: ConstructAt(_data.Data<Array<Variant>>(), (Array<Variant>)variant); break;
        case VariantType::Map: ConstructAt(_data.Data<Map<String, Variant>>(), (Map<String, Variant>)variant); break;
    }

    return *this;
}

Variant& Variant::operator=(Variant&& variant) noexcept {
    Reset();

    _type = variant._type;
    _data = variant._data;

    variant._type = VariantType::Null;
    return *this;
}

Variant& Variant::operator[](usize index) {
    Assert(_type == VariantType::Array);
    return (*_data.Data<Array<Variant>>())[index];
}

const Variant& Variant::operator[](usize index) const {
    Assert(_type == VariantType::Array);
    return (*_data.Data<Array<Variant>>())[index];
}

Variant& Variant::operator[](const String& key) {
    Assert(_type == VariantType::Map);
    return (*_data.Data<Map<String, Variant>>())[key];
}

const Variant& Variant::operator[](const String& key) const {
    Assert(_type == VariantType::Map);
    return (*_data.Data<Map<String, Variant>>())[key];
}

Variant::operator bool() const {
    Assert(_type == VariantType::Boolean);
    return *_data.Data<bool>();
}

Variant::operator int32() const {
    Assert(_type == VariantType::Integer);
    return int32(*_data.Data<int64>());
}

Variant::operator int64() const {
    Assert(_type == VariantType::Integer);
    return *_data.Data<int64>();
}

Variant::operator float() const {
    Assert(_type == VariantType::FloatingPoint);
    return float(*_data.Data<double>());
}

Variant::operator double() const {
    Assert(_type == VariantType::FloatingPoint);
    return *_data.Data<double>();
}

Variant::operator const String& () const {
    Assert(_type == VariantType::String);
    return *_data.Data<String>();
}

Variant::operator const Color& () const {
    Assert(_type == VariantType::Color);
    return *_data.Data<Color>();
}

Variant::operator const Vector2& () const {
    Assert(_type == VariantType::Vector2);
    return *_data.Data<Vector2>();
}

Variant::operator const Vector3& () const {
    Assert(_type == VariantType::Vector3);
    return *_data.Data<Vector3>();
}

Variant::operator const Vector4& () const {
    Assert(_type == VariantType::Vector4);
    return *_data.Data<Vector4>();
}

Variant::operator const Matrix4& () const {
    Assert(_type == VariantType::Matrix4);
    return *_data.Data<Matrix4>();
}

Variant::operator const Array<Variant>& () const {
    Assert(_type == VariantType::Array);
    return *_data.Data<Array<Variant>>();
}

Variant::operator const Map<String, Variant>& () const {
    Assert(_type == VariantType::Map);
    return *_data.Data<Map<String, Variant>>();
}

void Variant::Reset() {
    switch (_type) {
        case VariantType::Boolean: DestroyAt(_data.Data<bool>()); break;
        case VariantType::Integer: DestroyAt(_data.Data<int64>()); break;
        case VariantType::FloatingPoint: DestroyAt(_data.Data<double>()); break;
        case VariantType::String: DestroyAt(_data.Data<String>()); break;
        case VariantType::Color: DestroyAt(_data.Data<Color>()); break;
        case VariantType::Vector2: DestroyAt(_data.Data<Vector2>()); break;
        case VariantType::Vector3: DestroyAt(_data.Data<Vector3>()); break;
        case VariantType::Vector4: DestroyAt(_data.Data<Vector4>()); break;
        case VariantType::Matrix4: DestroyAt(_data.Data<Matrix4>()); break;
        case VariantType::Array: DestroyAt(_data.Data<Array<Variant>>()); break;
        case VariantType::Map: DestroyAt(_data.Data<Map<String, Variant>>()); break;
    }
    _type = VariantType::Null;
}

VariantType Variant::Type() const {
    return _type;
}
