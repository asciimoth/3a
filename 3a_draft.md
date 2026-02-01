# Intro

# Text
- unicode
- graphemes
- banned chars

# Concepts
3a **art** is a set of channels.  
**Channels** are parallel sequences of frames.  
**Frames** are a sequences of rows.  
**Rows** are a sequences of elements of type unique for channel.  
  
There are two major channels:  
- **text** channel holds frames of textual art itself. It's elements are UNICODE grapheme clusters.
- **style** channel holds various information for text channel elements (fg/bg colors, italic, blinking, etc). It's elements are names of style mappings.
  
**Style mappings** are bindings between styles and single grapheme names.  
**Style** is a set of visual modificators:
- **fg** and **bg** - foreground and background text colors. Can be
    - ANSI 4-bit colors (Black/Blue/Green/Cyan/Red/Magenta/Yellow/Wite + brightness mod)
    - ANSI [256 colors](https://en.wikipedia.org/wiki/8-bit_color)
    - True 24-bit RGB colors
- **bold** on/off
- **italic** on/off
- **crossed** on/off
- **underscore** on/off
  
Some of those modificators are not supported everywhere, so multiple colors may be
defined in single style as fallback. It is highly recommended to always define
4-bit fallback color.  
Users can define their own custom styles but there are some pre-defined ones:
- `_` - no style/default style. Usually white text on black background.
- `0` - ANSI 4-bit black text (code 30), default background.
- `1` - ANSI 4-bit red text (code 31), default background.
- `2` - ANSI 4-bit green text (code 32), default background.
- `3` - ANSI 4-bit yellow text (code 33), default background.
- `4` - ANSI 4-bit blue text (code 34), default background.
- `5` - ANSI 4-bit magenta text (code 35), default background.
- `6` - ANSI 4-bit cyan text (code 36), default background.
- `7` - ANSI 4-bit white text (code 37), default background.
- `8` - ANSI 4-bit bright black (gray) text (code 90), default background.
- `9` - ANSI 4-bit bright red text (code 91), default background.
- `a` - ANSI 4-bit bright green text (code 92), default background.
- `b` - ANSI 4-bit bright yellow text (code 93), default background.
- `c` - ANSI 4-bit bright blue text (code 94), default background.
- `d` - ANSI 4-bit bright magenta text (code 95), default background.
- `e` - ANSI 4-bit bright cyan text (code 96), default background.
- `f` - ANSI 4-bit bright white text (code 97), default background.
  
If all frames in channel have same content, they can be replaced with
one **pinned** frame.  
Except case with pinned frames, both text and style channels MUST have same
frames count and therefore one to one mapping between them.  
  
To show frames with adequate timing there are **delay** value describing pause
between frames in milliseconds.
Typically there are single delay value for whole 3a art, but one can be
specified for each frame individually.  
  
3a art can also contain various metadata like title, author name, tags and so on.
# File Format
- blocks; at least 2
    - blank line separation
- first block is always a header
    - contains art metadata and information about other blocks and their count
- last block is always a body
    - contains art itself (channels, frames, etc)
    - may contain blank lines

## header
- Comments
- Params
- Sections

# Extending
- Naming convention
- Custom header sections
- Custom blocks
- Do not modify existed blocks or header sections, instead add new ones

# Decoding

# Formatting and Optimisation

# MIME

# Legacy Format
- Automatic distinction from the legacy version

# Compatibility Notes
- 3a fully support UNICODE by specification but it is not true for all software that can be used to render and display 3a (terminal emulators, etc).
- It is recommended not to use grapheme clasters contains more that one code point in art.
- Also different software can support different versions of UNICODE so it is recommended not to use things added in rescent UNICODE versions.

# TODO
- comments in header
    - preserving during formatting
- banned chars
    - tab, vtab
- names banned for color mappings
- suggested optimistations
    - replace all whitespace chars with ASCII space
- suggested MIME type, MIME DB file
