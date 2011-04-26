#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "logger.h"
#include "options.h"
#include "file_helpers.h"

void log_impl(const char *file, const int line, const char *type, const char *msg, ...)
{
  if (!options || options->quiet) return;

  static FILE *log = NULL;
  if (!log && (options->in_filename || options->out_filename)) {
    const char *output_filename = options->out_filename ? options->out_filename : options->in_filename;
    char *log_filename = file_helpers_change_extension(output_filename, ".log");

    log = fopen(log_filename, "w");
    time_t rawtime;
    time(&rawtime);
    fprintf(log, "# created at: %s", ctime(&rawtime));
    fprintf(log, "#       file: %s\n", log_filename);

    free(log_filename);
  }

  const char log_fmt[] = "%s:%d: [%s] %s\n"; 
  char *log_msg;
  va_list ap;
  va_start(ap, msg);
  vasprintf(&log_msg, msg, ap);
  va_end(ap);
  
  if (log)
    fprintf(log, log_fmt, file, line, type, log_msg);
  if (strcmp(type, "error") == 0)
    fprintf(stderr, log_fmt, file, line, type, log_msg);

  free(log_msg);
}

