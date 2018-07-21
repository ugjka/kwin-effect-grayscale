# kwin-effect-grayscale

Turn the entire screen or a window in grayscale

## Shortuts

CTRL + META + G for grayscaling the entire screen

CTRL + META + H for grayscaling the current window

You can change the shortcuts via System Settings -> Global Keyboard Shortcuts -> KWin

## Installation

ArchLinux PKGBUILD in the repo

### Manual

```bash
git clone https://github.com/ugjka/kwin-effect-grayscale.git
cd kwin-effect-grayscale
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_LIBDIR=lib ..
make
sudo make install
```

## TODO

* KCM config plugin
