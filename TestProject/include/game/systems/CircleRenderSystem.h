#pragma once

#include <coment/systems/EntityProcessingSystem.h>

#include "../components/Position.h"
#include "../components/Radius.h"
#include "../components/Color.h"
#include "../components/CircleRenderer.h"

class CircleRenderSystem
    : public coment::EntityProcessingSystem
{
public:

    CircleRenderSystem()
    {

    }

    void registerComponents()
    {
        registerComponent<Position>();
        registerComponent<Radius>();
        registerComponent<Color>();
        registerComponent<CircleRenderer>();
    }

    /** Render a circle at position */
    void process(const coment::Entity& e) override
    {
        const Position* p = _world->getComponent<Position>(e);
        const Radius* r = _world->getComponent<Radius>(e);
        const Color* c = _world->getComponent<Color>(e);

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