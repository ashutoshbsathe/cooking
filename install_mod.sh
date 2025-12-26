#!/bin/bash
set -e
set -x
source .env

MOD_NAME="p2agent"
# This should be steamapps dir on drive where steam is installed, not necessarily where portal 2 lives
MOD_ROOT_DIR="$STEAMAPPS_DIR/$MOD_NAME"

mkdir -p "$MOD_ROOT_DIR/cfg"
mkdir -p "$MOD_ROOT_DIR/maps/soundcache"

cp -r "$P2_ROOT_DIR/portal2_dlc2/maps/soundcache/_master.cache" "$MOD_ROOT_DIR/maps/soundcache"
cp gameinfo.txt "$MOD_ROOT_DIR/"
sed -i 's@portal2_dlc2$@'"\"$P2_ROOT_DIR"'/portal2_dlc2\"@g' "$MOD_ROOT_DIR/gameinfo.txt"
sed -i 's@portal2$@'"\"$P2_ROOT_DIR"'/portal2\"@g' "$MOD_ROOT_DIR/gameinfo.txt"
cp pak01_dir.vpk "$MOD_ROOT_DIR/"
cp -r cfg/ "$MOD_ROOT_DIR/"

tree "$MOD_ROOT_DIR"
