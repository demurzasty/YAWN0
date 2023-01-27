#pragma once 

#include "Reference.hpp"
#include "TypeTraits.hpp"

namespace YAWN {
    template<typename TReference>
    class Managed {
    public:
        Managed() = default;

        Managed(TReference * reference)
            : _reference(reference) {
            Retain();
        }

        Managed(const Managed<TReference>&managed)
            : _reference(managed._reference) {
            Retain();
        }

        Managed(Managed<TReference> && managed) noexcept
            : _reference(managed._reference) {
            managed._reference = nullptr;
        }

        ~Managed() {
            Release();
        }

        Managed<TReference>& operator=(const Managed<TReference>&managed) {
            Release();
            _reference = managed._reference;
            Retain();
            return *this;
        }

        Managed<TReference>& operator=(Managed<TReference> && managed) noexcept {
            Release();
            _reference = managed._reference;
            managed._reference = nullptr;
            return *this;
        }

        void Reset() {
            *this = Managed<TReference>();
        }

        bool HasReference() const {
            return _reference != nullptr;
        }

        TReference& operator*() {
            return *_reference;
        }

        TReference* operator->() const {
            return _reference;
        }

        TReference* Get() const {
            return _reference;
        }

        operator TReference* () const {
            return _reference;
        }

        bool operator==(const Managed<TReference>&managed) const {
            return _reference == managed._reference;
        }

        bool operator!=(const Managed<TReference>&managed) const {
            return _reference != managed._reference;
        }

    private:
        void Retain() {
            if (_reference) {
                _reference->Retain();
            }
        }

        void Release() {
            if (_reference) {
                _reference->Release();
            }
        }

    private:
        TReference* _reference = nullptr;
    };


    template<typename T1, typename T2>
    inline Managed<T1> CastTo(const Managed<T2>& managed) {
        return dynamic_cast<T1*>(managed.Get());
    }
}
