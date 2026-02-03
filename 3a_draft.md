# Intro

# Text
- unicode
- graphemes
- banned chars
    - `\t`
- `\r` should be absolutely ignored

- what is ASCII alpha-numeric
- what is whitespace char
- what is ASCII space
- what is "word"

# Terminology
- character/char - unicode code point
- lines vs rows
    - lines are about plaintext. Ends with `\n`
    - What is empty/void/blank line
    - rows are about art data

# Concepts
3a **art** is a set of channels.  
**Channels** are parallel sequences of frames indexed from 0.  
**Frames** are a sequences of rows.  
**Rows** are a sequences of elements of type unique for channel.  
  
There are two major channels:  
- **text** channel holds frames of textual art itself. It's elements are UNICODE grapheme clusters.
- **style** channel holds various information for text channel elements (fg/bg colors, italic, blinking, etc). It's elements are names of style mappings.
  
**Style mappings** are bindings between styles and single char names.  
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

Styles may be completely disabled which means whole art shout be showed in
default bg/fg colors.
  
If all frames in channel have same content, they can be replaced with
one **pinned** frame.  
Except case with pinned frames, both text and style channels MUST have same
frames count and therefore one to one mapping between them.  
  
To show frames with adequate timing there are **delay** value describing pause
between frames in milliseconds.
Typically there are single "global" delay value for whole 3a art, but one can
be specified for each frame individually. Deleay value for specific frame means
that this time of *milliseconds* must be skipped *after* this frame before
continue to next one. Default delay value for 3a is 50.  
  
3a art can also contain various metadata like title, author name, tags and so on.

# File Format
## Comments
Some parts of 3a file are *explicitly* defined as supporting comments.
If so, comments are *entire* lines starting with `;;`. There is no multiline or
comments or comments that occupy only part of line.

## Structure
3a file consists of blocks separated by one or more blank lines.
There is always atleast [header](#header-block) or [body](#body-block).  
Each block starts with **block title line** of format `@<block name>` with two exceptions:
- `@header` title line before header block can be always omitted.
- `@body` title line before body block can be omitted if there is only header and body blocks in file.

Block name can contain only ASCII alpha-numeric chars and `+-_.`.

## Header Block
Header is an always first block that contains art metadata.
Header supports [comments](#comments).
Header consists of, key-value pairs, each one on new line.
In each pair, first word (part before first whitespace char) at the beginning
of the line is a key and remains text to the end of line is a value or values.
Value(s) parsing logic is specific for each key.  
Some keys are allowed to occurs multiple times in the header, which is
explicitly defined. For other keys, multiple occurrences are an error.  
All keys and values are case sensitive unless otherwise stated.

### Title Key
**title** key defines an art title. Whole line after key to the end of line is
a single string value. Sequences of multiple copies of same whitespace char
SHOULD be replaced with one during decoding/encoding. All leading and trailing
whitespace chars SHOULD be trimmed.

### Author Key
**author** key defines author of an art. Value parsing rules are same for
[title key](#title-key). Author key can occurs in header multiple times which
means a set of authors. Multiple occurs of author key with same
value (after whitespace trimming and deduplication) MUST be deduplicated.

### Original Author Key
**orig-author** key defines author of original art for derivatives ones.
It works same way as [author key](#author-key).

### Source Key
**src** key defines link to art's original. Typically url. Whole line
after key to the end of line is a single string value. All leading and trailing
whitespace chars SHOULD be trimmed.

### Editor Key
**editor** key provides info about editor software that was used to create this
art.

### License Key
**license** key defines [SPDX license identifier](https://spdx.org/licenses/)
or "proprietary" string. All leading and trailing whitespace chars SHOULD be
inored. Not defined license key or license key with unknown identifier MUST be
treated as "proprietary" unless otherwise stated
in context where 3a file is stored (LICENSE in repo, etc).

### Delay Key
**delay** key defines frame delay(s) as described in [concepts](#concepts).
It can have single or many values separated by one or multiple whitespaces.  
One and only one value of delay key MUST be a string representation of
unsigned decimal int. This value defines "global" delay.  
There also can be arbitrary number of colon-separated int pairs. In each pair
first int is a frame number (starting from 0) and second one is a delay specific
for this frame. Delays defined for non-existent frames SHOULD be ignored.  
If delay key is not provided, global delay has default value 50 milliseconds
and there is no frame-specific delays.

### Loop Key
**loop** key defines should art's animation playback be looped or stops after
first run. It have single case-insensitive boolean value which can be `yes` for
true and `no` for false. If loop key is not provided it is true by default.

### Preview Key
**preview** key defines number of frame that should be used as a preview. It
have only one decimal integer value. Default is 0. If there is no frame with
such number, preview key SHOULD be ignored.

### Style Key
**style** key defines new style binding. It have at least two values separated
by whitespaces. First value is a single char - name of new style. All next
following values defines it modificators.  
Modificators can be:
- `i` - enables italic mode
- `b` - enables bold mode
- `c` - enables crossed mode
- `u` - enables underscore mode
- `fg:<color>` and `bg:<color>` - set foreground and background color
  
Colors in `fg:<color>` and `bg:<color>` can be
- kebab case 3-bit ANSI color name (`green`, `bright-red`, etc)
- 3-bit or 8-bit ANSI color decimal code (`16`, `196`, etc)
- case-insensitive RGB hex color code e.g. `ff00A0`

There can be multiple fg and bg modificators. They should be tried in same
order they are defined (left to right), until one allowed in current environment
is found. if there is no suitable one, default should be used.

Multiple style bindings with same name are not allowed but pre-defined ones can
be overwritten.

### Styling Keys
**styling** key defines is styling enabled for this art, or there is only text
without any decorations. It have single case-insensitive boolean value which
can be `yes` for true and `no` for false. If styling key is not provided but
there is at least one style key, styling is enabled. If styling key is not
provided and there is no style keys, styling is disabled.

### Tags
Each key starts with `#` is not a key, but a tag, all following words in the
same line starting with `#` are also tags. Multiple occurs of same tag in header
SHOULD be deduplicated.

### Header Example
```
@header
;; This is comment. Block title on prev line is redundant, but
;; presented for example.
title A Cool Art
orig-author Some other guy
author Me
author You
;; This is another comment
editor nvim
license CC0-1.0
preview 3
loop off
src https://example.com/my-cool-art
delay 10 2:100
#ascii #ansi
#art
styling on
style + i c bg:bright-red fg:green bg:ff0000 fg:196
```

## Body Block
Body is an always last block that contains art itself. Because there is no other
blocks after it, body can contain blank lines.  

Body consists of frames separated by one or more blank lines. Each frame
consists of lines, separated by `\n` char.  

If styling is enabled and style channel is not pinned, there are two
rows (of same length) in each line going one after other without separator:
- first one from text channel
- second one is a corresponding row from style channel

If styling is disabled, each line is exactly matching one row from text channel.

Body example:
```
@body
  ,--./,-.  444444444444
 / //     \ 444cc4444444
|          |444444444444
 \        / 444444444444
  '._,._,'  444444444444

  ,--./,-.  444444444444
 / //    _\ 444cc4444444
|       /   4444444ffff4
 \      `-, 4444444ffff4
  '._,._,'  444444444444

  ,--./,-.  444444444444
 '--._,.--' 444444444444
    }  {    fffffffffff4
 ,-'._,-`-, fffffffffff4
  '._,._,'  444444444444
```

## Style Block
`@style` block can be used to pin a single frame for style channel.  
It consists of single frame with one row per line.  
Example:
```
@body
444444444444
444cc4444444
444444444444
444444444444
444444444444
```

# Extending
- Naming convention
- Custom header sections
- Custom blocks
- Do not modify existed blocks or header sections, instead add new ones

# Formatting and Optimisation
- comments preservation
- keys with comments should not be removed even they are redundant
- order of blocks
- order of KV pairs in header
- everything that should be ignored during parsing (`\r` chars, delay values for non-existent frames, etc) except comments should be stripped
- RGB color codes in lower case
- remove styles key if there is style keys

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
