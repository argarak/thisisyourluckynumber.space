#!/bin/bash

wget -q -N http://thisisyourluckynumber.space/user -O user.tmp

if cmp -s user user.tmp; then
    :
else
    cat user.tmp > user;
fi
