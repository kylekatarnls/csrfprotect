<?php

class GenerateTagFunctionsTest extends \PHPUnit_Framework_TestCase
{
    public function testTagSyntax()
    {
        $tag = \CsrfProtect\getTag();
        $this->assertsame(substr($tag, 0, 6), '<input', 'The CSRF tag should start with <input');
        $this->assertsame(substr($tag, -1), '>', 'The CSRF tag should end with >');
        $tag = preg_replace('`\s+`', '', strtr($tag, '\'', '"'));
        $this->assertContains('name="', $tag, 'The CSRF tag should contains a name attribute');
        $this->assertContains('value="', $tag, 'The CSRF tag should contains a value attribute');
        $this->assertContains('type="hidden"', $tag, 'The CSRF tag should have the type hidden');
    }

    public function testTagNameAndValue()
    {
        $tag = \CsrfProtect\getTag();
        $tag = preg_replace('`\s+`', '', strtr($tag, '\'', '"'));
        $this->assertContains('name="' . \CsrfProtect\CsrfProtect::POST_KEY . '"', $tag, 'The CSRF tag name should be \CsrfProtect\CsrfProtect::POST_KEY');
        $this->assertTrue(preg_match('`value="([^"]*)"`', $tag, $value) > 0, 'The CSRF tag value should be catchable');
        $value = $value[1];
        $this->assertTrue(preg_match('`^[' . preg_quote(\CsrfProtect\CsrfProtect::TOKEN_CHARS) . ']+$`', $value) > 0, 'The CSRF tag value should only use chars in \CsrfProtect\CsrfProtect::TOKEN_CHARS');
        $this->assertSame(strlen($value), \CsrfProtect\CsrfProtect::TOKEN_LENGTH, 'The CSRF tag value length should be \CsrfProtect\CsrfProtect::TOKEN_LENGTH');
    }
}
