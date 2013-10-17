#Basic Plugin for Retroshare

This is currently a simple paint+chat plugin for retroshare.

It uses some code from several other plugins, including electrons paintchat plugin.

All data is sent using the "example" class - "encoded" as a string.

Mouse XY positions are sent rather than image diffs.

Expect mistakes, my C++ is very rusty, and im new to both QT and retroshare.



## Quick Start:

If you know what you are doing, do that!

###Install
####build
 #qmake-qt4;make
####deploy
 #cp lib* ~/.retroshare/extensions
####(Re)Start RS


###Usage
RS should detect the plugin, the top left pane will show friends also running the plugin.

click a friends ID to select them.

type, then press the button or paint to send your friend data.






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



