<?php

use CsrfProtect\CsrfProtect as Csrf;

class GenerateTagTest extends \PHPUnit_Framework_TestCase
{
    public function testCheckPostToken()
    {
        $_POST[Csrf::POST_KEY] = Csrf::getToken();
        $this->assetTrue(Csrf::isValidToken(), 'The CSRF token should be valid');
        $this->assetTrue(Csrf::isValidToken(), 'The CSRF token should be valid again');
        $this->assetTrue(Csrf::checkPostToken(), 'The CSRF token should be checked');
        $this->assetFalse(Csrf::isValidToken(), 'The CSRF token should no longer be valid');
        $this->assetFalse(Csrf::checkPostToken(), 'The CSRF token should no longer be checked');
    }

    public function testCheckToken()
    {
        $token = Csrf::getToken();
        $this->assetTrue(Csrf::isValidToken($token), 'The CSRF token should be valid');
        $this->assetTrue(Csrf::isValidToken($token), 'The CSRF token should be valid again');
        $this->assetTrue(Csrf::checkToken($token), 'The CSRF token should be checked');
        $this->assetFalse(Csrf::isValidToken($token), 'The CSRF token should no longer be valid');
        $this->assetFalse(Csrf::checkToken($token), 'The CSRF token should no longer be checked');
        $this->assetFalse(Csrf::checkPostToken($token), 'The POST CSRF token should not be checked');
    }

    public function testIdentifiers()
    {
        $token1 = Csrf::getToken();
        $token2 = Csrf::getToken("foo");
        $token2a = Csrf::getToken("foo");
        $token2b = Csrf::getToken("foo");
        $token3 = Csrf::getToken(15);
        $_POST[Csrf::POST_KEY] = $token2;

        $this->assetTrue(Csrf::isValidToken($token1));
        $this->assetFalse(Csrf::isValidToken($token2));
        $this->assetFalse(Csrf::isValidToken($token3));

        $this->assetFalse(Csrf::isValidToken($token1, "foo"));
        $this->assetTrue(Csrf::isValidToken($token2, "foo"));
        $this->assetFalse(Csrf::isValidToken($token3, "foo"));

        $this->assetFalse(Csrf::isValidToken($token1, 15));
        $this->assetFalse(Csrf::isValidToken($token2, 15));
        $this->assetTrue(Csrf::isValidToken($token3, 15));

        $this->assetFalse(Csrf::isValidToken($token1, "bar"));
        $this->assetFalse(Csrf::isValidToken($token2, "bar"));
        $this->assetFalse(Csrf::isValidToken($token3, "bar"));

        $this->assetFalse(Csrf::checkPostToken());
        $this->assetTrue(Csrf::checkPostToken("foo"));
        $this->assetFalse(Csrf::checkPostToken("foo"));
        $this->assetFalse(Csrf::checkPostToken(15));

        $_POST[Csrf::POST_KEY] = $token2a;

        $this->assetTrue($token2a !== $token2);
        $this->assetFalse(Csrf::checkPostToken(''));
        $this->assetTrue(Csrf::checkPostToken('foo'));

        $this->assetTrue($token2b !== $token2);
        $this->assetFalse(Csrf::checkToken($token2b, 15));
        $this->assetTrue(Csrf::checkToken($token2b, 'foo'));
        $this->assetFalse(Csrf::checkToken($token2b, 'foo'));
    }
}
