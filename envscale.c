/**
 * envscale: Set scaling factor environment variables
 * Copyright 2019 Corey Hinshaw
 *
 * See LICENSE file for copyright and license details.
 */

#include <err.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gdk/gdk.h>


int main (int argc, char **argv)
{
  bool add_force = false;
  if (argc >= 2 && strcmp(argv[1], "-f") == 0) {
    add_force = true;
    argv[1] = argv[0];
    argv++;
    argc--;
  }

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [-f] COMMAND [ARG]...\n\
Try 'man %s' for more information.\n", basename(argv[0]), basename(argv[0]));
    exit(1);
  }

  char *command = argv[1];

  // With force argument: argc - argv[0] + force arg + argv[argc] NULL pointer
  // Without force argument: argc - argv[0] + argv[argc] NULL pointer
  size_t exec_argc = add_force ? argc + 1 : argc;
  char **exec_argv = malloc(exec_argc * sizeof(char *));

  if (!gdk_init_check(&argc, &argv))
    errx(2, "Could not initialize GDK");

  GdkWindowAttr attributes;
  attributes.window_type = GDK_WINDOW_TOPLEVEL;
  attributes.width = 0;
  attributes.height = 0;
  attributes.wclass = GDK_INPUT_OUTPUT;

  GdkWindow *window = gdk_window_new(NULL, &attributes, 0);
  gint scale = gdk_window_get_scale_factor(window);
  gdk_window_destroy(window);

  if (scale <= 0)
    errx(3, "Invalid scale factor detected");

  // Create a character array to store scale as string
  char scalestr[snprintf(0, 0, "%+d", scale) - 1];
  sprintf(scalestr, "%i", scale);

  char *force_arg = malloc(28 + strlen(scalestr) + 1);
  strcpy(force_arg, "--force-device-scale-factor=");
  strcat(force_arg, scalestr);

  char *elm_scale = malloc(strlen(scalestr) + 2 + 1);
  strcpy(elm_scale, scalestr);
  strcat(elm_scale, ".0");

  setenv("GDK_SCALE", scalestr, 1);
  setenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0", 1);
  setenv("QT_SCALE_FACTOR", scalestr, 1);
  setenv("ELM_SCALE", elm_scale, 1);

  if (add_force) {
    memcpy(exec_argv + 1, argv + 1, argc * sizeof(argv));
    exec_argv[0] = command;
    exec_argv[1] = force_arg;
  } else {
    memcpy(exec_argv, argv + 1, argc * sizeof(argv));
  }

  execvp(command, exec_argv);
  err(4, command);
}
