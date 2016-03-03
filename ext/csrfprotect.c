
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#if PHP_VERSION_ID < 50500
#include <locale.h>
#endif

#include "php_ext.h"
#include "csrfprotect.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *csrfprotect_csrfprotect_ce;

ZEND_DECLARE_MODULE_GLOBALS(csrfprotect)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(csrfprotect)
{
#if PHP_VERSION_ID < 50500
	char* old_lc_all = setlocale(LC_ALL, NULL);
	if (old_lc_all) {
		size_t len = strlen(old_lc_all);
		char *tmp  = calloc(len+1, 1);
		if (UNEXPECTED(!tmp)) {
			return FAILURE;
		}

		memcpy(tmp, old_lc_all, len);
		old_lc_all = tmp;
	}

	setlocale(LC_ALL, "C");
#endif
	REGISTER_INI_ENTRIES();
	ZEPHIR_INIT(CsrfProtect_CsrfProtect);

#if PHP_VERSION_ID < 50500
	setlocale(LC_ALL, old_lc_all);
	free(old_lc_all);
#endif
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(csrfprotect)
{

	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_csrfprotect_globals *csrfprotect_globals TSRMLS_DC)
{
	csrfprotect_globals->initialized = 0;

	/* Memory options */
	csrfprotect_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	csrfprotect_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	csrfprotect_globals->cache_enabled = 1;

	/* Recursive Lock */
	csrfprotect_globals->recursive_lock = 0;

	/* Static cache */
	memset(csrfprotect_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

static PHP_RINIT_FUNCTION(csrfprotect)
{

	zend_csrfprotect_globals *csrfprotect_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(csrfprotect_globals_ptr TSRMLS_CC);
	//zephir_init_interned_strings(TSRMLS_C);

	zephir_initialize_memory(csrfprotect_globals_ptr TSRMLS_CC);


	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(csrfprotect)
{

	

	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(csrfprotect)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_CSRFPROTECT_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_CSRFPROTECT_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_CSRFPROTECT_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_CSRFPROTECT_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_CSRFPROTECT_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(csrfprotect)
{
	php_zephir_init_globals(csrfprotect_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(csrfprotect)
{

}


zend_function_entry php_csrfprotect_functions[] = {
ZEND_FE_END

};

zend_module_entry csrfprotect_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_CSRFPROTECT_EXTNAME,
	php_csrfprotect_functions,
	PHP_MINIT(csrfprotect),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(csrfprotect),
#else
	NULL,
#endif
	PHP_RINIT(csrfprotect),
	PHP_RSHUTDOWN(csrfprotect),
	PHP_MINFO(csrfprotect),
	PHP_CSRFPROTECT_VERSION,
	ZEND_MODULE_GLOBALS(csrfprotect),
	PHP_GINIT(csrfprotect),
	PHP_GSHUTDOWN(csrfprotect),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_CSRFPROTECT
ZEND_GET_MODULE(csrfprotect)
#endif
