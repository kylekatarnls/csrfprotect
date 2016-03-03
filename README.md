# CsrfProtect

PHP extencion to handle easily a really reliable CSRF protection

## Basic usage: Form protection

```php
<?php

use \CsrfProtect\CsrfProtect as Csrf;

session_start();

if (isset($_POST['message'])) {
	if (Csrf::checkToken()) {
		echo 'Thanks for your message!';
	} else {
		echo 'Sorry, your session expired.';
	}
}

?>
<form method="post" action="">
  <textarea name="message">
	<input type="submit">
	<?php echo Csrf::getTag(); ?>
</form>
```

## Authentificated user

```php
<?php

use \CsrfProtect\CsrfProtect as Csrf;

session_start();

if (isset($_POST['message'])) {
	if (Csrf::checkPostToken($_SESSION['user_id'])) {
		echo 'Thanks for your message!';
	} else {
		echo 'Sorry, your session expired or you have log out.';
	}
}

?>
<form method="post" action="">
  <textarea name="message">
	<input type="submit">
	<?php echo Csrf::getTag($_SESSION['user_id']); ?>
</form>
```

## Protect a link

```php
<?php

use \CsrfProtect\CsrfProtect as Csrf;

session_start();

if (isset($_POST['message'])) {
	if (Csrf::checkToken($_GET['_csrf'])) {
		echo 'Thanks for clicking!';
	} else {
		echo 'Sorry, your session expired.';
	}
}

?>
<a href="?_csrf=<?php echo Csrf::getToken(); ?>">Click here!</a>
```

## Protect a link with an authentificated user

```php
<?php

use \CsrfProtect\CsrfProtect as Csrf;

if (isset($_POST['message'])) {
	if (Csrf::checkToken($_GET['_csrf'], $_SESSION['user_id'])) {
		echo 'Thanks for clicking!';
	} else {
		echo 'Sorry, your session expired.';
	}
}

?>
<a href="?_csrf=<?php echo Csrf::getToken($_SESSION['user_id']); ?>">Click here!</a>
```

## Installation

You can install CsrfProtect anywhere Zephir can be installed.

Here is an example with Debian/Ubuntu (we suppose you have PHP installed):
```shell
sudo apt-get update
sudo apt-get install git gcc make re2c php5 php5-json php5-dev libpcre3-dev
git clone https://github.com/csrfprotect/zephir
cd zephir
./install-json
./install -c
```

(Optionnal) Then you can remove Zephir sources:
```shell
cd ..
rm -r zephir
```

Then check zephir is well installed:
```shell
zephir help
```

If it's not, please see: http://docs.zephir-lang.com/en/latest/install.html

Now you can download and build CsrfProtect
```shell
git clone https://github.com/kylekatarnls/csrfprotect.git
cd csrfprotect
zephir build
```

(Optionnal) Then you can remove CsrfProtect sources:
```shell
cd ..
rm -r csrfprotect
```

Then add extension=csrfprotect.so to your PHP configuration.
```ini
# Suse: Add a file called csrfprotect.ini in /etc/php5/conf.d/ with this content:
extension=csrfprotect.so

# CentOS/RedHat/Fedora: Add a file called csrfprotect.ini in /etc/php.d/ with this content:
extension=csrfprotect.so

# Ubuntu/Debian with apache2: Add a file called 30-csrfprotect.ini in /etc/php5/apache2/conf.d/ with this content:
extension=csrfprotect.so

# Ubuntu/Debian with php5-fpm: Add a file called 30-csrfprotect.ini in /etc/php5/fpm/conf.d/ with this content:
extension=csrfprotect.so

# Ubuntu/Debian with php5-cli: Add a file called 30-csrfprotect.ini in /etc/php5/cli/conf.d/ with this content:
extension=csrfprotect.so
```
