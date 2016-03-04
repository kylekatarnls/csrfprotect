
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/math.h"


ZEPHIR_INIT_CLASS(CsrfProtect_CsrfProtect) {

	ZEPHIR_REGISTER_CLASS(CsrfProtect, CsrfProtect, csrfprotect, csrfprotect, csrfprotect_csrfprotect_method_entry, 0);

	zend_declare_class_constant_string(csrfprotect_csrfprotect_ce, SL("POST_KEY"), "_csrf" TSRMLS_CC);

	zend_declare_class_constant_string(csrfprotect_csrfprotect_ce, SL("SESSION_PREFIX"), "_csrf_" TSRMLS_CC);

	zend_declare_class_constant_long(csrfprotect_csrfprotect_ce, SL("TOKEN_LENGTH"), 32 TSRMLS_CC);

	zend_declare_class_constant_string(csrfprotect_csrfprotect_ce, SL("TOKEN_CHARS"), "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890_-" TSRMLS_CC);

	zend_declare_class_constant_long(csrfprotect_csrfprotect_ce, SL("TOKENS_LIMIT"), 5000 TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(CsrfProtect_CsrfProtect, prefixedIdentifier) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *identifier_param = NULL, *_0, *_1, *_2 = NULL;
	zval *identifier = NULL, *_3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &identifier_param);

	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_INIT_VAR(_0);
	zephir_get_called_class(_0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_VS(_1, _0, "::SESSION_PREFIX");
	ZEPHIR_CALL_FUNCTION(&_2, "constant", NULL, 1, _1);
	zephir_check_call_status();
	zephir_get_strval(_3, _2);
	ZEPHIR_CONCAT_VV(return_value, _3, identifier);
	RETURN_MM();

}

PHP_METHOD(CsrfProtect_CsrfProtect, identifierExists) {

	zend_bool _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *identifier_param = NULL, *_SESSION, *_0 = NULL, *_2;
	zval *identifier = NULL;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
	zephir_fetch_params(1, 0, 1, &identifier_param);

	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_CALL_SELF(&_0, "prefixedidentifier", NULL, 0, identifier);
	zephir_check_call_status();
	zephir_get_strval(identifier, _0);
	_1 = zephir_array_isset(_SESSION, identifier);
	if (_1) {
		zephir_array_fetch(&_2, _SESSION, identifier, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 21 TSRMLS_CC);
		_1 = Z_TYPE_P(_2) == IS_ARRAY;
	}
	RETURN_MM_BOOL(_1);

}

PHP_METHOD(CsrfProtect_CsrfProtect, checkPostToken) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *identifier_param = NULL, *_POST, *_0, *_1, *_2 = NULL, *_4, *_5;
	zval *identifier = NULL, *postKey = NULL, *_3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
	zephir_fetch_params(1, 0, 1, &identifier_param);

	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_INIT_VAR(_0);
	zephir_get_called_class(_0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_VS(_1, _0, "::POST_KEY");
	ZEPHIR_CALL_FUNCTION(&_2, "constant", NULL, 1, _1);
	zephir_check_call_status();
	zephir_get_strval(_3, _2);
	ZEPHIR_CPY_WRT(postKey, _3);
	zephir_array_fetch(&_4, _POST, postKey, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 29 TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(_4)) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch(&_5, _POST, postKey, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 33 TSRMLS_CC);
	ZEPHIR_RETURN_CALL_SELF("checktoken", NULL, 0, _5, identifier);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(CsrfProtect_CsrfProtect, getTokenIndex) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *token_param = NULL, *identifier_param = NULL, *_POST, *_SESSION, *_0 = NULL, *_1, *_2, *_3 = NULL, *_8 = NULL, *_5$$4, *_6$$4, *_9$$6, *_10$$6 = NULL;
	zval *token = NULL, *identifier = NULL, *postKey = NULL, *_4 = NULL, *_7$$4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
	zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
	zephir_fetch_params(1, 0, 2, &token_param, &identifier_param);

	if (!token_param) {
		ZEPHIR_INIT_VAR(token);
		ZVAL_STRING(token, "", 1);
	} else {
		zephir_get_strval(token, token_param);
	}
	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_CALL_FUNCTION(&_0, "session_id", NULL, 2);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_CALL_FUNCTION(NULL, "session_start", NULL, 3);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_1);
	zephir_get_called_class(_1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_VS(_2, _1, "::POST_KEY");
	ZEPHIR_CALL_FUNCTION(&_3, "constant", NULL, 1, _2);
	zephir_check_call_status();
	zephir_get_strval(_4, _3);
	ZEPHIR_CPY_WRT(postKey, _4);
	if (ZEPHIR_IS_EMPTY(token)) {
		zephir_array_fetch(&_5$$4, _POST, postKey, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 46 TSRMLS_CC);
		if (ZEPHIR_IS_EMPTY(_5$$4)) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_OBS_VAR(_6$$4);
		zephir_array_fetch(&_6$$4, _POST, postKey, PH_NOISY, "csrfprotect/CsrfProtect.zep", 49 TSRMLS_CC);
		zephir_get_strval(_7$$4, _6$$4);
		ZEPHIR_CPY_WRT(token, _7$$4);
	}
	ZEPHIR_CALL_SELF(&_8, "identifierexists", NULL, 0, identifier);
	zephir_check_call_status();
	if (zephir_is_true(_8)) {
		ZEPHIR_CALL_SELF(&_10$$6, "prefixedidentifier", NULL, 0, identifier);
		zephir_check_call_status();
		zephir_array_fetch(&_9$$6, _SESSION, _10$$6, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 53 TSRMLS_CC);
		ZEPHIR_RETURN_CALL_FUNCTION("array_search", NULL, 4, token, _9$$6);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

PHP_METHOD(CsrfProtect_CsrfProtect, checkToken) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *token_param = NULL, *identifier_param = NULL, *_SESSION, *key = NULL, *_0$$3, *_1$$3 = NULL;
	zval *token = NULL, *identifier = NULL;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
	zephir_fetch_params(1, 0, 2, &token_param, &identifier_param);

	if (!token_param) {
		ZEPHIR_INIT_VAR(token);
		ZVAL_STRING(token, "", 1);
	} else {
		zephir_get_strval(token, token_param);
	}
	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_CALL_SELF(&key, "gettokenindex", NULL, 0, token, identifier);
	zephir_check_call_status();
	if (!ZEPHIR_IS_FALSE_IDENTICAL(key)) {
		ZEPHIR_CALL_SELF(&_1$$3, "prefixedidentifier", NULL, 0, identifier);
		zephir_check_call_status();
		zephir_array_fetch(&_0$$3, _SESSION, _1$$3, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 65 TSRMLS_CC);
		zephir_array_unset(&_0$$3, key, PH_SEPARATE);
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

PHP_METHOD(CsrfProtect_CsrfProtect, isValidToken) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *token_param = NULL, *identifier_param = NULL, *_0 = NULL;
	zval *token = NULL, *identifier = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &token_param, &identifier_param);

	if (!token_param) {
		ZEPHIR_INIT_VAR(token);
		ZVAL_STRING(token, "", 1);
	} else {
		zephir_get_strval(token, token_param);
	}
	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_CALL_SELF(&_0, "gettokenindex", NULL, 0, token, identifier);
	zephir_check_call_status();
	RETURN_MM_BOOL(!ZEPHIR_IS_FALSE_IDENTICAL(_0));

}

PHP_METHOD(CsrfProtect_CsrfProtect, getToken) {

	zephir_fcall_cache_entry *_4 = NULL, *_23 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, tokenLength = 0, charsCount, i, _17$$5, tokenLimit$$6 = 0;
	zval *identifier_param = NULL, *_SESSION, *_0 = NULL, *_1, *_2, *_3 = NULL, *_6, *_7, *_8 = NULL, *_14 = NULL, *_15 = NULL, *_24, _9$$4 = zval_used_for_init, _10$$4 = zval_used_for_init, _11$$4 = zval_used_for_init, _12$$4 = zval_used_for_init, *_13$$4 = NULL, *_16$$5, *_18$$6, *_19$$6, *_20$$6 = NULL, *_21$$6, *_22$$7;
	zval *identifier = NULL, *tokenChars = NULL, *_5 = NULL, *token;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
	zephir_fetch_params(1, 0, 1, &identifier_param);

	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_CALL_FUNCTION(&_0, "session_id", NULL, 2);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_CALL_FUNCTION(NULL, "session_start", NULL, 3);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_1);
	zephir_get_called_class(_1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_VS(_2, _1, "::TOKEN_CHARS");
	ZEPHIR_CALL_FUNCTION(&_3, "constant", &_4, 1, _2);
	zephir_check_call_status();
	zephir_get_strval(_5, _3);
	ZEPHIR_CPY_WRT(tokenChars, _5);
	ZEPHIR_INIT_VAR(_6);
	zephir_get_called_class(_6 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_7);
	ZEPHIR_CONCAT_VS(_7, _6, "::TOKEN_LENGTH");
	ZEPHIR_CALL_FUNCTION(&_8, "constant", &_4, 1, _7);
	zephir_check_call_status();
	tokenLength = zephir_get_intval(_8);
	ZEPHIR_INIT_VAR(token);
	ZVAL_EMPTY_STRING(token);
	charsCount = zephir_fast_strlen_ev(tokenChars);
	i = 0;
	while (1) {
		if (!(i < tokenLength)) {
			break;
		}
		ZEPHIR_SINIT_NVAR(_9$$4);
		ZVAL_LONG(&_9$$4, 0);
		ZEPHIR_SINIT_NVAR(_10$$4);
		ZVAL_LONG(&_10$$4, charsCount);
		ZEPHIR_SINIT_NVAR(_11$$4);
		ZVAL_LONG(&_11$$4, zephir_mt_rand(zephir_get_intval(&_9$$4), zephir_get_intval(&_10$$4) TSRMLS_CC));
		ZEPHIR_SINIT_NVAR(_12$$4);
		ZVAL_LONG(&_12$$4, 1);
		ZEPHIR_INIT_NVAR(_13$$4);
		zephir_substr(_13$$4, tokenChars, zephir_get_intval(&_11$$4), 1 , 0);
		zephir_concat_self(&token, _13$$4 TSRMLS_CC);
		i = (i + 1);
	}
	ZEPHIR_CALL_SELF(&_14, "prefixedidentifier", NULL, 0, identifier);
	zephir_check_call_status();
	zephir_get_strval(identifier, _14);
	ZEPHIR_CALL_SELF(&_15, "identifierexists", NULL, 0, identifier);
	zephir_check_call_status();
	if (!(zephir_is_true(_15))) {
		ZEPHIR_INIT_VAR(_16$$5);
		array_init(_16$$5);
		_17$$5 = zephir_maybe_separate_zval(&_SESSION);
		zephir_array_update_zval(&_SESSION, identifier, &_16$$5, PH_COPY | PH_SEPARATE);
		if (_17$$5) {
			ZEND_SET_SYMBOL(&EG(symbol_table), "_SESSION", _SESSION);
		}
	} else {
		ZEPHIR_INIT_VAR(_18$$6);
		zephir_get_called_class(_18$$6 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_19$$6);
		ZEPHIR_CONCAT_VS(_19$$6, _18$$6, "::TOKENS_LIMIT");
		ZEPHIR_CALL_FUNCTION(&_20$$6, "constant", &_4, 1, _19$$6);
		zephir_check_call_status();
		tokenLimit$$6 = zephir_get_intval(_20$$6);
		while (1) {
			zephir_array_fetch(&_21$$6, _SESSION, identifier, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 104 TSRMLS_CC);
			if (!(zephir_fast_count_int(_21$$6 TSRMLS_CC) > tokenLimit$$6)) {
				break;
			}
			zephir_array_fetch(&_22$$7, _SESSION, identifier, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 105 TSRMLS_CC);
			ZEPHIR_MAKE_REF(_22$$7);
			ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_23, 5, _22$$7);
			ZEPHIR_UNREF(_22$$7);
			zephir_check_call_status();
		}
	}
	zephir_array_fetch(&_24, _SESSION, identifier, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 108 TSRMLS_CC);
	ZEPHIR_MAKE_REF(_24);
	ZEPHIR_CALL_FUNCTION(NULL, "array_push", NULL, 6, _24, token);
	ZEPHIR_UNREF(_24);
	zephir_check_call_status();
	RETURN_CTOR(token);

}

PHP_METHOD(CsrfProtect_CsrfProtect, getTag) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *identifier_param = NULL, *_0, *_1, *_2 = NULL, *_3 = NULL;
	zval *identifier = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &identifier_param);

	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_INIT_VAR(_0);
	zephir_get_called_class(_0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_VS(_1, _0, "::POST_KEY");
	ZEPHIR_CALL_FUNCTION(&_2, "constant", NULL, 1, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_SELF(&_3, "gettoken", NULL, 0, identifier);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SSSVSSVSS(return_value, "<input ", "type=\"hidden\" ", "name=\"", _2, "\" ", "value=\"", _3, "\"", ">");
	RETURN_MM();

}

