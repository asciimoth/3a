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

# Terminology
- character/char - unicode code point
- line and row are interchangeable. Ends on `\n`
    - What is empty/void/blank line

# Concepts
3a **art** is a set of channels.  
**Channels** are parallel sequences of frames indexed from 0.  
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
## Comments
Some parts of 3a file are *explicitly* defined as supporting comments.
If so, comments are *entire* rows starting with `;;`. There is no multiline or
comments or comments that occupy only part of row.

## Structure
3a file consists of blocks separated by one or more blank lines.
There is always atleast two blocks: [header](#header-block) (first) and [body](#body-block) (last).  
Each block starts with **block title row** of format `@<block name>` with two exceptions:
- `@header` title row before header block can be always omitted.
- `@body` title row before body block can be omitted if there is only header and body blocks in file.

Block name can contain only ASCII alpha-numeric chars and `+-_.`.

## Header Block
Header contains art metadata.
Header supports [comments](#comments).
Header consists of, key-value pairs, each one on new row.
In each pair, first word (part before first whitespace char) at the beginning
of the row is a key and remains text to the end of row is a value or values.
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

### Maintainer Key

### Source Key

### Editor Key

### License Key

### Delay Key

### Loop Key
- true by default

### Preview Key
- 0 by default

### Style Key

### Tags

### Header Example
```3a
@header
;; This is comment. Block title on prev line is redundant, but
;; presented for example.
title A Cool Art
author Me
author You
orig-author Some other guy
;; This is another comment
editor nvim
license CC0-1.0
preview 3
src https://example.com/my-cool-art
delay 1s 10 2s
#ascii #ansi
#art
```

## Body Block
- last block is always a body
    - contains art itself (channels, frames, etc)
    - may contain blank lines

# Extending
- Naming convention
- Custom header sections
- Custom blocks
- Do not modify existed blocks or header sections, instead add new ones

# Decoding

# Formatting and Optimisation
- order of blocks
- order of KV pairs in header

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
