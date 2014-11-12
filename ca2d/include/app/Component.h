#pragma once

/** Macro for registering component with swig */
#ifdef SWIG

    #define DECLARE_COMPONENT(x, y) \
        %template(addComponent) ca2d::Entity::addComponent< ## x ##>; \
        %template(getComponent) ca2d::Entity::getComponent< ## x ##>; \
        %template(removeComponent) ca2d::Entity::removeComponent< ## x ##>;

#else
    #define DECLARE_COMPONENT(x, y)
#endif

namespace ca2d
{
    class Entity;

    class Component
    {
    public:

        Component(Entity* ent = nullptr) : mEntity(ent) {}

        void setEntity(Entity* ent);

        virtual void update(float dt) {}
        virtual void render() {}

    protected:

        Entity* mEntity;
        
    };

    inline void Component::setEntity(Entity* ent)
    {
        mEntity = ent;
    }
}