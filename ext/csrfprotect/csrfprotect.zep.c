
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
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
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

PHP_METHOD(CsrfProtect_CsrfProtect, checkPostToken) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *identifier_param = NULL, *_POST, *_0, *_1;
	zval *identifier = NULL;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
	zephir_fetch_params(1, 1, 0, &identifier_param);

	zephir_get_strval(identifier, identifier_param);


	zephir_array_fetch_string(&_0, _POST, SL("_csrf"), PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 13 TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(_0)) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_string(&_1, _POST, SL("_csrf"), PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 17 TSRMLS_CC);
	ZEPHIR_RETURN_CALL_SELF("checktoken", NULL, 0, _1, identifier);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(CsrfProtect_CsrfProtect, checkToken) {

	zend_bool _5, _8;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *token_param = NULL, *identifier_param = NULL, *_POST, *_SESSION, *_0 = NULL, *_6, *_9, *_1$$4, *_2$$4;
	zval *token = NULL, *identifier = NULL, *_4, *_7, *_10, *_3$$4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
	zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
	zephir_fetch_params(1, 2, 0, &token_param, &identifier_param);

	zephir_get_strval(token, token_param);
	zephir_get_strval(identifier, identifier_param);


	ZEPHIR_CALL_FUNCTION(&_0, "session_id", NULL, 1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_CALL_FUNCTION(NULL, "session_start", NULL, 2);
		zephir_check_call_status();
	}
	if (ZEPHIR_IS_EMPTY(token)) {
		zephir_array_fetch_string(&_1$$4, _POST, SL("_csrf"), PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 27 TSRMLS_CC);
		if (ZEPHIR_IS_EMPTY(_1$$4)) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_OBS_VAR(_2$$4);
		zephir_array_fetch_string(&_2$$4, _POST, SL("_csrf"), PH_NOISY, "csrfprotect/CsrfProtect.zep", 30 TSRMLS_CC);
		zephir_get_strval(_3$$4, _2$$4);
		ZEPHIR_CPY_WRT(token, _3$$4);
	}
	ZEPHIR_INIT_VAR(_4);
	ZEPHIR_CONCAT_SV(_4, "_csrf_", identifier);
	_5 = zephir_array_isset(_SESSION, _4);
	if (_5) {
		ZEPHIR_INIT_VAR(_7);
		ZEPHIR_CONCAT_SV(_7, "_csrf_", identifier);
		zephir_array_fetch(&_6, _SESSION, _7, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 34 TSRMLS_CC);
		_5 = Z_TYPE_P(_6) == IS_ARRAY;
	}
	_8 = _5;
	if (_8) {
		ZEPHIR_INIT_VAR(_10);
		ZEPHIR_CONCAT_SV(_10, "_csrf_", identifier);
		zephir_array_fetch(&_9, _SESSION, _10, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 35 TSRMLS_CC);
		_8 = zephir_fast_in_array(token, _9 TSRMLS_CC);
	}
	RETURN_MM_BOOL(_8);

}

PHP_METHOD(CsrfProtect_CsrfProtect, getToken) {

	zephir_fcall_cache_entry *_17 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, charsCount, i, _12$$5;
	zval *identifier_param = NULL, *_SESSION, *_0 = NULL, _1, *_8, *_18, _2$$4 = zval_used_for_init, _3$$4 = zval_used_for_init, _4$$4 = zval_used_for_init, _5$$4 = zval_used_for_init, _6$$4 = zval_used_for_init, *_7$$4 = NULL, *_10$$5, *_13$$6, *_15$$7;
	zval *identifier = NULL, *token, *_9, *_19, *_11$$5, *_14$$6 = NULL, *_16$$7 = NULL;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
	zephir_fetch_params(1, 1, 0, &identifier_param);

	zephir_get_strval(identifier, identifier_param);


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
	ZEPHIR_INIT_VAR(_9);
	ZEPHIR_CONCAT_SV(_9, "_csrf_", identifier);
	zephir_array_fetch(&_8, _SESSION, _9, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 52 TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(_8)) {
		ZEPHIR_INIT_VAR(_10$$5);
		array_init(_10$$5);
		ZEPHIR_INIT_VAR(_11$$5);
		ZEPHIR_CONCAT_SV(_11$$5, "_csrf_", identifier);
		_12$$5 = zephir_maybe_separate_zval(&_SESSION);
		zephir_array_update_zval(&_SESSION, _11$$5, &_10$$5, PH_COPY | PH_SEPARATE);
		if (_12$$5) {
			ZEND_SET_SYMBOL(&EG(symbol_table), "_SESSION", _SESSION);
		}
	} else {
		while (1) {
			ZEPHIR_INIT_LNVAR(_14$$6);
			ZEPHIR_CONCAT_SV(_14$$6, "_csrf_", identifier);
			zephir_array_fetch(&_13$$6, _SESSION, _14$$6, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 55 TSRMLS_CC);
			if (!(zephir_fast_count_int(_13$$6 TSRMLS_CC) > 5000)) {
				break;
			}
			ZEPHIR_INIT_LNVAR(_16$$7);
			ZEPHIR_CONCAT_SV(_16$$7, "_csrf_", identifier);
			zephir_array_fetch(&_15$$7, _SESSION, _16$$7, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 56 TSRMLS_CC);
			ZEPHIR_MAKE_REF(_15$$7);
			ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_17, 3, _15$$7);
			ZEPHIR_UNREF(_15$$7);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_VAR(_19);
	ZEPHIR_CONCAT_SV(_19, "_csrf_", identifier);
	zephir_array_fetch(&_18, _SESSION, _19, PH_NOISY | PH_READONLY, "csrfprotect/CsrfProtect.zep", 59 TSRMLS_CC);
	ZEPHIR_MAKE_REF(_18);
	ZEPHIR_CALL_FUNCTION(NULL, "array_push", NULL, 4, _18, token);
	ZEPHIR_UNREF(_18);
	zephir_check_call_status();
	RETURN_CTOR(token);

}

PHP_METHOD(CsrfProtect_CsrfProtect, getTag) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *identifier_param = NULL, *_0 = NULL;
	zval *identifier = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &identifier_param);

	zephir_get_strval(identifier, identifier_param);


	ZEPHIR_CALL_SELF(&_0, "gettoken", NULL, 0, identifier);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SSSSSSVSS(return_value, "<input ", "type=\"hidden\" ", "name=\"", "_csrf", "\" ", "value=\"", _0, "\"", ">");
	RETURN_MM();

}

