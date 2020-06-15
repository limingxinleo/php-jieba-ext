/* jieba extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_jieba.h"
#include "lib/jieba.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

const char* DICT_PATH = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/jieba.dict.utf8";
const char* HMM_PATH = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/hmm_model.utf8";
const char* USER_DICT = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/user.dict.utf8";
const char* IDF_PATH = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/idf.utf8";
const char* STOP_WORDS_PATH = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/stop_words.utf8";

/* {{{ void jieba_test1()
 */
PHP_FUNCTION(jieba_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	Jieba handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH);

	php_printf("%s", DICT_PATH);
//
//    const char* s = "南京市长江大桥";
//    size_t len = strlen(s);
//    CJiebaWord* words = Cut(handle, s, len);
//    CJiebaWord* x;
//    for (x = words; x && x->word; x++) {
//        php_printf("%*.*s\n", x->len, x->len, x->word);
//    }
//
//    FreeWords(words);
//    FreeJieba(handle);
}
/* }}} */

/* {{{ string jieba_test2( [ string $var ] )
 */
PHP_FUNCTION(jieba_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(jieba)
{
#if defined(ZTS) && defined(COMPILE_DL_JIEBA)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(jieba)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "jieba support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_jieba_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_jieba_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ jieba_functions[]
 */
static const zend_function_entry jieba_functions[] = {
	PHP_FE(jieba_test1,		arginfo_jieba_test1)
	PHP_FE(jieba_test2,		arginfo_jieba_test2)
	PHP_FE_END
};
/* }}} */

/* {{{ jieba_module_entry
 */
zend_module_entry jieba_module_entry = {
	STANDARD_MODULE_HEADER,
	"jieba",					/* Extension name */
	jieba_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(jieba),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(jieba),			/* PHP_MINFO - Module info */
	PHP_JIEBA_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_JIEBA
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(jieba)
#endif
