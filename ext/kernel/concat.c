
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include "php_ext.h"
#include <ext/standard/php_string.h>
#include "ext.h"

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/concat.h"

void zephir_concat_sssvssvss(zval **result, const char *op1, zend_uint op1_len, const char *op2, zend_uint op2_len, const char *op3, zend_uint op3_len, zval *op4, const char *op5, zend_uint op5_len, const char *op6, zend_uint op6_len, zval *op7, const char *op8, zend_uint op8_len, const char *op9, zend_uint op9_len, int self_var TSRMLS_DC){

	zval result_copy, op4_copy, op7_copy;
	int use_copy = 0, use_copy4 = 0, use_copy7 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op4) != IS_STRING) {
	   zend_make_printable_zval(op4, &op4_copy, &use_copy4);
	   if (use_copy4) {
	       op4 = &op4_copy;
	   }
	}

	if (Z_TYPE_P(op7) != IS_STRING) {
	   zend_make_printable_zval(op7, &op7_copy, &use_copy7);
	   if (use_copy7) {
	       op7 = &op7_copy;
	   }
	}

	length = op1_len + op2_len + op3_len + Z_STRLEN_P(op4) + op5_len + op6_len + Z_STRLEN_P(op7) + op8_len + op9_len;
	if (self_var) {

		if (Z_TYPE_PP(result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				ZEPHIR_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_PP(result);
		length += offset;
		Z_STRVAL_PP(result) = (char *) str_erealloc(Z_STRVAL_PP(result), length + 1);

	} else {
		Z_STRVAL_PP(result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_PP(result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_PP(result) + offset + op1_len, op2, op2_len);
	memcpy(Z_STRVAL_PP(result) + offset + op1_len + op2_len, op3, op3_len);
	memcpy(Z_STRVAL_PP(result) + offset + op1_len + op2_len + op3_len, Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	memcpy(Z_STRVAL_PP(result) + offset + op1_len + op2_len + op3_len + Z_STRLEN_P(op4), op5, op5_len);
	memcpy(Z_STRVAL_PP(result) + offset + op1_len + op2_len + op3_len + Z_STRLEN_P(op4) + op5_len, op6, op6_len);
	memcpy(Z_STRVAL_PP(result) + offset + op1_len + op2_len + op3_len + Z_STRLEN_P(op4) + op5_len + op6_len, Z_STRVAL_P(op7), Z_STRLEN_P(op7));
	memcpy(Z_STRVAL_PP(result) + offset + op1_len + op2_len + op3_len + Z_STRLEN_P(op4) + op5_len + op6_len + Z_STRLEN_P(op7), op8, op8_len);
	memcpy(Z_STRVAL_PP(result) + offset + op1_len + op2_len + op3_len + Z_STRLEN_P(op4) + op5_len + op6_len + Z_STRLEN_P(op7) + op8_len, op9, op9_len);
	Z_STRVAL_PP(result)[length] = 0;
	Z_TYPE_PP(result) = IS_STRING;
	Z_STRLEN_PP(result) = length;

	if (use_copy4) {
	   zval_dtor(op4);
	}

	if (use_copy7) {
	   zval_dtor(op7);
	}

	if (use_copy) {
	   zval_dtor(&result_copy);
	}

}

void zephir_concat_sv(zval **result, const char *op1, zend_uint op1_len, zval *op2, int self_var TSRMLS_DC){

	zval result_copy, op2_copy;
	int use_copy = 0, use_copy2 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
	   zend_make_printable_zval(op2, &op2_copy, &use_copy2);
	   if (use_copy2) {
	       op2 = &op2_copy;
	   }
	}

	length = op1_len + Z_STRLEN_P(op2);
	if (self_var) {

		if (Z_TYPE_PP(result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				ZEPHIR_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_PP(result);
		length += offset;
		Z_STRVAL_PP(result) = (char *) str_erealloc(Z_STRVAL_PP(result), length + 1);

	} else {
		Z_STRVAL_PP(result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_PP(result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_PP(result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	Z_STRVAL_PP(result)[length] = 0;
	Z_TYPE_PP(result) = IS_STRING;
	Z_STRLEN_PP(result) = length;

	if (use_copy2) {
	   zval_dtor(op2);
	}

	if (use_copy) {
	   zval_dtor(&result_copy);
	}

}

void zephir_concat_vs(zval **result, zval *op1, const char *op2, zend_uint op2_len, int self_var TSRMLS_DC){

	zval result_copy, op1_copy;
	int use_copy = 0, use_copy1 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
	   zend_make_printable_zval(op1, &op1_copy, &use_copy1);
	   if (use_copy1) {
	       op1 = &op1_copy;
	   }
	}

	length = Z_STRLEN_P(op1) + op2_len;
	if (self_var) {

		if (Z_TYPE_PP(result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				ZEPHIR_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_PP(result);
		length += offset;
		Z_STRVAL_PP(result) = (char *) str_erealloc(Z_STRVAL_PP(result), length + 1);

	} else {
		Z_STRVAL_PP(result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_PP(result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_PP(result) + offset + Z_STRLEN_P(op1), op2, op2_len);
	Z_STRVAL_PP(result)[length] = 0;
	Z_TYPE_PP(result) = IS_STRING;
	Z_STRLEN_PP(result) = length;

	if (use_copy1) {
	   zval_dtor(op1);
	}

	if (use_copy) {
	   zval_dtor(&result_copy);
	}

}

void zephir_concat_vv(zval **result, zval *op1, zval *op2, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op2_copy;
	int use_copy = 0, use_copy1 = 0, use_copy2 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
	   zend_make_printable_zval(op1, &op1_copy, &use_copy1);
	   if (use_copy1) {
	       op1 = &op1_copy;
	   }
	}

	if (Z_TYPE_P(op2) != IS_STRING) {
	   zend_make_printable_zval(op2, &op2_copy, &use_copy2);
	   if (use_copy2) {
	       op2 = &op2_copy;
	   }
	}

	length = Z_STRLEN_P(op1) + Z_STRLEN_P(op2);
	if (self_var) {

		if (Z_TYPE_PP(result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				ZEPHIR_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_PP(result);
		length += offset;
		Z_STRVAL_PP(result) = (char *) str_erealloc(Z_STRVAL_PP(result), length + 1);

	} else {
		Z_STRVAL_PP(result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_PP(result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_PP(result) + offset + Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	Z_STRVAL_PP(result)[length] = 0;
	Z_TYPE_PP(result) = IS_STRING;
	Z_STRLEN_PP(result) = length;

	if (use_copy1) {
	   zval_dtor(op1);
	}

	if (use_copy2) {
	   zval_dtor(op2);
	}

	if (use_copy) {
	   zval_dtor(&result_copy);
	}

}

