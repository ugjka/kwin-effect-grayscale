# kwin-effect-grayscale

![demo](https://raw.githubusercontent.com/ugjka/kwin-effect-grayscale/master/demo/demo.png "demo")

Turn the entire screen or a window in grayscale

## Shortcuts

CTRL + META + G for grayscaling the entire screen

CTRL + META + H for grayscaling the current window

You can change the shortcuts via System Settings -> Global Keyboard Shortcuts -> KWin

Or directly from the kwin effects settings menu

![menu](https://raw.githubusercontent.com/ugjka/kwin-effect-grayscale/master/demo/menu.png "menu")

## Installation

ArchLinux: [AUR](https://aur.archlinux.org/packages/kwin-effect-grayscale-git/)

### Manual build

You need extra-cmake-modules, kwin and kf5 packages installed

```bash
git clone https://github.com/ugjka/kwin-effect-grayscale.git
cd kwin-effect-grayscale
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_LIBDIR=lib ..
make
sudo make install
```

## TODO

add gamma correction feature
