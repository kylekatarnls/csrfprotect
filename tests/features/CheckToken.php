<?php

use CsrfProtect\CsrfProtect as Csrf;

class CheckTokenTest extends \PHPUnit_Framework_TestCase
{
    public function testCheckPostToken()
    {
        $_POST[Csrf::POST_KEY] = Csrf::getToken();
        $this->assertTrue(Csrf::isValidToken(), 'The CSRF token should be valid');
        $this->assertTrue(Csrf::isValidToken(), 'The CSRF token should be valid again');
        $this->assertTrue(Csrf::checkPostToken(), 'The CSRF token should be checked');
        $this->assertFalse(Csrf::isValidToken(), 'The CSRF token should no longer be valid');
        $this->assertFalse(Csrf::checkPostToken(), 'The CSRF token should no longer be checked');
    }

    public function testCheckToken()
    {
        $token = Csrf::getToken();
        $this->assertTrue(Csrf::isValidToken($token), 'The CSRF token should be valid');
        $this->assertTrue(Csrf::isValidToken($token), 'The CSRF token should be valid again');
        $this->assertTrue(Csrf::checkToken($token), 'The CSRF token should be checked');
        $this->assertFalse(Csrf::isValidToken($token), 'The CSRF token should no longer be valid');
        $this->assertFalse(Csrf::checkToken($token), 'The CSRF token should no longer be checked');
        $this->assertFalse(Csrf::checkPostToken($token), 'The POST CSRF token should not be checked');
    }

    public function testIdentifiers()
    {
        $token1 = Csrf::getToken();
        $token2 = Csrf::getToken("foo");
        $token2a = Csrf::getToken("foo");
        $token2b = Csrf::getToken("foo");
        $token3 = Csrf::getToken(15);
        $_POST[Csrf::POST_KEY] = $token2;

        $this->assertTrue(Csrf::isValidToken($token1));
        $this->assertFalse(Csrf::isValidToken($token2));
        $this->assertFalse(Csrf::isValidToken($token3));

        $this->assertFalse(Csrf::isValidToken($token1, "foo"));
        $this->assertTrue(Csrf::isValidToken($token2, "foo"));
        $this->assertFalse(Csrf::isValidToken($token3, "foo"));

        $this->assertFalse(Csrf::isValidToken($token1, 15));
        $this->assertFalse(Csrf::isValidToken($token2, 15));
        $this->assertTrue(Csrf::isValidToken($token3, 15));

        $this->assertFalse(Csrf::isValidToken($token1, "bar"));
        $this->assertFalse(Csrf::isValidToken($token2, "bar"));
        $this->assertFalse(Csrf::isValidToken($token3, "bar"));

        $this->assertFalse(Csrf::checkPostToken());
        $this->assertTrue(Csrf::checkPostToken("foo"));
        $this->assertFalse(Csrf::checkPostToken("foo"));
        $this->assertFalse(Csrf::checkPostToken(15));

        $_POST[Csrf::POST_KEY] = $token2a;

        $this->assertTrue($token2a !== $token2);
        $this->assertFalse(Csrf::checkPostToken(''));
        $this->assertTrue(Csrf::checkPostToken('foo'));

        $this->assertTrue($token2b !== $token2);
        $this->assertFalse(Csrf::checkToken($token2b, 15));
        $this->assertTrue(Csrf::checkToken($token2b, 'foo'));
        $this->assertFalse(Csrf::checkToken($token2b, 'foo'));
    }
}
