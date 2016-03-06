<?php

use CsrfProtect\CsrfProtect as Csrf;

session_start();

$_SESSION = array();

$trues = array();
$falses = array();

session_destroy();
$trues[] = !session_id();

Csrf::getTokenIndex();
$falses[] = !session_id();
session_destroy();
$trues[] = !session_id();

Csrf::getToken();
$falses[] = !session_id();
session_destroy();
$trues[] = !session_id();

Csrf::getTag();
$falses[] = !session_id();
session_destroy();
$trues[] = !session_id();

Csrf::checkToken();
$falses[] = !session_id();
session_destroy();
$trues[] = !session_id();

Csrf::checkPostToken();
$trues[] = !session_id();
$_POST[Csrf::POST_KEY] = '-';
Csrf::checkPostToken();
$falses[] = !session_id();
session_destroy();
$trues[] = !session_id();

Csrf::isValidToken();
$falses[] = !session_id();
session_destroy();
$trues[] = !session_id();

Csrf::isValidToken();
$falses[] = !session_id();
session_destroy();
$trues[] = !session_id();

$_sessionTestsResults = (object) array(
    'trues' => $trues,
    'falses' => $falses,
);

unset($trues);
unset($falses);
