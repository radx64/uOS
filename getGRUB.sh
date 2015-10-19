#!/bin/bash
mkdir build
cd build
mkdir tmp
cd tmp
wget ftp://alpha.gnu.org/gnu/grub/grub-0.97-i386-pc.tar.gz
tar -zxvf grub-0.97-i386-pc.tar.gz
rm grub-0.97-i386-pc.tar.gz
cp grub-0.97-i386-pc/boot/grub/stage2 ../stage2
cd ..
rm -rf tmp
