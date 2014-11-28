#pragma once

#include <entity/Entity.h>
#include <scripting/LuaReference.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <map>
#include <string>
#include <typeindex>

#include <lua.hpp>

using namespace ca2d;

namespace ca2d
{
    inline void testcmp(LuaReference other)
    {
        std::unique_ptr<LuaComponent> cmp = std::make_unique<LuaComponent>(other);

        cmp->update(1.0f);
    }

    inline void addComponent(LuaReference ref)
    {
        printf("got lua ref: %d\n", ref.getReference());

        lua_State* luaState = ref.getLuaState();

        // Get lua table on top of stack
        lua_rawgeti(luaState, LUA_REGISTRYINDEX, ref.getReference());

        bool istable = lua_istable(luaState, -1);

        if (!istable)
        {
            fprintf(stderr, "not a table\n");

            // Pop table
            lua_pop(luaState, 1);

            return;
        }

        lua_pushstring(luaState, "test");
        lua_gettable(luaState, -2);

        if (!lua_isfunction(luaState, -1))
        {
            fprintf(stderr, "no such function: test\n");

            // Pop value and table
            lua_pop(luaState, 2);

            return;
        }

        if (lua_pcall(luaState, 0, 0, 0) != 0)
        {
            fprintf(stderr, "error running function: %s\n", lua_tostring(luaState, -1));

            // Pop error
            lua_pop(luaState, 1);
        }

        // Pop table
        lua_pop(luaState, 1);
    }
}

struct Position
    : public Component
{

    Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    float x, y;

};
DECLARE_COMPONENT(Position)

struct Color
    : public Component
{

    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f) : r(r), g(g), b(b) {}

    float r, g, b;

};
DECLARE_COMPONENT(Color)

struct MouseFollow
    : public Component
{

    void update(float dt) override
    {
        Position* p = getEntity()->getComponent<Position>();

        if (p != nullptr)
        {
            static float w = 800;
            static float h = 600;

            int x, y;
            SDL_GetMouseState(&x, &y);

            p->x = x / (w * 0.5f) - 1.0f;
            p->y = 1.0f - y / (h * 0.5f);

            // Fix for aspect ratio
            p->x *= w / h;
        }
    }

};
DECLARE_COMPONENT(MouseFollow)

struct Velocity
    : public Component
{

    Velocity(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    void update(float dt) override
    {
        Position* p = getEntity()->getComponent<Position>();

        if (p != nullptr)
        {
            p->x += x * dt;
            p->y += y * dt;
        }
    }

    float x, y;

};
DECLARE_COMPONENT(Velocity)

struct Radius
    : public Component
{

    Radius(float v = 0.5f) : v(v) {}

    float v;

};
DECLARE_COMPONENT(Radius)

class CircleRenderer
    : public Component
{
public:

    /** Render a circle at position */
    void render() override
    {
        const Position defaultPosition;
        const Radius defaultRadius;
        const Color defaultColour(1.0f, 1.0f, 1.0f);

        const Position* p = getEntity()->getComponent<Position>();
        const Radius* r = getEntity()->getComponent<Radius>();
        const Color* c = getEntity()->getComponent<Color>();

        if (p == nullptr)
            p = &defaultPosition;

        if (r == nullptr)
            r = &defaultRadius;

        if (c == nullptr)
            c = &defaultColour;

        // Render circle if this entity has a position
        {
            // Vertex buffer
            // 2 points for each division, 1 extra division so it wraps around
            static bool init = false;
            const int DIVISIONS = 32;
            static float vertices[(DIVISIONS + 1) * 2];

            if (!init)
            {
                init = true;

                // Generate vertices for unit sphere
                for (int i = 0; i < DIVISIONS; ++i)
                {
                    // Angle around in radians
                    float angle = (i / (float)DIVISIONS) * (2.0f * 3.141592653f);

                    // * 0.5 to generate a circle of diameter 1.0
                    vertices[i * 2 + 0] = sin(angle) * 0.5f;
                    vertices[i * 2 + 1] = cos(angle) * 0.5f;
                }

                // Wrap around vertices
                vertices[DIVISIONS * 2 + 0] = vertices[0];
                vertices[DIVISIONS * 2 + 1] = vertices[1];
            }

            int vertexElements = sizeof(vertices);

            glDisable(GL_CULL_FACE);

            glColor3f(c->r, c->g, c->b);

            glPushMatrix();
            glTranslatef(p->x, p->y, 0.0f);
            glScalef(2.0f * r->v, 2.0f * r->v, 1.0f);

            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glDrawArrays(GL_TRIANGLE_FAN, 0, DIVISIONS + 1);

            glPopMatrix();
        }
    }

};
DECLARE_COMPONENT(CircleRenderer)

class CircleCollider
    : public Component
{
public:

    /** Render a circle at position */
    void render() override
    {
        const Radius defaultRadius;

        Position* p = getEntity()->getComponent<Position>();
        Velocity* v = getEntity()->getComponent<Velocity>();
        const Radius* r = getEntity()->getComponent<Radius>();

        if (r == nullptr)
            r = &defaultRadius;

        // Render circle if this entity has a position
        if (p != nullptr && v != nullptr)
        {
            // Window width and height
            static float w = 800;
            static float h = 600;

            // Viewport max x and y (negative max too)
            float vw = 1.0f * w / h;
            float vh = 1.0f;

            // Check collision
            if (p->x + r->v > vw)
            {
                p->x = vw - r->v;
                v->x *= -1.0f;
            }

            if (p->x - r->v < -vw)
            {
                p->x = r->v - vw;
                v->x *= -1.0f;
            }

            if (p->y + r->v > vh)
            {
                p->y = vh - r->v;
                v->y *= -1.0f;
            }

            if (p->y - r->v < -vh)
            {
                p->y = r->v - vh;
                v->y *= -1.0f;
            }
        }
    }

};
DECLARE_COMPONENT(CircleCollider)