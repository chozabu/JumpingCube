make clean
qmake-qt4
make clean
make
kdesudo -u retrotester cp libJumpingCube.so* /home/retrotester/.retroshare/extensions6/
kdesudo -u retrotester ../../retroshare-gui/src/RetroShare
