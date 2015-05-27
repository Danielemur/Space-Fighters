#pragma once

#include <math.h>

#define COLOR_WHITE  ((color_t){1.0, 1.0, 1.0})
#define COLOR_BLACK  ((color_t){0.0, 0.0, 0.0})
#define COLOR_RED    ((color_t){1.0, 0.0, 0.0})
#define COLOR_GREEN  ((color_t){0.0, 1.0, 0.0})
#define COLOR_BLUE   ((color_t){0.0, 0.0, 1.0})
#define COLOR_PURPLE ((color_t){1.0, 0.0, 1.0})
#define COLOR_YELLOW ((color_t){1.0, 1.0, 0.0})
#define COLOR_CYAN   ((color_t){0.0, 1.0, 1.0})

typedef struct color {
    float r, g, b;
} color_t;

static inline color_t
color_clamp(color_t color)
{
    color_t clamped = {
        fmaxf(fminf(color.r, 1.0f), 0.0f),
        fmaxf(fminf(color.g, 1.0f), 0.0f),
        fmaxf(fminf(color.b, 1.0f), 0.0f)
    };
    return clamped;
}

static inline color_t
color_lerp(color_t c0, color_t c1, float t)
{
    return (color_t){
        (1 - t) * c0.r + t * c1.r,
        (1 - t) * c0.g + t * c1.g,
        (1 - t) * c0.b + t * c1.b
    };
}

static inline color_t
color_add(color_t c0, color_t c1)
{
    return (color_t){c0.r + c1.r, c0.g + c1.g, c0.b + c1.b};
}

static inline color_t
color_sub(color_t c0, color_t c1)
{
    return (color_t){c0.r - c1.r, c0.g - c1.g, c0.b - c1.b};
}

static inline color_t
color_pow(color_t c, float e)
{
    return (color_t){powf(c.r, e), powf(c.g, e), powf(c.b, e)};
}

static inline color_t
color_scale(color_t c, float s)
{
    return (color_t){c.r * s, c.g * s, c.b * s};
}


static inline color_t
color_mean(color_t *colors, int ncolors)
{
    color_t mean = {0, 0, 0};
    for (int i = 0; i < ncolors; i++)
        mean = color_add(mean, colors[i]);
    return color_scale(mean, 1.0f / ncolors);
}

static inline float
color_std(color_t *colors, int ncolors)
{
    color_t mean = color_mean(colors, ncolors);
    color_t sum = {0, 0, 0};
    for (int i = 0; i < ncolors; i++)
        sum = color_add(sum, color_pow(color_sub(colors[i], mean), 2.0f));
    return sqrtf(fmaxf(sum.r, fmaxf(sum.g, sum.b)) / ncolors);
}
