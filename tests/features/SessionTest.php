<?php

use CsrfProtect\CsrfProtect as Csrf;

if (!class_exists('SessionTest', false))
{
    return;
}

class SessionTest extends \PHPUnit_Framework_TestCase
{
    public function testSessionAutoStart()
    {
        session_destroy();
        $this->assetTrue(!session_id());

        Csrf::getTokenIndex();
        $this->assetFalse(!session_id());
        session_destroy();
        $this->assetTrue(!session_id());

        Csrf::getToken();
        $this->assetFalse(!session_id());
        session_destroy();
        $this->assetTrue(!session_id());

        Csrf::getTag();
        $this->assetFalse(!session_id());
        session_destroy();
        $this->assetTrue(!session_id());

        Csrf::checkToken();
        $this->assetFalse(!session_id());
        session_destroy();
        $this->assetTrue(!session_id());

        Csrf::checkPostToken();
        $this->assetFalse(!session_id());
        session_destroy();
        $this->assetTrue(!session_id());

        Csrf::isValidToken();
        $this->assetFalse(!session_id());
        session_destroy();
        $this->assetTrue(!session_id());

        Csrf::isValidToken();
        $this->assetFalse(!session_id());
        session_destroy();
        $this->assetTrue(!session_id());
    }
}
