/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "user.h"

ZEND_API ZEND_INI_MH(OnUpdateAddArray);

#define MYTEST_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(mytest, v)

ZEND_BEGIN_MODULE_GLOBALS(mytest)
    zend_long   open_cache;
    HashTable   class_table;
    zend_bool        is_open;
ZEND_END_MODULE_GLOBALS(mytest)

ZEND_DECLARE_MODULE_GLOBALS(mytest);


ZEND_BEGIN_ARG_INFO_EX(arginfo_my_func_1, 0, 1, 1)
    ZEND_ARG_INFO(0, arr)
ZEND_END_ARG_INFO()
    

PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("mytest.open_cache", "109", ZEND_INI_USER, OnUpdateLong, open_cache, zend_mytest_globals, mytest_globals)
    STD_PHP_INI_ENTRY("mytest.class", "stdClass", PHP_INI_ALL, OnUpdateAddArray, class_table, zend_mytest_globals, mytest_globals)
    STD_PHP_INI_BOOLEAN("mytest.is_open", "1", PHP_INI_ALL, OnUpdateBool, is_open, zend_mytest_globals, mytest_globals)
PHP_INI_END();

PHP_MINIT_FUNCTION(mytest)
{
    printf("PHP_MINIT::mytest\n");        
    zend_hash_init(&MYTEST_G(class_table), 0, NULL, NULL, 1);
    REGISTER_INI_ENTRIES();

    REGISTER_STRING_CONSTANT("MY_CONS_1", "this is a constant", CONST_CS | CONST_PERSISTENT);
}

ZEND_API ZEND_INI_MH(OnUpdateAddArray)
{
    HashTable   *ht;
    zval    val;
#ifndef ZTS
    char *base = (char *) mh_arg2;
#else
    char *base;
    base = (char *) ts_resource(*((int *) mh_arg2));
#endif

    ht = (HashTable*)(base+(size_t) mh_arg1);
    ZVAL_NULL(&val);
    zend_hash_add(ht, new_value, &val);
}

void my_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    printf("try to set property...\n");

    zend_std_write_property(object, member, value, cache_slot);
}

PHP_FUNCTION(my_func_1)
{
    zend_long   i;
    zval        call_func_name;
    zval        call_func_ret;
    uint32_t    call_func_param_cnt = 1;
    zval        call_func_params[1];
    zend_string *call_func_str;
    char        *func_name = "mySum";

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "l", &i) == FAILURE){
        RETURN_FALSE;
    }

    //分配zend_string:调用完需要释放
    call_func_str = zend_string_init(func_name, strlen(func_name), 0);
    //设置到zval
    ZVAL_STR(&call_func_name, call_func_str);
    
    ZVAL_LONG(&call_func_params[0], i);

    //call
    if(SUCCESS != call_user_function(EG(function_table), NULL, &call_func_name, &call_func_ret, call_func_param_cnt, call_func_params)){
        zend_string_release(call_func_str);
        RETURN_FALSE;
    }
        
    zend_string_release(call_func_str);
    
    RETURN_LONG(Z_LVAL(call_func_ret));
}

PHP_FUNCTION(my_func_2)
{
    zend_array  *arr1, *arr2;
    zval        call_func_name, call_func_ret, call_func_params[2];
    uint32_t    call_func_param_cnt = 2;
    zend_string *call_func_str;
    char        *func_name = "array_merge";

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "hh", &arr1, &arr2) == FAILURE){
        RETURN_FALSE;
    }
    //分配zend_string
    call_func_str = zend_string_init(func_name, strlen(func_name), 0);
    //设置到zval
    ZVAL_STR(&call_func_name, call_func_str);
    
    ZVAL_ARR(&call_func_params[0], arr1);
    ZVAL_ARR(&call_func_params[1], arr2);

    if(SUCCESS != call_user_function(EG(function_table), NULL, &call_func_name, &call_func_ret, call_func_param_cnt, call_func_params)){
        zend_string_release(call_func_str);
        RETURN_FALSE;
    }
    zend_string_release(call_func_str);

    printf("Hello, I'm my_func_2\n");
    RETURN_ARR(Z_ARRVAL(call_func_ret));
}

int my_cmp(void *a, void *b)
{
    Bucket  *f, *t;
    f = (Bucket *)a;
    t = (Bucket *)b;

    return f->val.value.dval < t->val.value.dval;
}

PHP_FUNCTION(my_func_3)
{
    zval    array;
    zval    *arr;
	
    if(zend_parse_parameters(ZEND_NUM_ARGS(), "a", &arr) == FAILURE){
        RETURN_FALSE;
    }

    printf("Z_ARR_P:%p\n", Z_ARR_P(arr));
    printf("Z_ARRVAL_P:%p\n", Z_ARRVAL_P(arr));

    
    zend_string *str1, *str2;
    zval    str;

    str1 = zend_string_init("AbcD", strlen("AbcD"), 0);
    
    //ZVAL_STR(&str, str1);

    ZVAL_NEW_ARR(&array);
    zend_hash_init(Z_ARRVAL(array), 3, NULL, ZVAL_PTR_DTOR, 0);

    Z_TRY_ADDREF_P(arr);
    //zend_hash_next_index_insert_new(Z_ARRVAL(array), arr);
    //zend_hash_next_index_insert_new(Z_ARRVAL(array), &str);
    zend_hash_add(Z_ARRVAL(array), str1, arr);
    //zend_hash_add_new(Z_ARRVAL(array), str1, arr);
    zval    var1,var2,var3;
    ZVAL_LONG(&var1, 80);
    ZVAL_LONG(&var2, 70);
    ZVAL_LONG(&var3, 100);
    
    zend_hash_next_index_insert(Z_ARRVAL(array), &var1);
    zend_hash_next_index_insert(Z_ARRVAL(array), &var2);
    zend_hash_next_index_insert(Z_ARRVAL(array), &var3);

    //zend_hash_sort(Z_ARRVAL(array), my_cmp, 0);

    zend_string_release(str1);

    char *aa = "ddddd";
    aa[0] = 'e';

    zend_array_destroy(Z_ARRVAL(array));

    EG(current_execute_data) = NULL;
    //RETURN_ARR(Z_ARRVAL(array));
}

const zend_function_entry timeout_functions[] = {
    PHP_FE(my_func_1,   arginfo_my_func_1)
    PHP_FE(my_func_2,   NULL)
    PHP_FE(my_func_3,   NULL)
    PHP_FE_END //末尾必须加这个
};

zend_module_entry mytest_module_entry = {
	STANDARD_MODULE_HEADER,
	"mytest",
	timeout_functions,//mytest_functions,
	PHP_MINIT(mytest),
	NULL,//PHP_MSHUTDOWN(mytest),
	NULL,//PHP_RINIT(mytest),
	NULL,//PHP_RSHUTDOWN(mytest),
	NULL,//PHP_MINFO(mytest),
	"1.0.0",
	STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(mytest)

