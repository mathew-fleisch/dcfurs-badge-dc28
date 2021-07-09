#!/bin/bash

# Ensure xcode command line tools are up to date,
# by removing (if present), and installing from scratch
echo "(Re)Install xcode command line tools"
sudo rm -rf /Library/Developer/CommandLineTools
sudo xcode-select --install

# ------------------------------------- #

echo "Install (homebrew) dependencies"
# Install dfu-util to flash badge
brew install dfu-util

# Install 32-bit version of riscv tools (https://github.com/riscv/homebrew-riscv) to compile c to .bin
brew tap riscv/riscv
echo "This step (riscv-gnu-toolchain install) takes a long time..."
brew install riscv-gnu-toolchain --with-multilib

# ------------------------------------- #
echo "Install (pip) dependencies"
pip3 install Image

# Useful commands:
#   - Build and upload:
#     `./make.py build && ./make.py upload`
#
#   - Screen into console
#     `screen /dev/tty.usb[tab-to-get-device-id]`
#
#   - Quit out of screen session
#     `screen -X -S $(screen -ls | grep tty | awk '{print $1}') quit`
#
#   - Sometimes quitting out of screen sessions screws up the terminal formatting
#     Use this to fix the formatting issues:
#     `stty sane`