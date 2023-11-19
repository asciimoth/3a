# Animated Ascii Art (3a)
- [Adbout](#adbout)
- [Reasons](#reasons)
- [More art](#more-art)
- [Specification](#specification)
  - [Comments](#comments)
  - [Header](#header)
  - [Body](#body)
  - [Example](#example)
  - [Creating extensions](#creating-extensions)
- [Reference implementation](#reference-implementation)
  - [Dependencies](#dependencies)
  - [Installation](#installation)
  - [Usage](#usage)
- [Other implementations](#other-implementations)
  - [rs3a](https://github.com/DomesticMoth/rs3a)
  - [py3a](https://github.com/DomesticMoth/py3a)
  - [go3a](https://github.com/DomesticMoth/go3a)
  - [aaa](https://github.com/DomesticMoth/aaa)
  - [convert3a](https://github.com/DomesticMoth/convert3a)
- [License](#license)

# Adbout
3a (stands for "Animated Ascii Art") is a simple human-readable text format for storing ascii animations, convenient for viewing and editing through any text editor.  
3a supports unicode and 16 ASNI colors (color + bold bit) for foreground and background.  
Also 3a designed for easy manual writing parsers.  

## Reasons
While customizing my *nix system, I was going to actively use ascii animations for styling. I expected that there is a widespread text format for storing animated ascii art. But it turned out that this was not the case. So I had to create it.

## More art
You can find more 3a art [here](https://github.com/DomesticMoth/3a_storage)

## Specification
3a file consists of two parts: the header and the body. The header contains the metadata of the art and the body contains the art itself. The header is separated from the body by one or more empty lines.  

### Unicode
Hereinafter, these terms have the following meaning:
- grapheme - unicode grapheme custer
- char or symbol - unicode code point

### Comments
The text starting from the tab character and up to the end of the line should be ignored. So it can be used as comments.

### Header
The header contains parameters. Each parameter is on a separate line. There should be no empty lines between the parameter lines (because it is header and body separator). The parameter line consists of the parameter name and its arguments separated by one or more spaces.  
General structure of the parameter: `[name] [arg 1] [arg 2] [arg n]`  
Example: `width 10`  

Required parameters (must be in any 3a file):
- `width` - Width of the art in characters(unsigned 16-bit integer)
- `height` - Height of the art in characters(unsigned 16-bit integer)

Optional parameters:
- `delay` - (unsigned 16-bit decimal integer) Delay between rendering animation frames in milliseconds. By default is 50.
- `loop` - (str `true` or `false`) Need to loop the animation. By default is `true`.
- `colors` - (str) The type of color palette. Accepts one of the following arguments (by default is `none`):
  - `none` - Colors are not specified.
  - `fg` - Сolors are specified for text only.
  - `bg` - Сolors are specified only for the background.
  - `full` - Colors are specified for both text and background.
- `@` - Ignored parmeter. Another way to leave comments in addition to the lines starting with tab.
- `datacols` - (unsigned 16-bit decimal integer) Number of columns with information. Use this parameter in format extensions. By default, it is calculated from the colors parameter.
- `preview` - (unsigned 16-bit decimal integer) Frame number (starts from 0) that should be shown as a static preview of the animation. By default is 0.
- `title` - (str) Title of art.
- `author` - (str) Author of art.
- `#` - (str) tag. Each argument of this parameter denotes a different tag. The tag array described with this parameter must be deduplicated.

All unknown parameters should be ignored.  
All parameters with incorrect arguments(except `width` and `height`) should be ignored.   
If a parameter occurs more than once in the header, all occurrences other than the first should be ignored.  

### Body
Tabs, line breaks, escape chars, and any other control or unprintable characters should be ignored in the file body.   
File body consists of frames that consist of rows that consist of columns.    
Each frame consists of as many rows as specified in the `height` parameter.  
Each row consists of one or more columns.  
Each column consists of as many graphemes as specified in the `width` parameter.  
Each column describes one type of information about the line displaying on the screen.  
First column always contains graphemes drawn on the screen. Second and third columns (if present) contain color masks of text and background.  
If `colors` parameter is set to `none`, then only the first column exists.  
If `colors` parameter is set to `fg`, then there is also a second column with the color mask of the displayed text.  
If `colors` parameter is set to `bg`, then second column contains color mask of the background.  
If `colors` parameter is set to `full`, then there is both a second column with a text color mask and a third with a background color mask.  

Colors are indicated by a single symbol - a number in the 16-digit system (not case sensitive). Each color maps to one of the 16 ANSI colors.  
| 3a color number | ANSI color name | ANSI Foreground code | ANSI Background code |
| --- | --- | --- | --- |
| 0 | Black               | 30 | 40  |
| 1 | Blue                | 34 | 44  |
| 2 | Green               | 25 | 45  |
| 3 | Cyan                | 36 | 46  | 
| 4 | Red                 | 31 | 41  |
| 5 | Magenta             | 35 | 45  |
| 6 | Yellow              | 33 | 43  |
| 7 | White               | 37 | 47  |
| 8 | Bright Black (Gray) | 90 | 100 | 
| 9 | Bright Blue         | 94 | 104 |
| a | Bright Green        | 92 | 102 |
| b | Bright Cyan         | 96 | 106 |
| c | Bright Red          | 91 | 101 |
| d | Bright Magenta      | 95 | 105 |
| e | Bright Yellow       | 93 | 103 |
| f | Bright White        | 97 | 107 |

For historical reasons, the 3a colors go in a different order than the ANSI colors.

### Example
The general structure of a file with a looped animation of three frames of 3x4 characters using a palette of colors for both the background and the characters:
```
width 3
height 4
delay 100
loop true
colors full

[3 characters][foreground color mask][background color mask]
[3 characters][foreground color mask][background color mask]
[3 characters][foreground color mask][background color mask]
[3 characters][foreground color mask][background color mask]


[3 characters][foreground color mask][background color mask]
[3 characters][foreground color mask][background color mask]
[3 characters][foreground color mask][background color mask]
[3 characters][foreground color mask][background color mask]


[3 characters][foreground color mask][background color mask]
[3 characters][foreground color mask][background color mask]
[3 characters][foreground color mask][background color mask]
[3 characters][foreground color mask][background color mask]
```

Example 3a file with logo format animation:
```3a
	Header starts here
	Comments starts with tab char
width 13	Count of symbols in column
height 5	Count of rows in frames
loop true
colors full	Colors are specified for both text and background
delay 200
title 3a demo
author ASCIIMoth
@ In header comments also may starts with @ char



	There
	is
	one
	or
	more
	empty
	lines
	between
	header
	and
	body



	Body starts here
	First frame
             fffffffffffff0000000000000	First row
             fffffffffffff0000000000000	Second row
             fffffffffffff0000000000000	Third row
             fffffffffffff0000000000000
             fffffffffffff0000000000000

	Second frame
 _____       000000000fffffffffffff0000
             fffffffffffff0000000000000
             fffffffffffff0000000000000
             fffffffffffff0000000000000
             fffffffffffff0000000000000

	Third frame
 _____       fffffffff0fff000000000f000
|___ /  __   0000000000fffffffffffff000
             fffffffffffff0000000000000
             fffffffffffff0000000000000
             fffffffffffff0000000000000

 _____       ffffffffff0ff0000000000f00
|___ /  __   ffffffffff0ff0000000000f00
  |_ \ / _`  00000000000fffffffffffff00
             ffffffffffff00000000000000
             fffffffffffff0000000000000

 _____       fffffffffff0f00000000000f0
|___ /  __ _ fffffffffff0f00000000000f0
  |_ \ / _`  fffffffffff0f00000000000f0
 ___) | (_|  000000000000fffffffffffff0
             fffffffffffff0000000000000

 _____       ffffffffffff0000000000000f
|___ /  __ _ ffffffffffff0000000000000f
  |_ \ / _` |ffffffffffff0000000000000f
 ___) | (_| |ffffffffffff0000000000000f
|____/ \__,_|0000000000000fffffffffffff

 _____       fffffffffffff0000000000000
|___ /  __ _ fffffffffffff0000000000000
  |_ \ / _` |fffffffffffff0000000000000
 ___) | (_| |fffffffffffff0000000000000
|____/ \__,_|fffffffffffff0000000000000
```

## Other implementations
- [rs3a](https://github.com/DomesticMoth/rs3a) - Rust library for work with 3a format
- [py3a](https://github.com/DomesticMoth/py3a) - Python library for work with 3a format
- [go3a](https://github.com/DomesticMoth/go3a) - Golang library for work with 3a format
- [aaa](https://github.com/DomesticMoth/aaa) - Tui tool for 3a files rendering written with pure rust
- [convert3a](https://github.com/DomesticMoth/convert3a) - Tool for convert 3a animations to media formats 

# License
Files in this repository are distributed under the [CC0 license](./LICENSE).  
<p xmlns:dct="http://purl.org/dc/terms/">
  <a rel="license"
     href="http://creativecommons.org/publicdomain/zero/1.0/">
    <img src="http://i.creativecommons.org/p/zero/1.0/88x31.png" style="border-style: none;" alt="CC0" />
  </a>
  <br />
  To the extent possible under law,
  <a rel="dct:publisher"
     href="https://github.com/asciimoth">
    <span property="dct:title">asciimoth</span></a>
  has waived all copyright and related or neighboring rights to
  <span property="dct:title">3a</span>.
</p>
