#!/bin/bash

#get password from ".password" file
password=$(cat .password) 
pass_len=${#password}
pass=${password:0:$pass_len-1}

#get new password from ".new_pass" file
new_pass=$(cat .new_pass)

#Change password with "sudo passwd"
echo -e "$pass\n$new_pass\n$new_pass" | passwd -q

#Delete output of previous operation
clear