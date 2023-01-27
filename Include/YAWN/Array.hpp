#pragma once 

#include "Memory.hpp"

namespace YAWN {
    template<typename T>
    class Array {
    public:
        Array() = default;

        Array(const Array<T>& array)
            : _capacity(array._size), _size(array._size) {
            if (_size > 0) {
                _data = new AlignedStorage<T>[_capacity];

                for (usize i = 0; i < _size; ++i) {
                    ConstructAt(_data[i].Data(), array[i]);
                }
            }
        }

        Array(Array<T>&& array) noexcept
            : _data(array._data), _capacity(array._capacity), _size(array._size) {
            array._data = 0;
            array._capacity = 0;
            array._size = 0;
        }

        Array(usize size)
            : _size(size), _capacity(size) {
            _data = new AlignedStorage<T>[_capacity];

            for (usize i = 0; i < _size; ++i) {
                ConstructAt(_data[i].Data(), T());
            }
        }

        Array(const T* data, usize size)
            : _size(size), _capacity(size) {
            _data = new AlignedStorage<T>[_capacity];

            for (usize i = 0; i < _size; ++i) {
                ConstructAt(_data[i].Data(), data[i]);
            }
        }

        ~Array() {
            Clear();

            delete[] _data;
        }

        Array<T>& operator=(const Array<T>& array) {
            for (usize i = 0; i < _size; ++i) {
                DestroyAt(_data[i].Data());
            }

            _size = array._size;

            if (_size > _capacity) {
                delete[] _data;
                _capacity = _size;
                _data = new AlignedStorage<T>[_capacity];
            }

            for (usize i = 0; i < _size; ++i) {
                ConstructAt(_data[i].Data(), array[i]);
            }
            return *this;
        }

        Array<T>& operator=(Array<T>&& array) noexcept {
            delete[] _data;

            _data = array._data;
            _capacity = array._capacity;
            _size = array._size;

            array._data = nullptr;
            array._capacity = 0;
            array._size = 0;
            return *this;
        }

        T& operator[](usize index) {
            Assert(index < _size);
            return *_data[index].Data();
        }

        const T& operator[](usize index) const {
            Assert(index < _size);
            return *_data[index].Data();
        }

        T& Add(const T& item) {
            EnsureCapacityGrow();

            return *ConstructAt(_data[_size++].Data(), item);
        }

        T& Add(T&& item) {
            EnsureCapacityGrow();

            return *ConstructAt(_data[_size++].Data(), Forward<T>(item));
        }

        T& Insert(usize index, const T& item) {
            Assert(index <= _size);

            EnsureCapacityGrow();

            for (usize i = _size; i > index; --i) {
                _data[i] = _data[i - 1];
            }

            ++_size;

            return *ConstructAt(_data[index].Data(), item);
        }

        T& Insert(usize index, T&& item) {
            Assert(index <= _size);

            EnsureCapacityGrow();

            for (usize i = _size; i > index; --i) {
                _data[i] = _data[i - 1];
            }

            ++_size;

            return *ConstructAt(_data[index].Data(), Forward<T>(item));
        }

        void Clear() {
            for (usize i = 0; i < _size; ++i) {
                DestroyAt(_data[i].Data());
            }
            _size = 0;
        }

        void RemoveAt(usize index) {
            if (index < _size) {
                DestroyAt(_data[index].Data());

                for (usize i = index + 1; i < _size; ++i) {
                    _data[i - 1] = _data[i];
                }

                --_size;
            }
        }

        T* Data() noexcept {
            return (T*)_data;
        }

        const T* Data() const noexcept {
            return (const T*)_data;
        }

        usize Capacity() const noexcept {
            return _capacity;
        }

        usize Size() const noexcept {
            return _size;
        }

    public:
        T* begin() noexcept { return Data(); }
        const T* begin() const noexcept { return Data(); }

        T* end() noexcept { return Data() + Size(); }
        const T* end() const noexcept { return Data() + Size(); }

    private:
        void EnsureCapacityGrow(usize space = 1) {
            usize oldCapacity = _capacity;
            while (_size + space > _capacity) {
                _capacity = (_capacity == 0) ? 1 : (_capacity << 1);
            }

            if (oldCapacity != _capacity) {
                AlignedStorage<T>* newData = new AlignedStorage<T>[_capacity];

                for (usize i = 0; i < _size; ++i) {
                    newData[i] = _data[i];
                }

                delete[] _data;
                _data = newData;
            }
        }

    private:
        AlignedStorage<T>* _data = nullptr;
        usize _capacity = 0;
        usize _size = 0;
    };
}
