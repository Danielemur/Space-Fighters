#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "image.h"

#define MIN(a, b) ((b) < (a) ? (b) : (a))
#define MAX(a, b) ((b) > (a) ? (b) : (a))

static inline void
assert_little_endian(void)
{
    /* Assume host is little endian. */
    assert((union {
        uint32_t value;
        uint8_t bytes[4];
    }){0x01020304}.bytes[0] == 0x04);
}

image_t *image_create(unsigned width, unsigned height)
{
    image_t *image = calloc(sizeof(*image) + width * height * 3, 1);
    image->width = width;
    image->height = height;
    return image;
}

void image_free(image_t *image)
{
    free(image);
}

image_t *image_read_ppm(FILE *ppm)
{
    unsigned width, height, depth;
    int count = fscanf(ppm, "P6 %u %u %u", &width, &height, &depth);
    if (count != 3 || fgetc(ppm) == EOF || depth != 255)
        return NULL;
    image_t *image = image_create(width, height);
    if (fread(image->pixels, 3 * width * height, 1, ppm) != 1) {
        free(image);
        return NULL;
    }
    return image;
}

image_t *image_load_ppm(const char *buffer)
{
    if (buffer[0] != 'P' || buffer[1] != '6')
        return NULL;
    char *p = (char *)buffer + 3;
    unsigned width = strtol(p, &p, 10);
    unsigned height = strtol(p, &p, 10);
    unsigned depth = strtol(p, &p, 10);
    if (depth != 255)
        return NULL;
    p++;
    image_t *image = image_create(width, height);
    memcpy(image->pixels, p, 3 * width * height);
    return image;
}

void image_write_ppm(const image_t *image, FILE *ppm)
{
    fprintf(ppm, "P6\n%d %d\n255\n", image->width, image->height);
    fwrite(image->pixels, image->width * image->height, 3, ppm);
}

void image_write_bmp(const image_t *image, FILE *bmp)
{
    assert_little_endian();
    fputs("BM", bmp);
    uint32_t bmp_header[] = {
        14 + 40 + ((image->width * 3 + 3) / 4) * 4 * image->height,
        0, 14 + 40
    };
    fwrite(&bmp_header, sizeof(bmp_header), 1, bmp);
    uint32_t dib_header[] = {
        40, image->width, -image->height, 0x00180001, 0, 0, 2835, 2835, 0, 0
    };
    fwrite(&dib_header, sizeof(dib_header), 1, bmp);
    uint32_t padding = 0;
    for (unsigned y = 0; y < image->height; y++) {
        for (unsigned x = 0; x < image->width; x++)
            for (int i = 2; i >= 0; i--)
                fputc(image->pixels[image->width * y * 3 + x * 3 + i], bmp);
        fwrite(&padding, (image->width * 3) % 4, 1, bmp);
    }
}

/* Only reads 24-bit true color bitmaps. */
image_t *image_read_bmp(FILE *bmp)
{
    assert_little_endian();
    uint8_t magic[2];
    if (fread(magic, sizeof(magic), 1, bmp) != 1 ||
        memcmp(magic, "BM", sizeof(magic)) != 0)
        return NULL;
    struct {
        uint32_t _size;
        uint32_t _reserved;
        uint32_t offset;
        uint32_t header_size;
        int32_t  width;
        int32_t  height;
        uint16_t planes;
        uint16_t bits;
        uint32_t compression;
        uint32_t _image_size;
        uint32_t _width_resolution;
        uint32_t _height_resolution;
        uint32_t _color_count;
        uint32_t _important_count;
    } bmp_header;
    if (fread(&bmp_header, sizeof(bmp_header), 1, bmp) != 1)
        return NULL;
    if (bmp_header.header_size != 40 &&
        bmp_header.header_size != 52 &&
        bmp_header.header_size != 56 &&
        bmp_header.header_size != 108 &&
        bmp_header.header_size != 124)
        return NULL;
    if (bmp_header.planes != 1)
        return NULL;
    if (bmp_header.bits != 24)
        return NULL;
    if (bmp_header.compression != 0)
        return NULL;
    size_t skip = bmp_header.offset - sizeof(bmp_header) - sizeof(magic);
    uint8_t dummy[skip];
    if (fread(dummy, 1, skip, bmp) != skip)
        return NULL;
    image_t *image = image_create(bmp_header.width, labs(bmp_header.height));
    uint32_t y_start = bmp_header.height > 0 ? image->height - 1 : 0;
    uint32_t y_stop  = bmp_header.height > 0 ? 0 : image->height - 1;
    uint32_t y_step  = bmp_header.height > 0 ? -1 : 1;
    for (uint32_t y = y_start; y != y_stop; y += y_step) {
        for (uint32_t x = 0; x < bmp_header.width; x++) {
            for (int c = 2; c >= 0; c--) {
                size_t i = image->width * y * 3 + x * 3 + c;
                image->pixels[i] = fgetc(bmp);
            }
        }
        uint32_t padding;
        fread(&padding, (4 - (image->width * 3)) % 4, 1, bmp);
    }
    return image;
}

void image_set(image_t *image, unsigned x, unsigned y, color_t color)
{
    size_t offset = image->width * y * 3 + x * 3;
    image->pixels[offset + 0] = color.r * 255.0f;
    image->pixels[offset + 1] = color.g * 255.0f;
    image->pixels[offset + 2] = color.b * 255.0f;
}

color_t image_get(const image_t *image, unsigned x, unsigned y)
{
    size_t offset = image->width * y * 3 + x * 3;
    return (color_t){
        .r = image->pixels[offset + 0] / 255.0f,
        .g = image->pixels[offset + 1] / 255.0f,
        .b = image->pixels[offset + 2] / 255.0f,
    };
}

color_t image_sample(const image_t *image, float x, float y)
{
    float i;
    x = modff((modff(x, &i) + 1.0f), &i);
    y = modff((modff(y, &i) + 1.0f), &i);
    /* Bilinear interpolation. */
    float w = image->width  - 1;
    float h = image->height - 1;
    unsigned x0 = x * w + 0;
    unsigned y0 = y * h + 0;
    unsigned x1 = x * w + 1;
    unsigned y1 = y * h + 1;
    color_t c00 = image_get(image, x0, y0);
    color_t c10 = image_get(image, x1, y0);
    color_t c01 = image_get(image, x0, y1);
    color_t c11 = image_get(image, x1, y1);
    float tx = modff(x * w, &tx);
    float ty = modff(y * h, &ty);
    color_t c0 = color_lerp(c00, c10, tx);
    color_t c1 = color_lerp(c01, c11, tx);
    return color_lerp(c0, c1, ty);
}

/* Y4M */

void y4m_writer_init(y4m_writer_t *w, image_t *image, int fps, FILE *out)
{
    w->out = out;
    w->image = image;
    w->workspace = malloc(image->width * image->height * 3);
    fprintf(out, "YUV4MPEG2 W%u H%u ", image->width, image->height);
    fprintf(out, "F%d:1 Ip A1:1 C444\n", fps);
}

void y4m_writer_free(y4m_writer_t *w)
{
    free(w->workspace);
    w->workspace = NULL;
}

typedef struct ycbcr {
    uint8_t y, cb, cr;
} ycbcr_t;

/* https://msdn.microsoft.com/en-us/library/ff635643.aspx */
static ycbcr_t
get_ycbcr(image_t *image, unsigned x, unsigned y)
{
    size_t offset = image->width * y * 3 + x * 3;
    float r = image->pixels[offset + 0];
    float g = image->pixels[offset + 1];
    float b = image->pixels[offset + 2];
    ycbcr_t ycbcr_t = {
        .y  =  0.299000f * r + 0.587000f * g + 0.114000f * b,
        .cb = -0.168935f * r - 0.331665f * g + 0.500590f * b + 128,
        .cr =  0.499813f * r - 0.418531f * g - 0.081282f * b + 128
    };
    return ycbcr_t;
}

void y4m_writer_frame(y4m_writer_t *w)
{
    fprintf(w->out, "FRAME\n");
    size_t plane_size = w->image->width * w->image->height;
    uint8_t *plane_y  = w->workspace + plane_size * 0;
    uint8_t *plane_cb = w->workspace + plane_size * 1;
    uint8_t *plane_cr = w->workspace + plane_size * 2;
    for (unsigned y = 0; y < w->image->height; y++) {
        for (unsigned x = 0; x < w->image->width; x++) {
            ycbcr_t ycbcr = get_ycbcr(w->image, x, y);
            *plane_y  = ycbcr.y;
            *plane_cb = ycbcr.cb;
            *plane_cr = ycbcr.cr;
            plane_y++;
            plane_cb++;
            plane_cr++;
        }
    }
    fwrite(w->workspace, plane_size, 3, w->out);
    fflush(w->out);
}

/* Drawing */

void font_init(font_t *font, const char *font_name)
{
    char path[strlen(font_name) + 5 + 4 + 1];
    sprintf(path, "font/%s.ppm", font_name);
    FILE *file = fopen(path, "rb");
    font->glyphs = image_read_ppm(file);
    fclose(file);
    font->color = COLOR_BLACK;
    font->alpha = 1.0f;
    font->scaled_size = 0.08f;
}

void font_buffer_init(font_t *font, const char *buffer)
{
    font->glyphs = image_load_ppm(buffer);
    font->color = COLOR_BLACK;
    font->alpha = 1.0f;
    font->scaled_size = 0.08f;
}

void font_free(font_t *font)
{
    image_free(font->glyphs);
}

float font_width(font_t *font, image_t *image, const char *text)
{
    unsigned glyph_w = font->glyphs->width / 16;
    unsigned glyph_h = font->glyphs->height / 6;
    unsigned draw_h = roundf(image->height * font->scaled_size);
    unsigned draw_w = roundf(draw_h * glyph_w / (float)glyph_h);
    return strlen(text) * draw_w / (float)image->width;
}

static inline bool
is_valid(const image_t *image, unsigned x, unsigned y)
{
    return x >= 0 && x < image->width && y >= 0 && y < image->height;
}

void
image_text(image_t *image, font_t *font, float x, float y, const char *text)
{
    unsigned glyph_h = font->glyphs->height / 6;
    unsigned glyph_w = font->glyphs->width / 16;
    unsigned draw_h = roundf(image->height * font->scaled_size);
    unsigned draw_w = roundf(draw_h * glyph_w / (float)glyph_h);
    unsigned py = roundf(y * image->height);
    unsigned px = roundf(x * image->width);
    float ry = glyph_h / (float)draw_h;
    float rx = glyph_w / (float)draw_w;
    for (; *text; text++, px += draw_w) {
        if (*text < ' ' || *text > 127)
            continue;
        unsigned char_x = ((*text - ' ') % 16) * glyph_w;
        unsigned char_y = ((*text - ' ') / 16) * glyph_h;
        for (unsigned dy = 0; dy < draw_h; dy++) {
            for (unsigned dx = 0; dx < draw_w; dx++) {
                unsigned tx = px + dx;
                unsigned ty = py + dy;
                if (is_valid(image, tx, ty)) {
                    float sx = (char_x + dx * rx) / font->glyphs->width;
                    float sy = (char_y + dy * ry) / font->glyphs->height;
                    float glyph_alpha =
                        1.0f - image_sample(font->glyphs, sx, sy).r;
                    float alpha = glyph_alpha * font->alpha;
                    color_t orig = image_get(image, tx, ty);
                    color_t result = color_lerp(orig, font->color, alpha);
                    image_set(image, tx, ty, result);
                }
            }
        }
    }
}

static void blend(image_t *image, unsigned x, unsigned y, color_t c, float a)
{
    color_t orig = image_get(image, x, y);
    image_set(image, x, y, color_lerp(orig, c, a));
}

static float fpart(float x)
{
    if (x < 0)
        return 1 - (x - floorf(x));
    else
        return x - floorf(x);
}

static float rfpart(float x)
{
    return 1.0f - fpart(x);
}

/* Xiaolin Wu's line algorithm
 * http://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 */
void
image_line(image_t *image, color_t color, int x0, int y0, int x1, int y1)
{
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        int tmp = x0;
        x0 = x1;
        x1 = tmp;
        tmp = y0;
        y0 = y1;
        y1 = tmp;
    }
    if (x0 > x1) {
        int tmp = x0;
        x0 = x1;
        x1 = tmp;
        tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    float dx = x1 - x0;
    float dy = y1 - y0;
    float gradient = dy / dx;

    float xend = roundf(x0);
    float yend = y0 + gradient * (xend - x0);
    float xgap = rfpart(x0 + 0.5);
    int xpxl1 = xend;
    int ypxl1 = floorf(yend);
    if (steep) {
        blend(image, ypxl1,   xpxl1, color, rfpart(yend) * xgap);
        blend(image, ypxl1+1, xpxl1, color,  fpart(yend) * xgap);
    } else {
        blend(image, xpxl1, ypxl1  , color, rfpart(yend) * xgap);
        blend(image, xpxl1, ypxl1+1, color,  fpart(yend) * xgap);
    }
    float intery = yend + gradient;

    xend = roundf(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = fpart(x1 + 0.5);
    int xpxl2 = xend;
    int ypxl2 = floorf(yend);
    if (steep) {
        blend(image, ypxl2  , xpxl2, color, rfpart(yend) * xgap);
        blend(image, ypxl2+1, xpxl2, color, fpart(yend) * xgap);
    } else {
        blend(image, xpxl2, ypxl2,   color, rfpart(yend) * xgap);
        blend(image, xpxl2, ypxl2+1, color, fpart(yend) * xgap);
    }

    // main loop
    for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
        if (steep) {
            blend(image, intery,     x, color, rfpart(intery));
            blend(image, intery + 1, x, color, fpart(intery));
        } else {
             blend(image, x, intery,     color, rfpart(intery));
             blend(image, x, intery + 1, color, fpart(intery));
        }
        intery = intery + gradient;
    }
}
