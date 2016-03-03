
#ifndef ZEPHIR_KERNEL_CONCAT_H
#define ZEPHIR_KERNEL_CONCAT_H

#include <php.h>
#include <Zend/zend.h>

#include "kernel/main.h"

#define ZEPHIR_CONCAT_SS(result, op1, op2) \
	 zephir_concat_ss(&result, op1, sizeof(op1)-1, op2, sizeof(op2)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SS(result, op1, op2) \
	 zephir_concat_ss(&result, op1, sizeof(op1)-1, op2, sizeof(op2)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_SSSSSSVSS(result, op1, op2, op3, op4, op5, op6, op7, op8, op9) \
	 zephir_concat_ssssssvss(&result, op1, sizeof(op1)-1, op2, sizeof(op2)-1, op3, sizeof(op3)-1, op4, sizeof(op4)-1, op5, sizeof(op5)-1, op6, sizeof(op6)-1, op7, op8, sizeof(op8)-1, op9, sizeof(op9)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SSSSSSVSS(result, op1, op2, op3, op4, op5, op6, op7, op8, op9) \
	 zephir_concat_ssssssvss(&result, op1, sizeof(op1)-1, op2, sizeof(op2)-1, op3, sizeof(op3)-1, op4, sizeof(op4)-1, op5, sizeof(op5)-1, op6, sizeof(op6)-1, op7, op8, sizeof(op8)-1, op9, sizeof(op9)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_SV(result, op1, op2) \
	 zephir_concat_sv(&result, op1, sizeof(op1)-1, op2, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SV(result, op1, op2) \
	 zephir_concat_sv(&result, op1, sizeof(op1)-1, op2, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VS(result, op1, op2) \
	 zephir_concat_vs(&result, op1, op2, sizeof(op2)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VS(result, op1, op2) \
	 zephir_concat_vs(&result, op1, op2, sizeof(op2)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VV(result, op1, op2) \
	 zephir_concat_vv(&result, op1, op2, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VV(result, op1, op2) \
	 zephir_concat_vv(&result, op1, op2, 1 TSRMLS_CC);


void zephir_concat_ss(zval **result, const char *op1, zend_uint op1_len, const char *op2, zend_uint op2_len, int self_var TSRMLS_DC);
void zephir_concat_ssssssvss(zval **result, const char *op1, zend_uint op1_len, const char *op2, zend_uint op2_len, const char *op3, zend_uint op3_len, const char *op4, zend_uint op4_len, const char *op5, zend_uint op5_len, const char *op6, zend_uint op6_len, zval *op7, const char *op8, zend_uint op8_len, const char *op9, zend_uint op9_len, int self_var TSRMLS_DC);
void zephir_concat_sv(zval **result, const char *op1, zend_uint op1_len, zval *op2, int self_var TSRMLS_DC);
void zephir_concat_vs(zval **result, zval *op1, const char *op2, zend_uint op2_len, int self_var TSRMLS_DC);
void zephir_concat_vv(zval **result, zval *op1, zval *op2, int self_var TSRMLS_DC);
#define zephir_concat_function(result, op1, op2) concat_function(result, op1, op2 TSRMLS_CC)

#endif /* ZEPHIR_KERNEL_CONCAT_H */

