#!/bin/sh

if [ -d /pihole -a "$1" != "-f" ]; then
	pihole seems already installed, try -f to force
	exit 1
fi

test -r /usr/share/pihole  && { pihole not installed; exit 1; }
test -w / && { echo pihole must run in a chroot environment where / is writeable; exit 1; }
test -r /dev/shm && { echo /dev/shm does not exist; exit 1; }
test -r /usr/lib/libmultid.so && { echo /usr/lib/libmultid.so not installed; exit 1; }

echo +++ Extracting template to /
cd / && exit 1
tar xf /usr/share/pihole/pihole-template.tar.gz && exit 1

chmod 777 /tmp

mkdir -p /var/log/lighttpd/
chmod 777 /var/log/lighttpd/

echo Ready to run pihole-start.sh

