namespace CsrfProtect;

class CsrfProtect
{
	const POST_KEY = "_csrf";
	const SESSION_PREFIX = "_csrf_";
	const TOKEN_LENGTH = 32;
	const TOKEN_CHARS = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890_-";
	const TOKENS_LIMIT = 5000;

	public static function checkToken(string identifier)
	{
		if ! session_id() {
			session_start();
		}

		return in_array(_POST[static::POST_KEY], _SESSION[static::SESSION_PREFIX . identifier]);
	}

	public static function getToken(string identifier)
	{
		if ! session_id() {
			session_start();
		}

		string token;
		int charsCount = strlen(static::TOKEN_CHARS);
		for int i = 0; i < static::TOKEN_LENGTH; i++ {
			token .= substr(static::TOKEN_CHARS, mt_rand(0, charsCount), 1);
		}

		if empty _SESSION[static::SESSION_PREFIX . identifier] {
			_SESSION[static::SESSION_PREFIX . identifier] = [];
		} else {
			while count(_SESSION[static::SESSION_PREFIX . identifier]) > static::TOKENS_LIMIT {
				array_shift(_SESSION[static::SESSION_PREFIX . identifier]);
			}
		}
		_SESSION[static::SESSION_PREFIX . identifier][] = token;

		return token;
	}
}
