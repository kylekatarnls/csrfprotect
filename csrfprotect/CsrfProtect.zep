namespace CsrfProtect;

class CsrfProtect
{
	const POST_KEY = "_csrf";
	const SESSION_PREFIX = "_csrf_";
	const TOKEN_LENGTH = 32;
	const TOKEN_CHARS = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890_-";
	const TOKENS_LIMIT = 5000;

	public static function checkPostToken(string identifier)
	{
		if empty _POST[CsrfProtect::POST_KEY] {
			return false;
		}

		return self::checkToken(_POST[CsrfProtect::POST_KEY], identifier);
	}

	public static function checkToken(string token, string identifier)
	{
		if ! session_id() {
			session_start();
		}

		if empty token {
			if empty _POST[CsrfProtect::POST_KEY] {
				return false;
			}
			let token = _POST[CsrfProtect::POST_KEY];
		}

		return isset(_SESSION[CsrfProtect::SESSION_PREFIX . identifier])
			&& is_array(_SESSION[CsrfProtect::SESSION_PREFIX . identifier])
			&& in_array(token, _SESSION[CsrfProtect::SESSION_PREFIX . identifier]);
	}

	public static function getToken(string identifier)
	{
		if ! session_id() {
			session_start();
		}

		string token = "";
		int charsCount = strlen(CsrfProtect::TOKEN_CHARS);
		int i = 0;
		while i < CsrfProtect::TOKEN_LENGTH {
			let token .= substr(CsrfProtect::TOKEN_CHARS, mt_rand(0, charsCount), 1);
			let i = i + 1;
		}

		if empty _SESSION[CsrfProtect::SESSION_PREFIX . identifier] {
			let _SESSION[CsrfProtect::SESSION_PREFIX . identifier] = [];
		} else {
			while count(_SESSION[CsrfProtect::SESSION_PREFIX . identifier]) > CsrfProtect::TOKENS_LIMIT {
				array_shift(_SESSION[CsrfProtect::SESSION_PREFIX . identifier]);
			}
		}
		array_push(_SESSION[CsrfProtect::SESSION_PREFIX . identifier], token);

		return token;
	}

	public static function getTag(string identifier)
	{
		string token;
		let token = self::getToken(identifier);

		return "<input type=\"hidden\" name=\"" . CsrfProtect::POST_KEY . "\" value=\"" . token . "\">";
	}
}
