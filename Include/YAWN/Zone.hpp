#pragma once 

#include "Arena.hpp"

namespace YAWN {
    template<typename TData, typename TMeta>
    class Zone {
    public:
        Id Create() {
            uint64 dataId = (uint64)_data.Create();
            uint64 metaId = (uint64)_meta.Create();

            return Id(dataId | (metaId << 32));
        }

        void Destroy(Id id) {
            Assert(IsValid(id));

            _data.Destroy(uint32(id));
            _meta.Destroy(uint32((uint64(id) >> 32)));
        }

        bool IsValid(Id id) {
            return _data.IsValid(uint32(id)) &&
                _meta.IsValid(uint32((uint64(id) >> 32)));
        }
        
        TData& GetData(Id id) {
            Assert(IsValid(id));

            return _data[uint32(id)];
        }

        TMeta& GetMeta(Id id) {
            Assert(IsValid(id));

            return _meta[uint32((uint64(id) >> 32))];
        }

        const TData* Data() const {
            return _data.Data();
        }

        usize MaxSize() const {
            return _data.MaxSize();
        }

    private:
        Arena<TData, uint32> _data;
        Arena<TMeta, uint32> _meta;
    };
}
