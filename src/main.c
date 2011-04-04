#include <stdlib.h>
#include "options.h"
#include "cli.h"
#include "list.h"
#include "io.h"
#include "spline.h"

int main(int argc, const char **argv)
{
  if (!cli_parse(argc, argv)) {
    fprintf(stderr, "[error] %s:%d:%s(): invalid command line arguments\n", __FILE__, __LINE__, __func__);
    return EXIT_FAILURE;
  }

  list_t *nodes = io_read();
  if (!nodes) {
    return EXIT_FAILURE;
  }

  list_t *splines = spline_interpolate(nodes);
  if (!splines) {
    return EXIT_FAILURE;
  }

  if(!io_write(nodes, splines)) {
    return EXIT_FAILURE;
  }

  if(!io_gnuplot(nodes, splines)) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
