# Wally's dwm config
A simple and cute dwm config with catppuccin colors c:

## Demo
![demo](./demo/screenshot.png)

## Install

### Dependencies
- [feh](https://github.com/derf/feh) (setting wallpaper)
- OPTIONAL: [dunst](https://github.com/dunst-project/dunst)

### Status bar
1. clone the repo: `git clone https://github.com/mWalrus/slstatus`
2. `cd slstatus`
3. OPTIONAL: choose status config:
    - `git checkout laptop` (includes battery info)
4. `make && sudo make clean install`

### dmenu
dmenu is used for the exit menu patch so it is needed for that to work.
However, if you want to use another menu for launching applications you can edit
`dmenucmd` in [config.h](./config.h).

Otherwise follow these steps:
1. clone the repo: `git clone https://github.com/mWalrus/dmenu`
2. `cd dmenu`
3. `make && sudo make clean install`

### Dwm
1. clone the repo: `git clone https://github.com/mWalrus/dwm`
2. `cd dwm`
3. `make && sudo make clean install`
4. reboot
5. select `dwm` from your display manager

### Dunst config
stand in this repository's directory:
1. `mkdir -p $HOME/.config/dunst`
2. `cp dunstrc $HOME/.config/dunst/`
3. reload dwm

## Spawn commands
The current spawn commands are:
- termcmd
- browsercmd
- discordcmd
- chatterinocmd
- flameshotcmd

These commands can be removed or modified in [config.h](./config.h) to your liking :)

## Patches applied
- [attachbottom](https://dwm.suckless.org/patches/attachbottom/)
- [colorbar](https://dwm.suckless.org/patches/colorbar/)
- [cool autostart](https://dwm.suckless.org/patches/cool_autostart/)
- [cursorwarp](https://dwm.suckless.org/patches/cursorwarp/)
- [exitmenu](https://dwm.suckless.org/patches/exitmenu/)
- [restartsig](https://dwm.suckless.org/patches/restartsig/)
- [statusallmons](https://dwm.suckless.org/patches/statusallmons/)
- [preserveonrestart](https://dwm.suckless.org/patches/preserveonrestart/)
- [doublepressquit](https://dwm.suckless.org/patches/doublepressquit/)
- [rotatestack](https://dwm.suckless.org/patches/rotatestack/)
- [statuspadding](https://dwm.suckless.org/patches/statuspadding/)

All `.diff` files can be found in the [patches/ directory](./patches).

## Keybinds
|Bind|Description|Notes|
|-|-|-|
|PrtSc|Launch flameshot (screenshot tool)|Requires [flameshot](https://github.com/flameshot-org/flameshot)|
|Mod+b|Launch firefox|Requires firefox|
|Mod+d|Launch discord|Requires discord|
|Mod+c|Launch chatterino|Requires chatterino|
|Mod+Shift+b|Toggle bar||
|Mod+Shift+q|Kill focused client||
|Mod+Shift+p|Launch exit menu||
|Mod+q|Exit dwm|Double press to perform action|
|Mod+Shift+Up|Increase volume||
|Mod+Shift+Down|Decrease volume||
|Mod+Shift+m|Mute volume||
