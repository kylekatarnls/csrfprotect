<?php

use CsrfProtect\CsrfProtect as Csrf;

class GenerateTagTest extends \PHPUnit_Framework_TestCase
{
    public function testTagSyntax()
    {
        $tag = Csrf::getTag();
        $this->assertsame(substr($tag, 0, 6), '<input', 'The CSRF tag should start with <input');
        $this->assertsame(substr($tag, -1), '>', 'The CSRF tag should end with >');
        $tag = preg_replace('`\s+`', '', strtr($tag, '\'', '"'));
        $this->assertContains('name="', $tag, 'The CSRF tag should contains a name attribute');
        $this->assertContains('value="', $tag, 'The CSRF tag should contains a value attribute');
        $this->assertContains('type="hidden"', $tag, 'The CSRF tag should have the type hidden');
    }

    public function testTagNameAndValue()
    {
        $tag = Csrf::getTag();
        $tag = preg_replace('`\s+`', '', strtr($tag, '\'', '"'));
        $this->assertContains('name="' . Csrf::POST_KEY . '"', $tag, 'The CSRF tag name should be Csrf::POST_KEY');
        $this->assetTrue(preg_match('`value="([^"]*)"`', $tag, $value) > 0, 'The CSRF tag value should be catchable');
        $value = $value[1];
        $this->assetTrue(preg_match('`^[' . preg_quote(Csrf::TOKEN_CHARS) . ']+$`', $value) > 0, 'The CSRF tag value should only use chars in Csrf::TOKEN_CHARS');
        $this->assetSame(strlen($value), Csrf::TOKEN_LENGTH, 'The CSRF tag value length should be Csrf::TOKEN_LENGTH');
    }
}
