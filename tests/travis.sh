#!/bin/sh

apt-get update
apt-get install git gcc make re2c php5 php5-json php5-dev libpcre3-dev
git clone https://github.com/phalcon/zephir
cd zephir
./install-json
./install -c
cd ..
git clone https://github.com/kylekatarnls/csrfprotect
cd csrfprotect
zephir build
cd ..
phpenv config-add tests/conf/php-csrfprotect.ini
