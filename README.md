# Animated Ascii Art (3a)
3A (Animated ASCII Art) is a straightforward, human-readable text format for
storing ASCII animations. It is disigned to be easy editable in any text editor
without spechial software needed. Espechially it textual representation preserves
art layout unlike plaintext with ANSI escape codes which is historically used to
store ASCII art.

- [3a_legacy_spec](./3a_legacy_spec.md) - is an old specification (currently implemented in most tools)
- [3a](./3a.md) - is a new spec

# Motivation
Back in 2020 I was ricing my linux system and planned to use ASCII animations
in rice.
For some reason, I assumed that there was a common file format for such
animations and tools for working with it, but it turned out that this was not
the case. Therefore, I developed 3a.

# Art Examples
[logo.3a](./logo.3a) is an official 3a format example.  
You can also find more 3a art [here](https://github.com/DomesticMoth/3a_storage).

# Software Implementations
- tools
    - [aaa](https://github.com/DomesticMoth/aaa) - Tui tool for 3a files rendering
    - [convert3a](https://github.com/DomesticMoth/convert3a) - Tool for convert 3a animations to media formats 
- libs
    - [rs3a](https://github.com/DomesticMoth/rs3a)
    - [py3a](https://github.com/DomesticMoth/py3a)
    - [go3a](https://github.com/DomesticMoth/go3a)

# Similar Projects
- [durdraw](https://github.com/cmang/durdraw) is a TUI ascii art editor with it's own format (gzipped json) with animations support.
- [nuru](https://github.com/domsson/nuru) is a binary ascii art format. Seems abandoned.

# TODO
- [MIME info](https://specifications.freedesktop.org/shared-mime-info) files
- Compact binary format

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
