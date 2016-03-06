namespace CsrfProtect;

class CsrfProtect
{
    const POST_KEY = "_csrf";
    const SESSION_PREFIX = "_csrf_";
    const TOKEN_LENGTH = 32;
    const TOKEN_CHARS = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890_-";
    const TOKENS_LIMIT = 5000;

    protected static function initSession()
    {
        bool sessionStarted;
        let sessionStarted = version_compare(phpversion(), "5.4.0", ">=")
            ? (session_status() === PHP_SESSION_ACTIVE)
            : (session_id() !== "");
        if !sessionStarted && !headers_sent() {
            session_start();
        }
    }

    protected static function prefixedIdentifier(string identifier = "") -> string
    {
        return (string) constant(get_called_class() . "::SESSION_PREFIX") . identifier;
    }

    protected static function identifierExists(string identifier = "") -> boolean
    {
        return isset(_SESSION[identifier]) && is_array(_SESSION[identifier]);
    }

    public static function checkPostToken(string identifier = "") -> boolean
    {
        string postKey;
        let postKey = (string) constant(get_called_class() . "::POST_KEY");

        if !isset _POST[postKey] || empty _POST[postKey] {
            return false;
        }

        return self::checkToken(_POST[postKey], identifier);
    }

    public static function getTokenIndex(string token = "", string identifier = "") -> int | string | boolean
    {
        self::initSession();

        string postKey;
        let postKey = (string) constant(get_called_class() . "::POST_KEY");

        if empty token {
            if !isset _POST[postKey] || empty _POST[postKey] {
                return false;
            }
            let token = (string) _POST[postKey];
        }

        let identifier = self::prefixedIdentifier(identifier);

        if self::identifierExists(identifier) {
            return array_search(token, _SESSION[identifier]);
        }

        return false;
    }

    public static function checkToken(string token = "", string identifier = "") -> boolean
    {
        var key;
        let key = self::getTokenIndex(token, identifier);

        if key !== false {
            unset(_SESSION[self::prefixedIdentifier(identifier)][key]);
            return true;
        }

        return false;
    }

    public static function isValidToken(string token = "", string identifier = "") -> boolean
    {
        return self::getTokenIndex(token, identifier) !== false;
    }

    public static function getToken(string identifier = "") -> string
    {
        self::initSession();

        string tokenChars;
        let tokenChars = (string) constant(get_called_class() . "::TOKEN_CHARS");

        int tokenLength;
        let tokenLength = (int) constant(get_called_class() . "::TOKEN_LENGTH");

        string token = "";
        int charsCount;
        let charsCount = strlen(tokenChars) - 1;
        int i = 0;
        while i < tokenLength {
            let token .= substr(tokenChars, mt_rand(0, charsCount), 1);
            let i = i + 1;
        }

        let identifier = self::prefixedIdentifier(identifier);

        if ! self::identifierExists(identifier) {
            let _SESSION[identifier] = [];
        } else {
            int tokenLimit;
            let tokenLimit = (int) constant(get_called_class() . "::TOKENS_LIMIT");
            while count(_SESSION[identifier]) > tokenLimit {
                array_shift(_SESSION[identifier]);
            }
        }
        array_push(_SESSION[identifier], token);

        return token;
    }

    public static function getTag(string identifier = "") -> string
    {
        return "<input " .
            "type=\"hidden\" " .
            "name=\"" . constant(get_called_class() . "::POST_KEY") . "\" " .
            "value=\"" . self::getToken(identifier) . "\"" .
        ">";
    }
}
