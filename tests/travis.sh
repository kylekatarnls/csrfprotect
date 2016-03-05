#!/bin/sh

git clone https://github.com/phalcon/zephir
cd zephir
./install-json
./install -c
cd ..
git clone https://github.com/kylekatarnls/csrfprotect
cd csrfprotect
sudo zephir build
cd ..
composer install --no-interaction --prefer-source --dev
phpenv config-add tests/conf/php-csrfprotect.ini
