#pragma once 

#include "Array.hpp"

namespace YAWN {
    template<typename T = Id>
    class Pool {
    public:
        T Acquire() {
            if (_disposed == ~0) {
                return T(_data.Add(_data.Size()));
            }

            usize recycled = _disposed;
            _disposed = _data[_disposed];
            return T(_data[recycled] = recycled);
        }

        void Dispose(T id) {
            Assert(IsValid(id));

            _data[usize(id)] = _disposed;
            _disposed = usize(id);
        }

        template<typename Func>
        void Each(Func func) {
            for (usize i = 0, size = _data.Size(); i < size; ++i) {
                if (_data[i] == i) {
                    func(T(i));
                }
            }
        }

        bool IsValid(T id) {
            return usize(id) < _data.Size() && _data[usize(id)] == usize(id);
        }

        usize Size() const {
            return _data.Size();
        }

    private:
        Array<usize> _data;
        usize _disposed = ~0;
    };
}
