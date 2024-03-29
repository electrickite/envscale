envscale
========

A small utility that sets several HiDPI scaling environment variables before
running a command. It uses GDK to detect the current scaling factor.

Note: The tool was built to solve a specific issue on certain applications
running under GNOME/Wayland and is unlikely to work in other environments.

## Install

Ensure that the following dependencies are installed:

  * GTK3
  * gcc
  * make

Then run:

    $ make
    $ sudo make install

On Arch Linux, you can install `envscale` from the AUR.

## Usage

    envscale [-f] COMMAND [ARG]...

Sets several HiDPI scaling variables in the process environment then execs
`COMMAND`. Any additional arguments are passed directly to `COMMAND`.

The `-f` option adds `--force-device-scale-factor` as the first argument to
COMMAND.

### Environment

Currently, the following environment variables are set:

  * `GDK_SCALE`
  * `QT_SCALE_FACTOR`
  * `QT_AUTO_SCREEN_SCALE_FACTOR=0`
  * `ELM_SCALE`

## License and copyright

Copyright 2019 Corey Hinshaw

Released under the MIT license. See the LICENSE file for details.
