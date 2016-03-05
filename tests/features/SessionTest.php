<?php

use CsrfProtect\CsrfProtect as Csrf;

class SessionTest extends \PHPUnit_Framework_TestCase
{
    public function testSessionAutoStart()
    {
        ob_start();

        session_write_close();
        $this->assertTrue(!session_id());

        Csrf::getTokenIndex();
        $this->assertFalse(!session_id());
        session_write_close();
        $this->assertTrue(!session_id());

        Csrf::getToken();
        $this->assertFalse(!session_id());
        session_write_close();
        $this->assertTrue(!session_id());

        Csrf::getTag();
        $this->assertFalse(!session_id());
        session_write_close();
        $this->assertTrue(!session_id());

        Csrf::checkToken();
        $this->assertFalse(!session_id());
        session_write_close();
        $this->assertTrue(!session_id());

        Csrf::checkPostToken();
        $this->assertFalse(!session_id());
        session_write_close();
        $this->assertTrue(!session_id());

        Csrf::isValidToken();
        $this->assertFalse(!session_id());
        session_write_close();
        $this->assertTrue(!session_id());

        Csrf::isValidToken();
        $this->assertFalse(!session_id());
        session_write_close();
        $this->assertTrue(!session_id());

        ob_end_clean();
    }
}
