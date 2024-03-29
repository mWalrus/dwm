# Wally's dwm config
A simple and cute dwm config with catppuccin colors c:

## Demo
![demo](./demo/screenshot.png)

## Install

### Dependencies
- [dmenu](https://tools.suckless.org/dmenu/) (can be replaced by modifying the code)
- [feh](https://github.com/derf/feh) (setting wallpaper)
- pulseaudio-alsa (for volume display in the bar)
- xdotool (local bookmarking)
- xclip (local bookmarking)
- OPTIONAL: [dunst](https://github.com/dunst-project/dunst)

### Status bar
1. clone the repo: `git clone https://github.com/mWalrus/slstatus`
2. `cd slstatus`
3. OPTIONAL: choose status config:
    - `git checkout laptop` (includes battery info)
4. `make && sudo make clean install`

### Dwm
1. clone the repo: `git clone https://github.com/mWalrus/dwm`
2. `cd dwm`
3. `make && sudo make clean install`
4. reboot
5. select `dwm` from your display manager

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
- [colstack](./patches/dwm-colstack-6.4.diff)
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
|PrtSc|Launch flameshot|Requires [flameshot](https://github.com/flameshot-org/flameshot)(screenshot tool)|
|Mod+b|Launch firefox|Requires firefox|
|Mod+d|Launch discord|Requires discord|
|Mod+c|Launch chatterino|Requires chatterino|
|Mod+Shift+Ctrl+h|Toggle bar||
|Mod+Shift+q|Kill focused client||
|Mod+Shift+p|Launch exit menu||
|Mod+q|Exit dwm|Double press to perform action|
|Mod+Shift+Up|Increase volume||
|Mod+Shift+Down|Decrease volume||
|Mod+Shift+Ctrl+m|Mute volume||
|Mod+h|Focus monitor left||
|Mod+l|Focus monitor right||
|Mod+Shift+h|Decrease master client width||
|Mod+Shift+l|Increase master client width||
|Mod+Shift+t|Default tiling layout||
|Mod+Shift+f|Floating layout||
|Mod+Shift+m|Monocle layout||
|Mod+Shift+b|Open bookmarks||
|Mod+Shift+Ctrl+b|Save bookmark|Takes currently selected text|
|Mod+Shift+x|Delete bookmark||
