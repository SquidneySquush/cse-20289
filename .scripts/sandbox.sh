#!/bin/sh

SANDBOX=sandbox
IMAGE=pbui/cse-20289-sp20

if [ ! -d "$SANDBOX" ]; then
    mkdir -p "$SANDBOX"
fi

cp -f $@ "$SANDBOX"
docker run -it -w /sandbox -v "$(readlink -f $SANDBOX)":/sandbox $IMAGE /bin/bash

# vim: set sts=4 sw=4 ts=8 expandtab ft=sh:
