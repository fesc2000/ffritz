#!/bin/sh
#
# Starts pihole services in buildroot envoronment
#

if [ ! -r /tmp/ffbuildroot.conf ]; then
	echo buildroot service not running
	exit 1
fi

. /tmp/ffbuildroot.conf

if [ -z $BR_USER_COPY ]; then
	echo buildroot service must be running in BR_USER_COPY mode
	exit 1
fi

# Multid configuration (which ports to move)
# For now only DNS
#
export LMD_CHANGE_DNS=1
#export LMD_CHANGE_DHCP=1
#export LMD_CHANGE_LLMNR=1

test -r $BR_USER_COPY/pihole  || { pihole not installed; exit 1; }

echo +++ killing multid
kill `pidof multid`

sleep 1

echo +++ starting pihole-FTL
br pihole-FTL 

sleep 2

if [ -z `pidof pihole-FTL` ]; then
	echo -- --- failed
	/sbin/multid
	exit 1
fi

echo +++ Restarting multid without dns/dhcp server
LD_PRELOAD=/usr/local/lib/libmultid.so /sbin/multid

echo +++ starting lighttpd
ffdaemon -o /tmp/br /usr/sbin/lighttpd -D -f /etc/lighttpd/lighttpd.conf 


echo +++ done, maybe
