# Car Monitor

## Development

Tips: to lint your code use:

```shell
make lint
```

Note: this command is available after a successfull `qmake` run and require `clang-format` binary.

## Global requirements

You need Qt 5.12.x installed through Qt official way:

1. Download http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
1. Change permissions (ie. `chmod +x qt-unified-linux*.run`)
1. Launch installer (ie. `./qt-unified-linux*.run`
1. Install whole needed things

## QtMqtt

```shell
git clone git://code.qt.io/qt/qtmqtt.git
cd qtmqtt
export PATH=$HOME/Qt/5.12.3/gcc_64/bin:$PATH
qmake
make -j4
make install
```

## QtMultimedia

You need a patched `qtmultimedia`:

1. Dowload

```shell
git clone git@gitlab.opus-codium.fr:carinsitu/qtmultimedia.git
cd qtmultimedia
```

2. Compile and install

```shell
export PATH=$HOME/Qt/5.12.3/gcc_64/bin:$PATH
qmake
make -j4
make install
```

## OpenAL

sudo apt-get install libopenal-dev

sudo apt-get install libalut0 libalut-dev
