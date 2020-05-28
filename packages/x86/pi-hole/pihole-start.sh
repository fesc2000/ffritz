#!/bin/sh

# Multid configuration (which ports to move)
export LMD_CHANGE_DNS=1
export LMD_CHANGE_DHCP=1
#export LMD_CHANGE_LLMNR=1

test -r /usr/share/pihole  && { pihole not installed; exit 1; }

echo +++ killing multid
kill `pidof multid`


echo +++ starting pihole-FTL
pihole-FTL && { echo -- --- failed, restarting multid; /sbin/multid; exit 1 }

sleep 2

echo +++ Restarting multid
LD_PRELOAD=/usr/lib/libmultid.so /sbin/multid

echo +++ starting lighttpd
ffdaemon /usr/sbin/lighttpd -D -f /etc/lighttpd/lighttpd.conf 


echo +++ done, maybe
