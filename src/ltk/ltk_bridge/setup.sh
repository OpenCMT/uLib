#!/bin/sh
module="ltkb"
device="ltkb"
mode="664"

/sbin/insmod ./$module.ko $* || exit 1

rm -f ./${device}[0-3]

major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

mknod ./${device}0 c $major 0
mknod ./${device}1 c $major 1
mknod ./${device}2 c $major 2
mknod ./${device}3 c $major 3

group="mutom"
grep -q '^mutom:' /etc/group || group="adm"

chgrp $group ./${device}[0-3]
chmod $mode ./${device}[0-3]