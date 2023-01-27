#pragma once 

#include "Pool.hpp"

namespace YAWN {
    template<typename T, typename TId = Id>
    class Arena {
    public:
        Arena() = default;

        Arena(const Arena<T, TId>&) = delete;

        Arena(Arena<T, TId>&&) = delete;

        ~Arena() {
            _pool.Each([this](TId id) {
                DestroyAt(_data[usize(id)].Data());
            });
        }

        Arena<T, TId>& operator=(const Arena<T, TId>&) = delete;

        Arena<T, TId>& operator=(Arena<T, TId>&&) = delete;

        T& operator[](TId id) {
            Assert(IsValid(id));
            return *_data[usize(id)].Data();
        }

        const T& operator[](TId id) const {
            Assert(IsValid(id));
            return *_data[usize(id)].Data();
        }

        template<typename... Args>
        TId Create(Args&&... args) {
            TId id = _pool.Acquire();

            if (usize(id) == _data.Size()) {
                _data.Add(AlignedStorage<T>());
            }

            ConstructAt(_data[usize(id)].Data(), Forward<Args>(args)...);

            return id;
        }

        void Destroy(TId id) {
            Assert(IsValid(id));

            DestroyAt(_data[usize(id)].Data());

            _pool.Dispose(id);
        }

        bool IsValid(TId id) {
            return _pool.IsValid(id);
        }

        const T* Data() const {
            return (T*)_data.Data();
        }

        usize MaxSize() const {
            return _pool.Size();
        }

    private:
        Pool<TId> _pool;
        Array<AlignedStorage<T>> _data;
    };
}
