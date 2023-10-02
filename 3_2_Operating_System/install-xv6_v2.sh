# system environment install

sudo apt-get update
sudo apt-get install git python2.7 build-essential gcc-multilib libglib2.0-dev libpixman-1-dev libjpeg9

#install qemu & xv6 
git clone https://github.com/mit-pdos/6.828-qemu.git qemu
git clone https://github.com/mit-pdos/xv6-public.git xv6
cd qemu && git submodule update --init pixman


vi qga/commands-posix.c
#include <sys/sysmacros.h> 추가

#Configure for QEMU build
./configure --disable-kvm --disable-werror --target-list="i386-softmmu x86_64-softmmu" --python=/usr/bin/python2.7

#Build QEMU
make -j 8

#Environment PATH setting for QEMU
#NEED TO CHANGE <path-to-qemu> to your qemu path (e.g., /home/yhgong/qemu)
vi ~/.bashrc
export QEMU=/vagrant/3_2_Operating_System/qemu/i386-softmmu/qemu-system-i386
export PATH=/vagrant/3_2_Operating_System/qemu:$PATH
source ~/.bashrc

#Run XV6 on QEMU

cd xv6 
make qemu-nox QEMU=$QEMU


#(optional) if libtinfow.so.6 error occurred
sudo ln -s /lib/x86_64-linux-gnu/libtic.so.6.2 /lib/x86_64-linux-gnu/libtinfow.so.6
