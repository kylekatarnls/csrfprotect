
extern zend_class_entry *csrfprotect_csrfprotect_ce;

ZEPHIR_INIT_CLASS(CsrfProtect_CsrfProtect);

PHP_METHOD(CsrfProtect_CsrfProtect, prefixedIdentifier);
PHP_METHOD(CsrfProtect_CsrfProtect, identifierExists);
PHP_METHOD(CsrfProtect_CsrfProtect, checkPostToken);
PHP_METHOD(CsrfProtect_CsrfProtect, getTokenIndex);
PHP_METHOD(CsrfProtect_CsrfProtect, checkToken);
PHP_METHOD(CsrfProtect_CsrfProtect, isValidToken);
PHP_METHOD(CsrfProtect_CsrfProtect, getToken);
PHP_METHOD(CsrfProtect_CsrfProtect, getTag);

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_prefixedidentifier, 0, 0, 0)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_identifierexists, 0, 0, 0)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_checkposttoken, 0, 0, 0)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_gettokenindex, 0, 0, 0)
	ZEND_ARG_INFO(0, token)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_checktoken, 0, 0, 0)
	ZEND_ARG_INFO(0, token)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_isvalidtoken, 0, 0, 0)
	ZEND_ARG_INFO(0, token)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_gettoken, 0, 0, 0)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_gettag, 0, 0, 0)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(csrfprotect_csrfprotect_method_entry) {
	PHP_ME(CsrfProtect_CsrfProtect, prefixedIdentifier, arginfo_csrfprotect_csrfprotect_prefixedidentifier, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(CsrfProtect_CsrfProtect, identifierExists, arginfo_csrfprotect_csrfprotect_identifierexists, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(CsrfProtect_CsrfProtect, checkPostToken, arginfo_csrfprotect_csrfprotect_checkposttoken, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CsrfProtect_CsrfProtect, getTokenIndex, arginfo_csrfprotect_csrfprotect_gettokenindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CsrfProtect_CsrfProtect, checkToken, arginfo_csrfprotect_csrfprotect_checktoken, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CsrfProtect_CsrfProtect, isValidToken, arginfo_csrfprotect_csrfprotect_isvalidtoken, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CsrfProtect_CsrfProtect, getToken, arginfo_csrfprotect_csrfprotect_gettoken, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CsrfProtect_CsrfProtect, getTag, arginfo_csrfprotect_csrfprotect_gettag, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
