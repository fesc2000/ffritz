#!/bin/sh
#
# Stops pihole services in buildroot envoronment
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

echo +++ stopping lighttpd
ffdaemon -K lighttpd
echo +++ stopping pihole-FTL
kill `pidof pihole-FTL`
sleep 1
echo +++ restarting multid 
kill `pidof multid`
sleep 1
/sbin/multid
