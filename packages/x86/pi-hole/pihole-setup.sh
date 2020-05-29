#!/bin/sh

if [ ! -r /tmp/ffbuildroot.conf ]; then
	echo buildroot service not running
	exit 1
fi

. /tmp/ffbuildroot.conf

if [ -z $BR_USER_COPY ]; then
	echo buildroot service must be running in BR_USER_COPY mode
	exit 1
fi

if [ -d $BR_USER_COPY/pihole -a "$1" != "-f" ]; then
	echo pihole seems already installed, try -f to force
	exit 1
fi

test -r /usr/local/share/pihole  || { echo pihole not installed; exit 1; }
test -r $BR_USER_COPY/dev/shm || { echo /dev/shm does not exist; exit 1; }
test -r /usr/local/lib/libmultid.so || { echo /usr/lib/libmultid.so not installed; exit 1; }

lanip=`/sbin/ifconfig lan|grep 'inet addr:'|sed -e 's/.*inet addr:\([0-9.]*\).*/\1/'`
lanip6g=`/sbin/ifconfig lan|grep 'inet6 addr:'|grep Global|sed -e 's/.*inet6 addr:\(.*\)\/.*/\1/'`
lanip6l=`/sbin/ifconfig lan|grep 'inet6 addr:'|grep Local|sed -e 's/.*inet6 addr:\(.*\)\/.*/\1/'`

test -z $lanip && { echo failed to determine lan IP; exit 1; }

if [ -z $lanip6g ]; then
	if [ -z $lanip6l ]; then
		echo No local/global ipv6 address
		lanip6=::1
	else
		lanip6=$lanip6l
	fi
else
	lanip6=$lanip6g
fi


echo +++ Extracting template to $BR_USER_COPY
cd $BR_USER_COPY || exit 1
tar xf /usr/local/share/pihole/pihole-template.tar.gz || exit 1

sed -i -e "s@IPV4_ADDRESS=.*@IPV4_ADDRESS=$lanip/24@" $BR_USER_COPY/etc/pihole/setupVars.conf
sed -i -e "s@IPV6_ADDRESS=.*@IPV6_ADDRESS=$lanip6@" $BR_USER_COPY/etc/pihole/setupVars.conf

chmod 777 /tmp

mkdir -p $BR_USER_COPY/var/log/lighttpd/
chmod 777 $BR_USER_COPY/var/log/lighttpd/

mkdir -p $BR_USER_COPY/var/run/lighttpd/
chmod 777 $BR_USER_COPY/var/run/lighttpd/

chmod 777 $BR_USER_COPY/tmp

echo Ready to run pihole-start.sh

