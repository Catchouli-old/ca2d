#version 100

precision mediump float;

#define MAX_BOUNCES 4 /* The number of times the primary ray can bounce around the scene */
#define SAMPLES_X 1
#define SAMPLES_Y 1 /* Total samples per pixel = SAMPLES_X * SAMPLE_Y */

varying vec3 vertex_pos;

uniform vec3 in_position;
uniform mat4 in_rotation;

struct Sphere
{
	vec3 center;
	float radius;
	vec3 col;
};

struct Box
{
	vec3 min, max;
};

struct Plane
{
	vec3 point, normal, col;
};

struct Quad
{
	vec3 a, b, c, d;	// Normal vertices in clockwise order
	vec3 normal, col;
};

struct HitResult
{
    float t;
    vec3 pos;
    vec3 normal;
    vec3 col;
    float reflectiveness;
};

HitResult trace(vec3 origin, vec3 dir, float tmax);
//float rand(in vec2 co);
Box boxFromCentreExtents(vec3 centre, vec3 extents);
float rayIntersectsSphere(vec3 origin, vec3 dir, vec3 center, float radius, float closestHit);
float rayIntersectsBox(vec3 origin, vec3 dir, vec3 boxmin, vec3 boxmax, float closestHit);
float rayIntersectsPlane(vec3 origin, vec3 dir, vec3 point, vec3 normal, float closestHit);
float rayIntersectsQuad(vec3 origin, vec3 dir,
	vec3 a, vec3 b, vec3 c, vec3 d,
    vec3 normal, float closestHit);

highp float rand(in vec2 co)
{
    co.x += 7.0 * 0.0;
    co.y += 13.0 * 0.0;

    highp float a = 12.9898;
    highp float b = 78.233;
    highp float c = 43758.5453;
    highp float dt = dot(co.xy, vec2(a, b));
    highp float sn = mod(dt, 3.14);
    return fract(sin(sn) * c);
}

const int sphereCount = 2;
    
   Sphere sphere1 = Sphere(vec3(1.5, 0, 1), 1.0, vec3(0.3, 0.3, 0.3));
  Sphere sphere2 = Sphere(vec3(-1.5, 0, -1), 1.0, vec3(0.3, 0.3, 0.3));

const int quadCount = 6;

// Cornell box
Quad quad1 =	Quad(vec3(-5, -5, -5), vec3(5, -5, -5), vec3(5, 5, -5), vec3(-5, 5, -5),	// Front
		vec3(0, 0, 1),
		vec3(0.75, 0.75, 0.75));
Quad quad2 =	Quad(vec3(-5, -5, 5), vec3(5, -5, 5), vec3(5, 5, 5), vec3(-5, 5, 5),		// Back
		vec3( 0, 0, -1),
		vec3(0.0, 0.0, 0.0));
Quad quad3 =	Quad(vec3(-5, -5, -5), vec3(-5, 5, -5), vec3(-5, 5, 5), vec3(-5, -5, 5),	// Left
		vec3(1, 0, 0),
		vec3(0.75, 0.25, 0.25));
Quad quad4 =	Quad(vec3( 5, -5, -5), vec3( 5, 5, -5), vec3( 5, 5, 5), vec3( 5, -5, 5),	// Right
		vec3(-1, 0, 0),
		vec3(0.25, 0.25, 0.75));
Quad quad5 =	Quad(vec3(-5, 5, -5), vec3(5, 5, -5), vec3(5, 5, 5), vec3(-5, 5, 5),		// Top
		vec3(0, -1, 0),
		vec3(0.75, 0.75, 0.75));
Quad quad6 =	Quad(vec3(-5, -5, -5), vec3(5, -5, -5), vec3(5, -5, 5), vec3(-5, -5, 5),	// Bottom
		vec3( 0, 1, 0),
        vec3(0.75, 0.75, 0.75));

Quad light = Quad(vec3(-1.0, 4.9, -1.0), vec3(1.0, 4.9, -1.0), vec3(1.0, 4.9, 1.0), vec3(-1.0, 4.9, 1.0),
                vec3(0, -1, 0),
                vec3(1.0, 1.0, 1.0));

const float LARGE_VALUE = 1e20;

void main()
{
    vec2 rng_state = vec2(vertex_pos.x + 7.0 * 0.0, vertex_pos.y + 13.0 * 0.0);

    gl_FragColor = vec4(0);

	// Camera space ray
	vec3 ray_pos_camera = vec3(0, 0, 0);
	vec3 ray_dir_camera = normalize(vec3(vertex_pos.x, vertex_pos.y * 1.0, -1.0));

	// Transform to world
	vec3 ray_pos_world = ray_pos_camera + in_position;
	vec3 ray_dir_world = vec3(vec4(ray_dir_camera, 0.0) * in_rotation);

	// Do ray trace
    float dx = 1.0 / float(SAMPLES_X);
    float dy = 1.0 / float(SAMPLES_X);

    //for (float x = 0.0; x < 1.0; x += dx)
    //for (float y = 0.0; y < 1.0; y += dy)
    {
        float weight = 1.0;
        vec3 origin = ray_pos_world;
        vec3 dir = ray_dir_world;

        for (int bounce = 0; bounce < MAX_BOUNCES; ++bounce)
        {
            HitResult hit = trace(origin, dir, LARGE_VALUE);

            if (hit.t == LARGE_VALUE)
            {
                // No intersection.. black
                break;
            }
            else
            {
                // Intersection.. shade
                // Shadow ray
                // Pick random point on light
                float u = 0.0 + rand(rng_state) * 0.1;
                float v = 0.0 + rand(rng_state) * 0.1;

                vec3 p = light.a + u * (light.b - light.a) + v * (light.d - light.a);

                vec3 dirToLight = p - hit.pos;
                float dist = length(dirToLight);
                dirToLight = normalize(dirToLight);

                // Cast shadow ray
                HitResult shadowRay = trace(hit.pos + dirToLight * 0.1, dirToLight, dist);

                // If shadow ray wasn't intersected
                if (shadowRay.t == dist)
                {
                    // Add contribution from light
                    float diffuse = dot(hit.normal, dirToLight);
                    vec3 colour = vec3(dot(hit.normal, dirToLight)) * hit.col;

                    gl_FragColor += weight * vec4(colour, 1);
                }

                if (hit.reflectiveness > 0.0)
                {
                    origin = hit.pos;
                    dir = reflect(dir, hit.normal);
                    weight = hit.reflectiveness;
                }
                else
                {
                    break;
                }
            }
        }
    }
    
    gl_FragColor /= float(SAMPLES_X * SAMPLES_Y);
    gl_FragColor = clamp(gl_FragColor, 0.0, 1.0);
}

HitResult trace(vec3 origin, vec3 dir, float tmax)
{
    float tmin = tmax;
    vec3 pos;
    vec3 normal;
    vec3 col;
    float reflectiveness = 0.0;

    //for (int i = 0; i < quadCount; ++i)
    {
        float t = rayIntersectsQuad(origin, dir,
            quad1.a, quad1.b, quad1.c, quad1.d,
            quad1.normal, tmin);

        if (t < tmin)
        {
            tmin = t;
            pos = origin + dir * t;
            normal = quad1.normal;
            col = quad1.col;
            reflectiveness = 0.3;
        }
		
		        t = rayIntersectsQuad(origin, dir,
            quad2.a, quad2.b, quad2.c, quad2.d,
            quad2.normal, tmin);

        if (t < tmin)
        {
            tmin = t;
            pos = origin + dir * t;
            normal = quad2.normal;
            col = quad2.col;
            reflectiveness = 0.3;
        }
		
		        t = rayIntersectsQuad(origin, dir,
            quad3.a, quad3.b, quad3.c, quad3.d,
            quad3.normal, tmin);

        if (t < tmin)
        {
            tmin = t;
            pos = origin + dir * t;
            normal = quad3.normal;
            col = quad3.col;
            reflectiveness = 0.3;
        }
		
		        t = rayIntersectsQuad(origin, dir,
            quad4.a, quad4.b, quad4.c, quad4.d,
            quad4.normal, tmin);

        if (t < tmin)
        {
            tmin = t;
            pos = origin + dir * t;
            normal = quad4.normal;
            col = quad4.col;
            reflectiveness = 0.3;
        }
		
		        t = rayIntersectsQuad(origin, dir,
            quad5.a, quad5.b, quad5.c, quad5.d,
            quad5.normal, tmin);

        if (t < tmin)
        {
            tmin = t;
            pos = origin + dir * t;
            normal = quad5.normal;
            col = quad5.col;
            reflectiveness = 0.3;
        }
		
		        t = rayIntersectsQuad(origin, dir,
            quad6.a, quad6.b, quad6.c, quad6.d,
            quad6.normal, tmin);

        if (t < tmin)
        {
            tmin = t;
            pos = origin + dir * t;
            normal = quad6.normal;
            col = quad6.col;
            reflectiveness = 0.3;
        }
    }

    //for (int i = 0; i < sphereCount; ++i)
    {
        float t = rayIntersectsSphere(origin, dir,
            sphere1.center, sphere1.radius, LARGE_VALUE);

        if (t < LARGE_VALUE && t < tmin)
        {
            tmin = t;
            pos = origin + dir * t;
            normal = normalize(pos - sphere1.center);
            col = sphere1.col;
            reflectiveness = 0.3;
        }
		
		
        t = rayIntersectsSphere(origin, dir,
            sphere2.center, sphere2.radius, LARGE_VALUE);

        if (t < LARGE_VALUE && t < tmin)
        {
            tmin = t;
            pos = origin + dir * t;
            normal = normalize(pos - sphere2.center);
            col = sphere2.col;
            reflectiveness = 0.3;
        }
    }

    return HitResult(tmin, pos, normal, col, reflectiveness);
}

Box boxFromCentreExtents(vec3 centre, vec3 extents)
{
	vec3 min = centre - extents;
	vec3 max = centre + extents;

	return Box(min, max);
}

float rayIntersectsSphere(vec3 origin, vec3 dir, vec3 center, float radius, float closestHit)
{
	vec3 rc = origin-center;
	float c = dot(rc, rc) - (radius*radius);
	float b = dot(dir, rc);
	float d = b*b - c;
	float t = -b - sqrt(abs(d));
	if (d < 0.0 || t < 0.0 || t > closestHit)
	{
		return closestHit;
	}
	else
	{
		return t;
	}
}

float rayIntersectsBox(vec3 origin, vec3 dir, vec3 box_min, vec3 box_max, float closestHit)
{
	vec3 tmin = (box_min - origin) / dir;
	vec3 tmax = (box_max - origin) / dir;
   
	vec3 real_min = min(tmin, tmax);
	vec3 real_max = max(tmin, tmax);
   
	float minmax = min(min(real_max.x, real_max.y), real_max.z);
	float maxmin = max(max(real_min.x, real_min.y), real_min.z);

	if (minmax < maxmin)
		return closestHit;
	else
		return maxmin;
}

float rayIntersectsPlane(vec3 origin, vec3 dir, vec3 point, vec3 normal, float closestHit)
{
	// Ray plane intersection
	// http://www.yaldex.com/game-programming/0131020099_ch22lev1sec2.html
	float normalDot = dot(normal, dir);

	// Check if we're facing the plane's normal
	if (normalDot < 0.0)
	{
		float t = dot(normal, (point - origin)) / normalDot;

		// Check if the ray intersects the plane
		if (t > 0.0)
		{
			// Ray intersects the plane
			return t;
		}
	}

	return closestHit;
}

float rayIntersectsQuad(vec3 origin, vec3 dir,
	vec3 b, vec3 c, vec3 d, vec3 e,
	vec3 normal, float closestHit)
{
	// Ray plane intersection
	// http://www.yaldex.com/game-programming/0131020099_ch22lev1sec2.html
	float normalDot = dot(normal, dir);

	// Check if we're facing the plane's normal
	if (normalDot < 0.0)
	{
		float t = dot(normal, (b - origin)) / normalDot;

		// Check if the ray intersects the plane
		if (t > 0.0)
		{
			// Ray intersects plane, now check it's in the rectangle
			// http://math.stackexchange.com/a/476614
			vec3 a = origin + t * dir;

			float u = dot(a, c - b);
			float v = dot(b, c - b);
			float w = dot(c, c - b);
			float x = dot(a, e - b);
			float y = dot(b, e - b);
			float z = dot(e, e - b);

			if (v <= u && u <= w &&
				y <= x && x <= z)
			{
				return t;
			}
		}
	}

	return closestHit;
}