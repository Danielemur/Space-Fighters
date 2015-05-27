#include <stdio.h>
#include <math.h>

#include "stage.h"
#include "image.h"

void image_render(stage_t *stage, void **context)
{
    image_t *image = (image_t*)context[0];
    y4m_writer_t *y4m = (y4m_writer_t*)context[1];
    for (entity_t *entity = stage->entities; entity != NULL; entity = entity->next) {
        color_t color;
        if (entity->type == PLAYER)
            color = COLOR_RED;
        else if (entity->type == ENEMY)
            color = COLOR_GREEN;
        else if (entity->type == PROJECTILE)
            color =  COLOR_YELLOW;
        else if (entity->type == ASTEROID)
            color =  COLOR_BLUE;
        for (int i = -2; i < 3; i++) {
            for (int h = -2; h < 3; h++) {
                image_set(image, fmin(entity->movement.position.x + i + STAGE_WIDTH / 2, STAGE_WIDTH / 2),
                          fmin(entity->movement.position.y + h + STAGE_HEIGHT / 2, STAGE_HEIGHT / 2), color);
            }
        }
    }
    y4m_writer_frame(y4m);
}

int main(int argc, char **argv)
{
    FILE *space = fopen("space.bmp", "r");
    image_t *image = image_read_bmp(space);
//image_create(STAGE_WIDTH, STAGE_HEIGHT);
    FILE *out = stdout;
    y4m_writer_t y4m;
    y4m_writer_init(&y4m, image, 15, out);
    void *context[2] = {image, &y4m};
    stage_t stage;
    stage_init(&stage);
    stage_run(&stage, image_render, context);
    stage_cleanup(&stage);
    y4m_writer_free(&y4m);
    image_free(image);
}
