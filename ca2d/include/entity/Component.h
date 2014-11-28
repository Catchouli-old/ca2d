#pragma once

/** Macro for registering component with swig */
#ifdef SWIG

    #define DECLARE_COMPONENT(x) \
        %template(addComponent) ca2d::Entity::addComponent< ## x ##>; \
        %template(getComponent) ca2d::Entity::getComponent< ## x ##>; \
        %template(removeComponent) ca2d::Entity::removeComponent< ## x ##>;

#else
    #define DECLARE_COMPONENT(x)
#endif

namespace ca2d
{
    class Entity;

    /**
    *   \brief The base class of components
    *
    *   Components are added to entities in order to attach data to them or
    *   give them behaviours. A custom component can be defined by subclassing
    *   this type, and then Entity::addComponent can be called with it.
    *
    *   In order for a component type to be available in lua, after the class
    *   definition the macro DECLARE_COMPONENT(type) must follow, where type
    *   is the component type you wish to expose.
    */
    class Component
    {
    public:

        virtual void update(float dt) {}
        virtual void render() {}

    protected:

        /* Get the entity this component belongs to */
        Entity* getEntity() const;

    private:

        friend class Entity;

        /** Set the entity this component belongs to */
        void setEntity(Entity* ent);

        /** The entity this component belongs to */
        Entity* mEntity;
        
    };

    /* Get the entity this component belongs to */
    inline Entity* Component::getEntity() const
    {
        return mEntity;
    }

    /* Set the entity this component belongs to */
    inline void Component::setEntity(Entity* ent)
    {
        mEntity = ent;
    }
}