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
- 3a supports 8 colors for background and 16 colors for characters
- 3a only supports ASCII characters because it must be compatible with ncurses
- 3a format has a small, but existing possibility for extension

## Reasons
While customizing my *nix system, I was going to actively use ascii animations for styling. I expected that there is a widespread text format for storing animated ascii art. But it turned out that this was not the case. So I had to create it.

## More art
You can find more 3a art [here](https://github.com/DomesticMoth/3a_storage)

## Specification
3a file consists of two parts: the header and the body. The header contains the metadata of the art and the body contains the art itself. The header is separated from the body by one or more empty lines.  

### Comments
The text starting from the tab character and up to the end of the line should be ignored. So it can be used as comments.

### Header
The header contains parameters. Each parameter is on a separate line. There should be no empty lines between the parameter lines (because it is header and body separator). The parameter line consists of the parameter name and its arguments separated by one or more spaces.  
General structure of the parameter: `[name] [arg 1] [arg 2] [arg n]`  
Example: `width 10`  

Required parameters (must be in any 3a file):
- width - Width of the art in characters(unsigned 16-bit integer)
- height - Height of the art in characters(unsigned 16-bit integer)

Optional parameters:
- delay - Delay between rendering animation frames in milliseconds (unsigned 16-bit integer). By default is 50.
- loop - Need to loop the animation (str "true" or "false"). By default is true.
- colors - The type of color palette (str). Accepts one of the following arguments (by default is "none"):
  - none - Colors are not specified.
  - fg - Сolors are specified for text only.
  - bg - Сolors are specified only for the background.
  - full - Colors are specified for both text and background.
- @ - Ignored parmeter. Another way to leave comments in addition to the lines starting with tab.
- utf8 - Some implementations may have utf8 support, despite limiting the format to ascii characters only. If you create art only for such implementations, add this parameter to your header.
- datacols - Number of columns with information (unsigned 16-bit integer). Use this parameter in format extensions. By default, it is calculated from the colors parameter.
- preview - Frame number (starting from 0) that should be shown as a static preview of the animation (unsigned 16-bit integer). By default is 0.
- title - Title of art (str).
- author - Author of art (str).

All unknown parameters should be ignored.  
All parameters with incorrect arguments(except width and height) should be ignored.   

### Body
Tabs, line breaks, escape sequences, and any other control characters should be ignored in the file body.   
File body consists of frames that consist of rows that consist of columns.  
Each frame consists of $height rows.  
Each row consists of one or more columns.  
Each column consists of $width characters.  
Each column describes one type of information about the line displaying on the screen.  
First column always contains characters drawn on the screen. Second and third columns (if present) contain color masks of text and background.  
If $colors is set to "none", then only the first column exists.  
If $colors is set to "fg", then there is also a second column with the color mask of the displayed text.  
If $colors is set to "bg", then second column contains color mask of the background.  
If $colors is set to "full", then there is both a second column with a text color mask and a third with a background color mask.  

Colors are indicated by a single symbol - a number in the 16-digit system.  
Matching a number to a color:
- 0 BLACK
- 1 BLUE
- 2 GREEN
- 3 CYAN
- 4 RED
- 5 MAGENTA
- 6 YELLOW
- 7 WHITE
- 8 GRAY
- 9 BRIGHT_BLUE
- a BRIGHT_GREEN
- b BRIGHT_CYAN
- c BRIGHT_RED
- d BRIGHT_MAGENTA
- e BRIGHT_YELLOW  
- f BRIGHT_WHITE 

Background support only [0-7] colors. Text support support all 16 colors.  

### Example
The general structure of a file with a looped animation of three frames of 3x4 characters using a palette of colors for both the background and the characters:
```
width 3
height 4
delay 100
loop true
colors full

[characters][text color mask][background color mask]
[characters][text color mask][background color mask]
[characters][text color mask][background color mask]
[characters][text color mask][background color mask]


[characters][text color mask][background color mask]
[characters][text color mask][background color mask]
[characters][text color mask][background color mask]
[characters][text color mask][background color mask]


[characters][text color mask][background color mask]
[characters][text color mask][background color mask]
[characters][text color mask][background color mask]
[characters][text color mask][background color mask]
```

Example 3a file with logo format animation:
```
	Header starts here
	Comments starts with tab char
width 22	Count of symbols in column
height 14	Count of rows in frames
loop true
colors full	Colors are specified for both text and background
delay 300
title 3a demo
author Moth
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
LU]Pk&3):F*k[]qbd;$0Bp77777777777777777777770000000000000000000000	First row
}YZ7Ik;=a^KF(0CxvF5AU+77777777777777777777770000000000000000000000	Second row
uPJZ]RJ3]^xsyJ~-;2~.dW777777cccccc77777777770000003333330000000000	Third row
pj&<rH.vFN6odJ5c-l~CRx777777cccccc77777777770000003333330000000000
A!ht(UB@(jNDl.67+n)?,N7777777777cc77cccccc770000000000330033333300
v6,gTX64AWFW>%>IdAxSgW7777777777cc77cccccc770000000000330033333300
}[FiPQzkcMdG@K!<@dvC-$777777cccccc77cc77cc770000003333330033003300
C:DT+Odt-P(0pu%r}vlr#H777777cccccc77cc77cc770000003333330033003300
wAD)<iMp>L}yh}Y+}-r$BN7777777777cc77cccccc770000000000330033333300
@,ekE:w[Xt8sCmxxFj9EHN7777777777cc77cccccc770000000000330033333300
rX7=W;uEZii2*xosZuDRBg77cc77cccccc77cc77cc770033003333330033003300
vHtkD411dJ>P~3=kkB4wU^77cc77cccccc77cc77cc770033003333330033003300
,6oFB+gD3f_%gJua{50=HD77777777777777777777770000000000000000000000
rq5?T0lL06Vg-[0G:,sum)77777777777777777777770000000000000000000000

	Second frame
lH<^&?@^Hbt^3v5]7gx9<o	First column in a first row
7777777777777777777777	Second column in a first row
0000000000000000000000	Third column in a first row
hoB<mg>DGKGfM3woWh4%EC77777777777777777777770000000000000000000000
Js%6!JG[m,C8PVsrG7_ESx777777cccccc77777777770000003333330000000000
dCX<E6]xxP~Hk(([D*dGU?777777cccccc77777777770000003333330000000000
~!gdx`w[f0z)xKbnj{rAWS7777777777cc77cccccc770000000000330033333300
5V=hf%`00gl2-YlT;L*&U`7777777777cc77cccccc770000000000330033333300
qk[3_hDMUNNIn}Y`F>lh@o777777cccccc77cc77cc770000003333330033003300
HsHD0=38OO.#iCA&~U[{kT777777cccccc77cc77cc77
0000003333330033003300v#x@h.OzV,zLI6#5&kv4T-777777777	You can add line breaks anywhere in the body.
7cc77cccccc770000000000330033333300			Any way they, like comments, are ignored by the parser.
#t:Gic$*w-i;P<O!fIWdC,7777777777cc77cccccc770000000000330033333300
zs{lk^a3Ty8SbYgLGe7Pdt77cc77cccccc77cc77cc770033003333330033003300
i#%5(w~u9+cdlOdO!&Ms}677cc77cccccc77cc77cc770033003333330033003300
Ou=JC8Zn.T;pq98cx)ov>~77777777777777777777770000000000000000000000
aNvuQi.U6%7-Kf,uk{FG[J77777777777777777777770000000000000000000000

	Third frame
Jk%bTX:]aZ,D?jkB0?*I*O77777777777777777777770000000000000000000000
r~&Em{~S%FVCv._]xdt5.,77777777777777777777770000000000000000000000
OEr=o[s:ocqCa;,h2a-d:q777777cccccc77777777770000003333330000000000
U6]~]fX>~%T%(RAa$p`~n!777777cccccc77777777770000003333330000000000
YRq`hu=gRKg.!k>82v#[^D7777777777cc77cccccc770000000000330033333300
C#F7Nq3U3!yopFgBSRoUPB7777777777cc77cccccc770000000000330033333300
)p_U9Fhxi]W1IE)=s$>dh^777777cccccc77cc77cc770000003333330033003300
8uhRPgAy2}uioTM5Rw@>*5777777cccccc77cc77cc770000003333330033003300
xgq#T=V5d}8WaQU+kez]>X7777777777cc77cccccc770000000000330033333300
ed`pS6%DK9N% iQo7-[gDO7777777777cc77cccccc770000000000330033333300
[Z:jGUY%L&$74[@Q8;Km~E77cc77cccccc77cc77cc770033003333330033003300
gQ{ikr-5fyM<{ny6=]r4U$77cc77cccccc77cc77cc770033003333330033003300
iVG.vOv5uWkulYY#GT[&Tm77777777777777777777770000000000000000000000
U0DC_D-@ml4[7sP7&)C9Q>77777777777777777777770000000000000000000000
```

And this is how the render of this art looks:  
![3a demo](https://i.imgur.com/a013QHv.gif)

### Creating extensions
You can create your own format extensions by adding parameters and data columns. Use the "datacols" and maybe "colors none" parameter to save partial compatibility of your extension with the original format.  
## Reference implementation
This repository also provides an example of a TUI tool for rendering 3a animations.

### Dependencies
You will need the ncurses library version 4 and higher.  

### Installation
1) Clone this repo `$ git clone https://github.com/DomesticMoth/3a.git`
2) Build `$ make build`
3) Install `$ make install`

### Usage  
Run `3a <file.3a>` where <file.3a> is is an animation file, to play it.
Run `3a -c` to show demo colortable with all combinations of foreground and background colors.
Run `3a --help` to see other options.
```
Usage: 3a [OPTION...]
TUI tool for playng .3a animations.

  -c, --colortable           Show colortable
  -d, --delay=NUM            Force frames draw delay
  -l, --loop                 Enable loop mode
  -n, --noloop               Disable loop mode
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.
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
