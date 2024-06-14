#! /bin/bash

echo -n "Input A:"; read A
echo -n "Input B:"; read B
echo -n "Input C:"; read C

V=`expr $A \* \( $B + $C \)`

echo "A * (B + C) = $V"
