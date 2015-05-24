#include <stdio.h>

int main(int argc, char **argv)
{
  
  stage_t stage;
  stage_init(&stage);
  stage_run(&stage);
  stage_cleanup(&stage);
}
