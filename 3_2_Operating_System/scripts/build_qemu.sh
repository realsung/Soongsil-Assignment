QEMU_DIR="qemu"

sudo apt-get update
sudo apt-get install -y python2.7 build-essential gcc-multilib libglib2.0-dev libpixman-1-dev

git clone https://github.com/mit-pdos/6.828-qemu.git $QEMU_DIR
git submodule update --init pixman

cd $QEMU_DIR

POSIX_C=qga/commands-posix.c
TMP_POSIX_C=/tmp/commands-posix.c

#include <sys/sysmacros.h> 추가
cp $POSIX_C $TMP_POSIX_C
echo "#include <sys/sysmacros.h>" > $POSIX_C && cat $TMP_POSIX_C >> $POSIX_C
rm $TMP_POSIX_C

./configure --disable-kvm --disable-werror --target-list="i386-softmmu x86_64-softmmu" --python=/usr/bin/python2.7

make -j 8

QEMU_SYSTEM=`realpath i386-softmmu/qemu-system-i386`
echo "export QEMU=$QEMU_SYSTEM" >> $HOME/.bashrc
echo "export PATH=`pwd`:\$PATH" >> $HOME/.bashrc
