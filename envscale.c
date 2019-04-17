/**
 * envscale: Set scaling factor environment variables
 * Copyright 2019 Corey Hinshaw
 *
 * See LICENSE file for copyright and license details.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gdk/gdk.h>

int main (int argc, char **argv)
{
  size_t exec_argc;
  char **exec_argv;
  GdkWindow *window;
  GdkWindowAttr attributes;
  gint scale;

  if (argc < 2)
    errx(1, "Missing argument");

  // argc - argv[0] + argv[argc] NULL pointer
  exec_argc = argc;
  exec_argv = malloc(exec_argc * sizeof(char *));
  memcpy(exec_argv, argv + 1, (exec_argc + 1) * sizeof(argv));

  if (!gdk_init_check(&argc, &argv))
    errx(2, "Could not initialize GDK");

  attributes.window_type = GDK_WINDOW_TOPLEVEL;
  attributes.width = 0;
  attributes.height = 0;
  attributes.wclass = GDK_INPUT_OUTPUT;

  window = gdk_window_new(NULL, &attributes, 0);
  scale = gdk_window_get_scale_factor(window);
  gdk_window_destroy(window);

  if (scale <= 0)
    errx(3, "Invalid scale factor detected");

  // Create a character array to store scale as string
  char scalestr[snprintf(0, 0, "%+d", scale) - 1];
  sprintf(scalestr, "%i", scale);

  setenv("GDK_SCALE", scalestr, 1);
  setenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0", 1);
  setenv("QT_SCALE_FACTOR", scalestr, 1);

  execvp(argv[1], exec_argv);
  err(4, argv[1]);
}
