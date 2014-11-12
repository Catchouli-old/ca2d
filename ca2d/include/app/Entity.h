#pragma once

#include <map>
#include <memory>
#include <typeindex>

#include "Component.h"

namespace ca2d
{
    class Entity
    {
    public:

        /** Fail to add a component type to the entity - to prevent blank swig calls */
        void addComponent();

        /** Add a component to the entity */
        template <typename T>
        T* addComponent();

        /** Add a component to the entity */
        template <typename T, typename... Args>
        T* addComponent(Args... args);

        /** Add a component to the entity */
        template <typename T>
        T* addComponent(const T& other);

        /** Fail to get a component type to the entity - to prevent blank swig calls */
        void getComponent();

        /** Get a component from the entity */
        template <typename T>
        T* getComponent();

        /** Get a component from the entity (arg is unused)
        This method makes it possible to specify T from lua */
        template <typename T>
        T* getComponent(const T&);

        /** Fail to get a component type to the entity - to prevent blank swig calls */
        void removeComponent();

        /** Remove a component from the entity */
        template <typename T>
        void removeComponent();

        /** Remove a component from the entity (arg is unused)
        This method makes it possible to specify T from lua */
        template <typename T>
        void removeComponent(const T&);

        /** Update this entity */
        void update(float dt);

        /** Render this entity */
        void render();

    private:

        /** The components this entity has */
        std::map<std::type_index, std::unique_ptr<Component>> mComponents;

    };

    /** Fail to add a component type to the entity - to prevent blank swig calls */
    inline void Entity::addComponent()
    {
        fprintf(stderr, "addComponent() - No component type specified.\n");
    }

    /** Add a component to the entity */
    template <typename T>
    T* Entity::addComponent()
    {
        T* ptr = new T();
        ptr->setEntity(this);

        mComponents[typeid(T)] = std::unique_ptr<T>(ptr);

        return ptr;
    }

    /** Add a component to the entity */
    template <typename T, typename... Args>
    T* Entity::addComponent(Args... args)
    {
        T* ptr = new T(args...);
        ptr->setEntity(this);

        mComponents[typeid(T)] = std::unique_ptr<T>(ptr);

        return ptr;
    }

    /** Add a component to the entity */
    template <typename T>
    T* Entity::addComponent(const T& other)
    {
        T* ptr = new T(other);
        ptr->setEntity(this);

        mComponents[typeid(T)] = std::unique_ptr<T>(ptr);

        return ptr;
    }

    /** Fail to get a component type from the entity - to prevent blank swig calls */
    inline void Entity::getComponent()
    {
        fprintf(stderr, "getComponent() - No component type specified.\n");
    }

    /** Get a component from the entity */
    template <typename T>
    T* Entity::getComponent()
    {
        if (mComponents.find(typeid(T)) == mComponents.end())
            return nullptr;

        return static_cast<T*>(mComponents.at(typeid(T)).get());
    }

    /** Get a component from the entity (arg is unused)
       This method makes it possible to specify T from lua */
    template <typename T>
    T* Entity::getComponent(const T&)
    {
        if (mComponents.find(typeid(T)) == mComponents.end())
            return nullptr;

        return static_cast<T*>(mComponents.at(typeid(T)).get());
    }

    /** Fail to get a component type to the entity - to prevent blank swig calls */
    inline void Entity::removeComponent()
    {
        fprintf(stderr, "removeComponent() - No component type specified.\n");
    }

    /** Remove a component from the entity */
    template <typename T>
    void Entity::removeComponent()
    {
        mComponents.erase(typeid(T));
    }

    /** Remove a component from the entity (arg is unused)
    This method makes it possible to specify T from lua */
    template <typename T>
    void Entity::removeComponent(const T&)
    {
        printf("Removing component %s\n", typeid(T).name());
        mComponents.erase(typeid(T));
    }

    /** Update this entity */
    inline void Entity::update(float dt)
    {
        for (auto& comp : mComponents)
        {
            comp.second->update(dt);
        }
    }

    /** Render this entity */
    inline void Entity::render()
    {
        for (auto& comp : mComponents)
        {
            comp.second->render();
        }
    }

}