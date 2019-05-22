# Car Monitor

## QCamera based implementation

### Requiements

To use this implementation, you need Qt 5.12.x installed through Qt official way:

1. Download http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
1. Change permissions (ie. `chmod +x qt-unified-linux*.run`)
1. Launch installer (ie. `./qt-unified-linux*.run`
1. Install whole needed things

Next, you need a patched `qtmultimedia`:

1. Dowload

```shell
git clone git@gitlab.opus-codium.fr:carinsitu/qtmultimedia.git
cd qtmultimedia
git checkout fix-gstreamer-source-parsing
```

2. Compile and install

```shell
export PATH=$HOME/Qt/5.12.2/gcc_64/bin:$PATH
qmake
make -j4
make install
```

### Configure

This environment variable must be set in order to use UVC capture device (USB):

```shell
QT_GSTREAMER_CAMERABIN_VIDEOSRC=v4l2src ! jpegdec ! videoconvert
```

## libQtGStreamer based implementation

```shell
sudo apt install XXX
```
