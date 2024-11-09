#!/bin/bash
source .env

MOD_NAME="p2agent"
MOD_ROOT_DIR="$P2_ROOT_DIR/../../steamapps/sourcemods/$MOD_NAME"

echo $P2_ROOT_DIR
echo $MOD_ROOT_DIR

mkdir -p $MOD_ROOT_DIR/cfg
mkdir -p $MOD_ROOT_DIR/maps/soundcache

cp -r "$MOD_ROOT_DIR/maps/soundcache" "$P2_ROOT_DIR/portal2_dlc2/maps/soundcache"
