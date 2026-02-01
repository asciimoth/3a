This spec describes original **deprecated** 3a version.

# Specification
A 3A file has two sections: the header, which contains metadata, and the body, which holds the artwork itself. These are separated by one or more blank lines.

## Unicode
For clarity:
A `grapheme` refers to a Unicode grapheme cluster.  
`Char` or `symbol` denotes a Unicode code point.  

## Comments
Text following a tab character to the line's end is considered a comment and should be ignored.

## Header
The header lists parameters line by line without blank lines (as they separate header and body). Each line has a parameter name followed by its arguments, separated by spaces.  
General format: [name] [arg 1] [arg 2] [arg n]  
Example: `width 10`  
  
Mandatory parameters (must be in any 3a file):
- `width` - Width of the art in characters(unsigned 16-bit integer)
- `height` - Height of the art in characters(unsigned 16-bit integer)
  
Optional parameters:
- `delay` - (unsigned 16-bit decimal integer) Delay between rendering animation frames in milliseconds. By default is 50.
- `loop` - (str `true` or `false`) Animation looping. By default is `true`.
- `colors` - (str) Color palette type.
  - `none` -  No colors specified. (Default)
  - `fg` - Only text colors specified.
  - `bg` - Only background colors specified.
  - `full` - Both text and background colors specified.
- `@` - Ignored parameter. Another way to leave comments in addition to the lines starting with tab.
- `preview` - (unsigned 16-bit decimal integer) Frame number (starts from 0) for static preview. By default is 0.
- `title` - (str) Title of art.
- `author` - (str) Author of art.
- `#` - (str) tag. Each argument of this parameter denotes a different tag. Tags should be deduplicated while parsing.
  
All unknown parameters should be ignored.  
All parameters with incorrect arguments(except `width` and `height`) should be ignored.   
For repeated parameters, only consider the first instance.  

## Body
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

Colors are denoted by a single hexadecimal digit (case unsensitive), corresponding to one of the 16 ANSI colors. The mapping between 3a color numbers and ANSI colors is as follows:
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

## Example
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

Also check [3a logo](./logo.3a)
