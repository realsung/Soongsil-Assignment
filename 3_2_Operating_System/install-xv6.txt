sudo apt-get update
sudo apt-get install python2.7 build-essential gcc-multilib libglib2.0-dev libpixman-1-dev

git clone https://github.com/mit-pdos/6.828-qemu.git qemu
git submodule update --init pixman

qga/commands-posix.c
#include <sys/sysmacros.h> 추가

./configure --disable-kvm --disable-werror --prefix=/home/<path-you-want>/qemu-install --target-list="i386-softmmu x86_64-softmmu" --python=/usr/bin/python2.7

make -j 8

vi ~/.bashrc
export PATH=/home/to/path:$PATH

git clone git://github.com/mit-pdos/xv6-public.git

make qemu-nox