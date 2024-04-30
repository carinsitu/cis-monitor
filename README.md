:warning: **Depreciation note:** The code is now obsolete and the new *CarInSitu* version no longer uses this application.

# Car Monitor

## Development

Tips: to lint your code use:

```shell
make lint
```

Note: this command is available after a successfull `qmake` run and require `clang-format` binary.

## Global requirements

You need Qt 5.12.x installed through [Qt offline installer](https://www.qt.io/offline-installers):

1. Download https://download.qt.io/archive/qt/5.12/5.12.12/qt-opensource-linux-x64-5.12.12.run
1. Change permissions
    ```
    chmod +x qt-opensource-linux*.run
    ```
1. Launch installer
    ```
    ./qt-opensource-linux*.run`
    ```
1. Set destination path, please note following instructions assume your path is `~/Qt`
1. Install whole needed things
    * Qt 5.12.12 / Desktop gcc 64-bit
    * Qt 5.12.12 / Sources
    * Developer and Designer Tools

### Dependencies

_CIS monitor_ uses [OpenAL]() and [GStreamer]().

```
# Directly used by _CIS monitor_
sudo apt install libopenal-dev libalut0 libalut-dev
# Used by QtMultimedia
sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
```

### QtMqtt

```shell
git clone --branch 5.12.12 https://github.com/qt/qtmqtt.git
cd qtmqtt
export PATH=$HOME/Qt/5.12.12/gcc_64/bin:$PATH
qmake
make -j4
make install
```

### QtMultimedia

You need a patched `qtmultimedia`:

1. Dowload

```shell
git clone --branch carinsitu git@github.com:carinsitu/qtmultimedia.git
cd qtmultimedia
```

2. Compile and install

```shell
export PATH=$HOME/Qt/5.12.12/gcc_64/bin:$PATH
qmake
make -j4
make install
```
