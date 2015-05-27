#pragma once

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

enum axis{
    X_AXIS, Y_AXIS, Z_AXIS
};

typedef struct vec2 {
    double x, y;
} vec2_t;

static inline double vec2_mag2(vec2_t v)
{
    return v.x * v.x + v.y * v.y;
}

static inline double vec2_mag(vec2_t v)
{
    return sqrt(vec2_mag2(v));
}

static inline vec2_t vec2_unitize(vec2_t v)
{
    double mag = vec2_mag(v);
    return (vec2_t){v.x / mag, v.y / mag};
}

static inline double vec2_dist2(vec2_t v1, vec2_t v2)
{
    return vec2_mag2((vec2_t){v1.x - v2.x, v1.y - v2.y});
}

static inline double vec2_dist(vec2_t v1, vec2_t v2)
{
    return sqrt(vec2_dist2(v1, v2));
}

static inline double vec2_dot(vec2_t v1, vec2_t v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

static inline vec2_t vec2_sub(vec2_t v1, vec2_t v2)
{
    return (vec2_t){v1.x - v2.x, v1.y - v2.y};
}

static inline vec2_t vec2_add(vec2_t v1, vec2_t v2)
{
    return (vec2_t){v1.x + v2.x, v1.y + v2.y};
}

static inline vec2_t vec2_negate(vec2_t v)
{
    return (vec2_t){-v.x, -v.y};
}

static inline double vec2_angle(vec2_t v1, vec2_t v2)
{
    return acos(vec2_dot(vec2_unitize(v1), vec2_unitize(v2)));
}

static inline vec2_t vec2_scale(vec2_t v, double s)
{
    return (vec2_t){v.x * s, v.y * s};
}

static inline vec2_t vec2_refl(vec2_t v1, vec2_t v2)
{
    return vec2_sub(v1, vec2_scale(v2, 2 * vec2_dot(v1, v2)));
}

static inline vec2_t vec2_min(vec2_t v1, vec2_t v2)
{
    return (vec2_t){fmin(v1.x, v2.x), fmin(v1.y, v2.y)};
}

static inline vec2_t vec2_max(vec2_t v1, vec2_t v2)
{
    return (vec2_t){fmax(v1.x, v2.x), fmax(v1.y, v2.y)};
}

static inline bool vec2_equals(vec2_t v1, vec2_t v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}

static inline bool vec2_in_bounds(vec2_t min, vec2_t max, vec2_t test)
{
    return (vec2_equals(vec2_max(test, min), test) && vec2_equals(vec2_min(test, max), test));
}

static inline vec2_t vec2_proj(vec2_t v1, vec2_t v2)
{
    vec2_t v2_n = vec2_unitize(v2);
    return vec2_scale(v2_n, vec2_dot(v1, v2_n));
}

static inline vec2_t vec2_from_angle(vec2_t x, vec2_t y, double angle)
{
    double dx = cos(angle);
    double dy = sin(angle);
    return vec2_add(vec2_scale(x, dx), vec2_scale(y, dy));
}

static inline vec2_t vec2_mid(vec2_t v1, vec2_t v2)
{
    return vec2_scale(vec2_add(v1, v2), 0.5f);
}

static inline void vec2_print(vec2_t vec)
{
    printf("(%.2f, %.2f)", vec.x, vec.y);
}
