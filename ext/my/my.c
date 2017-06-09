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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_my.h"

static int le_my;

zend_class_entry* my_ce;

PHP_MINIT_FUNCTION(my)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "My", NULL);
	my_ce = zend_register_internal_class(&ce);
	//
	my_ce.create_object = 

	return SUCCESS;
}

zend_module_entry my_module_entry = {
	STANDARD_MODULE_HEADER,
	"my",
	NULL,
	PHP_MINIT(my),
	NULL,
	NULL,		/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	NULL,
	PHP_MY_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MY
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(my)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
