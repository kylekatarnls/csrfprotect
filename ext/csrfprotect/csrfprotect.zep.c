
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
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
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

PHP_METHOD(CsrfProtect_CsrfProtect, identifierExists) {

	zend_bool _1;
	zval *identifier_param = NULL, *_SESSION, *_2;
	zval *identifier = NULL, *_0, *_3;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
	zephir_fetch_params(1, 0, 1, &identifier_param);

	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "_csrf_", identifier);
	_1 = zephir_array_isset(_SESSION, _0);
	if (_1) {
		ZEPHIR_INIT_VAR(_3);
		ZEPHIR_CONCAT_SV(_3, "_csrf_", identifier);
		zephir_array_fetch(&_2, _SESSION, _3, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 14 TSRMLS_CC);
		_1 = Z_TYPE_P(_2) == IS_ARRAY;
	}
	RETURN_MM_BOOL(_1);

}

PHP_METHOD(CsrfProtect_CsrfProtect, checkPostToken) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *identifier_param = NULL, *_POST, *_0, *_1;
	zval *identifier = NULL;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
	zephir_fetch_params(1, 0, 1, &identifier_param);

	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	zephir_array_fetch_string(&_0, _POST, SL("_csrf"), PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 19 TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(_0)) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_string(&_1, _POST, SL("_csrf"), PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 23 TSRMLS_CC);
	ZEPHIR_RETURN_CALL_SELF("checktoken", NULL, 0, _1, identifier);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(CsrfProtect_CsrfProtect, getTokenIndex) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *token_param = NULL, *identifier_param = NULL, *_POST, *_SESSION, *_0 = NULL, *_4 = NULL, *_1$$4, *_2$$4, *_5$$6;
	zval *token = NULL, *identifier = NULL, *_3$$4 = NULL, *_6$$6;

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


	ZEPHIR_CALL_FUNCTION(&_0, "session_id", NULL, 1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_CALL_FUNCTION(NULL, "session_start", NULL, 2);
		zephir_check_call_status();
	}
	if (ZEPHIR_IS_EMPTY(token)) {
		zephir_array_fetch_string(&_1$$4, _POST, SL("_csrf"), PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 33 TSRMLS_CC);
		if (ZEPHIR_IS_EMPTY(_1$$4)) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_OBS_VAR(_2$$4);
		zephir_array_fetch_string(&_2$$4, _POST, SL("_csrf"), PH_NOISY, "csrfprotect/CsrfProtect.zep", 36 TSRMLS_CC);
		zephir_get_strval(_3$$4, _2$$4);
		ZEPHIR_CPY_WRT(token, _3$$4);
	}
	ZEPHIR_CALL_SELF(&_4, "identifierexists", NULL, 0, identifier);
	zephir_check_call_status();
	if (zephir_is_true(_4)) {
		ZEPHIR_INIT_VAR(_6$$6);
		ZEPHIR_CONCAT_SV(_6$$6, "_csrf_", identifier);
		zephir_array_fetch(&_5$$6, _SESSION, _6$$6, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 40 TSRMLS_CC);
		ZEPHIR_RETURN_CALL_FUNCTION("array_search", NULL, 3, token, _5$$6);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

PHP_METHOD(CsrfProtect_CsrfProtect, checkToken) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *token_param = NULL, *identifier_param = NULL, *_SESSION, *key = NULL, *_0$$3;
	zval *token = NULL, *identifier = NULL, *_1$$3;

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
		ZEPHIR_INIT_VAR(_1$$3);
		ZEPHIR_CONCAT_SV(_1$$3, "_csrf_", identifier);
		zephir_array_fetch(&_0$$3, _SESSION, _1$$3, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 52 TSRMLS_CC);
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

	zephir_fcall_cache_entry *_16 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, charsCount, i, _11$$5;
	zval *identifier_param = NULL, *_SESSION, *_0 = NULL, _1, *_8 = NULL, *_17, _2$$4 = zval_used_for_init, _3$$4 = zval_used_for_init, _4$$4 = zval_used_for_init, _5$$4 = zval_used_for_init, _6$$4 = zval_used_for_init, *_7$$4 = NULL, *_9$$5, *_12$$6, *_14$$7;
	zval *identifier = NULL, *token, *_18, *_10$$5, *_13$$6 = NULL, *_15$$7 = NULL;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
	zephir_fetch_params(1, 0, 1, &identifier_param);

	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_CALL_FUNCTION(&_0, "session_id", NULL, 1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_CALL_FUNCTION(NULL, "session_start", NULL, 2);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(token);
	ZVAL_EMPTY_STRING(token);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890_-", 0);
	charsCount = zephir_fast_strlen_ev(&_1);
	i = 0;
	while (1) {
		if (!(i < 32)) {
			break;
		}
		ZEPHIR_SINIT_NVAR(_2$$4);
		ZVAL_LONG(&_2$$4, 0);
		ZEPHIR_SINIT_NVAR(_3$$4);
		ZVAL_LONG(&_3$$4, charsCount);
		ZEPHIR_SINIT_NVAR(_4$$4);
		ZVAL_STRING(&_4$$4, "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890_-", 0);
		ZEPHIR_SINIT_NVAR(_5$$4);
		ZVAL_LONG(&_5$$4, zephir_mt_rand(zephir_get_intval(&_2$$4), zephir_get_intval(&_3$$4) TSRMLS_CC));
		ZEPHIR_SINIT_NVAR(_6$$4);
		ZVAL_LONG(&_6$$4, 1);
		ZEPHIR_INIT_NVAR(_7$$4);
		zephir_substr(_7$$4, &_4$$4, zephir_get_intval(&_5$$4), 1 , 0);
		zephir_concat_self(&token, _7$$4 TSRMLS_CC);
		i = (i + 1);
	}
	ZEPHIR_CALL_SELF(&_8, "identifierexists", NULL, 0, identifier);
	zephir_check_call_status();
	if (!(zephir_is_true(_8))) {
		ZEPHIR_INIT_VAR(_9$$5);
		array_init(_9$$5);
		ZEPHIR_INIT_VAR(_10$$5);
		ZEPHIR_CONCAT_SV(_10$$5, "_csrf_", identifier);
		_11$$5 = zephir_maybe_separate_zval(&_SESSION);
		zephir_array_update_zval(&_SESSION, _10$$5, &_9$$5, PH_COPY | PH_SEPARATE);
		if (_11$$5) {
			ZEND_SET_SYMBOL(&EG(symbol_table), "_SESSION", _SESSION);
		}
	} else {
		while (1) {
			ZEPHIR_INIT_LNVAR(_13$$6);
			ZEPHIR_CONCAT_SV(_13$$6, "_csrf_", identifier);
			zephir_array_fetch(&_12$$6, _SESSION, _13$$6, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 81 TSRMLS_CC);
			if (!(zephir_fast_count_int(_12$$6 TSRMLS_CC) > 5000)) {
				break;
			}
			ZEPHIR_INIT_LNVAR(_15$$7);
			ZEPHIR_CONCAT_SV(_15$$7, "_csrf_", identifier);
			zephir_array_fetch(&_14$$7, _SESSION, _15$$7, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 82 TSRMLS_CC);
			ZEPHIR_MAKE_REF(_14$$7);
			ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_16, 4, _14$$7);
			ZEPHIR_UNREF(_14$$7);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_VAR(_18);
	ZEPHIR_CONCAT_SV(_18, "_csrf_", identifier);
	zephir_array_fetch(&_17, _SESSION, _18, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 85 TSRMLS_CC);
	ZEPHIR_MAKE_REF(_17);
	ZEPHIR_CALL_FUNCTION(NULL, "array_push", NULL, 5, _17, token);
	ZEPHIR_UNREF(_17);
	zephir_check_call_status();
	RETURN_CTOR(token);

}

PHP_METHOD(CsrfProtect_CsrfProtect, getTag) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *identifier_param = NULL, *_0 = NULL;
	zval *identifier = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &identifier_param);

	if (!identifier_param) {
		ZEPHIR_INIT_VAR(identifier);
		ZVAL_STRING(identifier, "", 1);
	} else {
		zephir_get_strval(identifier, identifier_param);
	}


	ZEPHIR_CALL_SELF(&_0, "gettoken", NULL, 0, identifier);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SSSSSSVSS(return_value, "<input ", "type=\"hidden\" ", "name=\"", "_csrf", "\" ", "value=\"", _0, "\"", ">");
	RETURN_MM();

}

