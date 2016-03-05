#!/bin/sh

mkdir .build-travis
cd .build-travis
git clone https://github.com/phalcon/zephir
cd zephir
./install -c
cd ..
git clone https://github.com/kylekatarnls/csrfprotect
cd csrfprotect
sudo zephir build
cd ../..
rm -r .build-travis
composer install --no-interaction --prefer-source --dev
phpenv config-add tests/conf/php-csrfprotect.ini
