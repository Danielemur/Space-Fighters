#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "color.h"

typedef struct image {
    unsigned width, height;
    uint8_t pixels[];
} image_t;

image_t *image_create(unsigned width, unsigned height);
void     image_free(image_t *image);
image_t *image_read_ppm(FILE *ppm);
image_t *image_read_bmp(FILE *bmp);
void     image_write_ppm(const image_t *, FILE *ppm);
void     image_write_bmp(const image_t *image, FILE *bmp);
void     image_set(image_t *, unsigned x, unsigned y, color_t);
color_t  image_get(const image_t *, unsigned x, unsigned y);
color_t  image_sample(const image_t *image, float x, float y);

/* Y4M */

typedef struct y4m_writer {
    FILE *out;
    image_t *image;
    uint8_t *workspace;
} y4m_writer_t;

/**
 * Associates a particular image buffer with a Y4M writer. Each call
 * to y4m_writer_frame() dumps the contents of the image out as a
 * frame of the video.
 */
void y4m_writer_init(y4m_writer_t *, image_t *, int fps, FILE *);
void y4m_writer_frame(y4m_writer_t *);
void y4m_writer_free(y4m_writer_t *);

/* Drawing Functions */

typedef struct font {
    image_t *glyphs;
    color_t color;
    float alpha;
    float scaled_size;
} font_t;

void font_init(font_t *font, const char *font_name);
void font_buffer_init(font_t *font, const char *buffer);
void font_free(font_t *font);

/**
  * Returns the normalized draw width of a string.
  */
float font_width(font_t *, image_t *, const char *);

/**
 * Draw a string at a normalized (0.0-1.0) image position.
 */
void image_text(image_t *image, font_t *font, float x, float y, const char *);

void image_line(image_t *image, color_t, int x0, int y0, int x1, int y1);
