<?php

use CsrfProtect\CsrfProtect as Csrf;

class SessionTest extends \PHPUnit_Framework_TestCase
{
    public function testSessionAutoStart()
    {
        $results = $GLOBALS['_sessionTestsResults'];

        array_walk($results->trues, array($this, 'assertTrue'));
        array_walk($results->falses, array($this, 'assertFalse'));
    }
}
