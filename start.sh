#!/bin/bash
echo $1 > .new_pass
./a.out
./cpass.sh
./install.sh $1 $2