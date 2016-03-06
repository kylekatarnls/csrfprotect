<?php

class CheckTokenFunctionsTest extends \PHPUnit_Framework_TestCase
{
    public function testCheckPostToken()
    {
        $_POST[\CsrfProtect\CsrfProtect::POST_KEY] = \CsrfProtect\getToken();
        $this->assertTrue(\CsrfProtect\isValidToken(), 'The CSRF token should be valid');
        $this->assertTrue(\CsrfProtect\isValidToken(), 'The CSRF token should be valid again');
        $this->assertTrue(\CsrfProtect\checkPostToken(), 'The CSRF token should be checked');
        $this->assertFalse(\CsrfProtect\isValidToken(), 'The CSRF token should no longer be valid');
        $this->assertFalse(\CsrfProtect\checkPostToken(), 'The CSRF token should no longer be checked');
    }

    public function testCheckToken()
    {
        $token = \CsrfProtect\getToken();
        $this->assertTrue(\CsrfProtect\isValidToken($token), 'The CSRF token should be valid');
        $this->assertTrue(\CsrfProtect\isValidToken($token), 'The CSRF token should be valid again');
        $this->assertTrue(\CsrfProtect\checkToken($token), 'The CSRF token should be checked');
        $this->assertFalse(\CsrfProtect\isValidToken($token), 'The CSRF token should no longer be valid');
        $this->assertFalse(\CsrfProtect\checkToken($token), 'The CSRF token should no longer be checked');
        $this->assertFalse(\CsrfProtect\checkPostToken(), 'The POST CSRF token should not be checked');
    }

    public function testIdentifiers()
    {
        $token1 = \CsrfProtect\getToken();
        $token2 = \CsrfProtect\getToken("foo");
        $token2a = \CsrfProtect\getToken("foo");
        $token2b = \CsrfProtect\getToken("foo");
        $token3 = \CsrfProtect\getToken(15);
        $_POST[\CsrfProtect\CsrfProtect::POST_KEY] = $token2;

        $this->assertTrue(\CsrfProtect\isValidToken($token1));
        $this->assertFalse(\CsrfProtect\isValidToken($token2));
        $this->assertFalse(\CsrfProtect\isValidToken($token3));

        $this->assertFalse(\CsrfProtect\isValidToken($token1, "foo"));
        $this->assertTrue(\CsrfProtect\isValidToken($token2, "foo"));
        $this->assertFalse(\CsrfProtect\isValidToken($token3, "foo"));

        $this->assertFalse(\CsrfProtect\isValidToken($token1, 15));
        $this->assertFalse(\CsrfProtect\isValidToken($token2, 15));
        $this->assertTrue(\CsrfProtect\isValidToken($token3, 15));

        $this->assertFalse(\CsrfProtect\isValidToken($token1, "bar"));
        $this->assertFalse(\CsrfProtect\isValidToken($token2, "bar"));
        $this->assertFalse(\CsrfProtect\isValidToken($token3, "bar"));

        $this->assertFalse(\CsrfProtect\checkPostToken());
        $this->assertTrue(\CsrfProtect\checkPostToken("foo"));
        $this->assertFalse(\CsrfProtect\checkPostToken("foo"));
        $this->assertFalse(\CsrfProtect\checkPostToken(15));

        $_POST[\CsrfProtect\CsrfProtect::POST_KEY] = $token2a;

        $this->assertTrue($token2a !== $token2);
        $this->assertFalse(\CsrfProtect\checkPostToken(''));
        $this->assertTrue(\CsrfProtect\checkPostToken('foo'));

        $this->assertTrue($token2b !== $token2);
        $this->assertFalse(\CsrfProtect\checkToken($token2b, 15));
        $this->assertTrue(\CsrfProtect\checkToken($token2b, 'foo'));
        $this->assertFalse(\CsrfProtect\checkToken($token2b, 'foo'));
    }
}
