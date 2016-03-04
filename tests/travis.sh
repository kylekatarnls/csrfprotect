#!/bin/sh

sudo apt-get update
sudo apt-get install git gcc make re2c php5 php5-json php5-dev libpcre3-dev
git clone https://github.com/phalcon/zephir
cd zephir
./install-json
./install -c
cd ..
rm -r zephir
git clone https://github.com/kylekatarnls/csrfprotect
cd csrfprotect
zephir build
cd ..
rm -r csrfprotect
phpenv config-add tests/conf/php-csrfprotect.ini
