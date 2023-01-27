#pragma once 

#include "Array.hpp"

namespace YAWN {
    template<typename TKey, typename TValue>
    class Map {
    public:
        Pair<TKey, TValue>& Add(const TKey& key, const TValue& value) {
            usize index = BinarySearch(key);
            Assert(index >= Size() || _data[index].First != key);
            return _data.Insert(index, { key, value });
        }

        TValue& operator[](const TKey& key) {
            usize index = BinarySearch(key);
            if (index < Size() && _data[index].First == key) {
                return _data[index].Second;
            }
            return Add(key, TValue()).Second;
        }

        const TValue& operator[](const TKey& key) const {
            usize index = BinarySearch(key);
            Assert(index < Size() && _data[index].First == key);
            return _data[index].Second;
        }

        void Remove(const TKey& key) {
            const usize index = BinarySearch(key);
            if (index < Size() && _data[index].First == key) {
                _data.RemoveAt(index);
            }
        }

        bool Contains(const TKey& key) const {
            const usize index = BinarySearch(key);
            return index < Size() && _data[index].First == key;
        }

        void Clear() {
            _data.Clear();
        }

        usize Size() const {
            return _data.Size();
        }

    public:
        Pair<TKey, TValue>* begin() {
            return _data.begin();
        }

        Pair<TKey, TValue>* end() {
            return _data.end();
        }

        const Pair<TKey, TValue>* begin() const {
            return _data.begin();
        }

        const Pair<TKey, TValue>* end() const {
            return _data.end();
        }

    private:
        usize BinarySearch(const TKey& key) const {
            if (Size() == 0) {
                return 0;
            }

            int64 low = 0;
            int64 high = int64(Size() - 1);
            while (low <= high) {
                const int64 mid = (low + high) / 2;
                if (key == _data[mid].First) {
                    return mid;
                } else if (key > _data[mid].First) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            return usize(low);
        }

    private:
        Array<Pair<TKey, TValue>> _data;
    };
}
