# Abe's Amazing Adventure

A scrolling, platform-jumping, key-collecting, ancient pyramid exploring game,
vaguely in the style of similar games for the Commodore+4. Originally written
by Gabor Torok as a birthday gift for his son.

## Requirements

- SDL 2.x (see `abe_os2.txt` for the ArcaOS/OS2 port)
- SDL 2 mixer

## Building

**Linux (autoconf):**
```
./autogen.sh
./configure
make
```

**Windows cross-compile (from Linux with MinGW):**
```
./autogen.sh
./cross-configure
./cross-make clean all
```

**ArcaOS / OS/2:**
See `abe_os2.txt`.

## Running

```
./abe            # windowed
./abe -f         # fullscreen
./abe --help     # list all options
```

On Windows/OS2: `abe.exe --window`

Abe supports video modes from 320x200 up to 800x600 and requires at least 16 bpp.
Run `./abe -t` to benchmark which fullscreen modes are fastest.

## Controls

### Game
| Key | Action |
|-----|--------|
| Arrow keys | Move / climb |
| Space | Jump |
| Enter | Use a balloon |
| Esc | Quit |

### Editor
The built-in map editor is enabled by setting `GOD_MODE 1` in `src/Game.h` and rebuilding.

| Key | Action |
|-----|--------|
| Arrow keys | Move cursor |
| Home / End / PgUp / PgDn | Move by pages |
| Enter | Place tile |
| 1 / 2 / 3 | Select layer |
| Del / Backspace | Clear tile |
| 5 / 6 | Cycle through tiles |
| L | Load map |
| S | Save map |
| Q, W | Define a slide (Q = top-left, W = bottom-right) |
| Q, E | Draw a filled rectangle |
| Esc | Quit |

## Authors

- Gabor Torok &lt;cctorok@yahoo.com&gt; — original game
- Pedro Izecksohn &lt;izecksohn@yahoo.com&gt;
- Alex Clarck
- Martin Iturbide — ArcaOS / OS2 SDL2 port

## License

GNU GPL V2

## Links

- Original project: http://abe.sf.net
- ArcaOS port notes: `abe_os2.txt`
