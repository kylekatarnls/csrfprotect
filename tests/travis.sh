#!/bin/sh

phpenv config-add tests/conf/php-csrfprotect.ini
composer install --no-interaction --prefer-source --dev
cd csrfprotect
sudo ../vendor/bin/zephir build
