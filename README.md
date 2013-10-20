#JumpingCube Game (and some paintchat)

This is currently a simple game+paint+chat plugin for retroshare.

It is not intended for practical use - mostly as a project for me to get a handle on RS.

It uses some code from several other plugins, including electrons paintchat plugin.

All data is sent using the "example" class - "encoded" as a string.

Mouse XY positions are sent rather than image diffs.

Expect mistakes, my C++ is very rusty, and im new to both QT and retroshare. I also know I dropped some ugly hacks.
![My image](http://chozabu.net/stuff/jumpingcubepaint.png)

## Quick Start:

If you know what you are doing, do that!

###Install
####build
 #qmake-qt4;make
####deploy
 #cp lib* ~/.retroshare/extensions/
####(Re)Start RS


###Usage
RS should detect the plugin, the top left pane will show friends also running the plugin.

click a friends ID to select them.

type, then press the button or paint to send your friend data.
press "start game" to have a game of "jumpingcube" with friend.

learn the rules by playing!

I first saw this game on a then new-ish acorn.
A more recent implementation can be found here http://games.kde.org/game.php?game=kjumpingcube



## If you wish to test in a second instance of RetroShare
### Make a new user
```
  useradd retrotester
```
### Inspect then run the build and test script (KDE)
```
  cat testit.sh
  ./testit.sh
```
### Exit the new instance of retroshare when done testing



