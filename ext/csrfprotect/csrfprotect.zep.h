
extern zend_class_entry *csrfprotect_csrfprotect_ce;

ZEPHIR_INIT_CLASS(CsrfProtect_CsrfProtect);

PHP_METHOD(CsrfProtect_CsrfProtect, checkToken);
PHP_METHOD(CsrfProtect_CsrfProtect, getToken);

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_checktoken, 0, 0, 1)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_csrfprotect_csrfprotect_gettoken, 0, 0, 1)
	ZEND_ARG_INFO(0, identifier)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(csrfprotect_csrfprotect_method_entry) {
	PHP_ME(CsrfProtect_CsrfProtect, checkToken, arginfo_csrfprotect_csrfprotect_checktoken, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CsrfProtect_CsrfProtect, getToken, arginfo_csrfprotect_csrfprotect_gettoken, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
