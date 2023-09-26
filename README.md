# HailMary

HailMary is a minimalistic isometric 2D runtime

## Project Setup

### Requirements

HailMary requires an installation of `python-3.11` and the `meson` build
system. As well as a functioning C++ compiler that supports C++ 20.

If you are in linux, you'll also need the `python-3.11-dev` package for
Python development headers.

Any other requirements are handled by the meson itself.


### Setup

We use `meson` to bootstrap the project, you'll have to create the build
directory and set the project up.

```bash
mkdir build
meson setup build
```

Then, to compile:

```bash
meson compile -C build
```

Initial compilation will also take care the installing of `sdl2` and
the associated helper libraries.

Once the first compilation is done, Intelisense should kick in VSCode,
provided you have the extensions installed.


