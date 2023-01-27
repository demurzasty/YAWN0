#pragma once 

#include "Map.hpp"
#include "Tuple.hpp"
#include "Array.hpp"
#include "String.hpp"
#include "ArrayView.hpp"
#include "Managed.hpp"
#include "TypeInfo.hpp"
#include "Component.hpp"

namespace YAWN {
    class Actor : public Reference {
    public:
        void Update(float timeStep);

        void AddChild(Managed<Actor> child);

        template<typename TComponent, typename... TArgs>
        Managed<TComponent> AddComponent(TArgs&&... args) {
            constexpr usize typeId = TypeId<TComponent>();

            Assert(!_components.Contains(typeId));

            TComponent* component = new TComponent(Forward<TArgs>(args)...);
            _components.Add(typeId, component);
            return component;
        }

        template<typename TComponent>
        bool HasComponent() {
            constexpr usize typeId = TypeId<TComponent>();

            return _components.Contains(typeId);
        }

        template<typename... TComponents>
        bool HasComponents() {
            return (HasComponent<TComponents>() && ...);
        }

        template<typename TComponent>
        Managed<TComponent> GetComponent() const {
            constexpr usize typeId = TypeId<TComponent>();

            return CastTo<TComponent>(_components[typeId]);
        }

        template<typename... TComponents>
        Tuple<Managed<TComponents>...> GetComponents() const {
            return { GetComponent<TComponents>()... };
        }

        Managed<Actor> Parent() const;

        ArrayView<const Managed<Actor>> Children() const;

        void SetName(const String& name);

        const String& Name() const;

    private:
        Actor* _parent = nullptr;
        Array<Managed<Actor>> _children;
        String _name;
        Map<usize, Managed<Component>> _components;
    };
}
