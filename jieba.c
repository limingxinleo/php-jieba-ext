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

zend_class_entry *jieba_ce;

PHP_METHOD(PHPJieba, __construct);
PHP_METHOD(PHPJieba, cut);

ZEND_BEGIN_ARG_INFO_EX(arginfo_php_jieba_cut, 0, 0, 2)
    ZEND_ARG_INFO(0, keyword)
    ZEND_ARG_INFO(0, hmm)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_php_jieba_construct, 0, 0, 5)
    ZEND_ARG_INFO(0, dict)
    ZEND_ARG_INFO(0, hmm)
    ZEND_ARG_INFO(0, user)
    ZEND_ARG_INFO(0, idf)
    ZEND_ARG_INFO(0, stop_words)
ZEND_END_ARG_INFO()

const zend_function_entry php_jieba_methods[] = {
    PHP_ME(PHPJieba, __construct, arginfo_php_jieba_construct, ZEND_ACC_PUBLIC)
    PHP_ME(PHPJieba, cut, arginfo_php_jieba_cut, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(PHPJieba)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "PHPJieba", php_jieba_methods);

    jieba_ce = zend_register_internal_class(&ce);

    zend_declare_property_string(jieba_ce, ZEND_STRL("dict"), "", ZEND_ACC_PUBLIC);
    zend_declare_property_string(jieba_ce, ZEND_STRL("hmm"), "", ZEND_ACC_PUBLIC);
    zend_declare_property_string(jieba_ce, ZEND_STRL("user"), "", ZEND_ACC_PUBLIC);
    zend_declare_property_string(jieba_ce, ZEND_STRL("idf"), "", ZEND_ACC_PUBLIC);
    zend_declare_property_string(jieba_ce, ZEND_STRL("stop_words"), "", ZEND_ACC_PUBLIC);

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(PHPJieba)
{
    return SUCCESS;
}

PHP_METHOD(PHPJieba, __construct)
{
    char *dict;
    size_t dict_len;
    char *hmm;
    size_t hmm_len;
    char *user;
    size_t user_len;
    char *idf;
    size_t idf_len;
    char *stop_words;
    size_t stop_words_len;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_STRING(dict, dict_len)
        Z_PARAM_STRING(hmm, hmm_len)
        Z_PARAM_STRING(user, user_len)
        Z_PARAM_STRING(idf, idf_len)
        Z_PARAM_STRING(stop_words, stop_words_len)
    ZEND_PARSE_PARAMETERS_END();

    zend_update_property_string(jieba_ce,  getThis(), "dict", dict_len, dict);
    zend_update_property_string(jieba_ce,  getThis(), "hmm", hmm_len, hmm);
    zend_update_property_string(jieba_ce,  getThis(), "user", user_len, user);
    zend_update_property_string(jieba_ce,  getThis(), "idf", idf_len, idf);
    zend_update_property_string(jieba_ce,  getThis(), "stop_words", stop_words_len, stop_words);
}

PHP_METHOD(PHPJieba, cut)
{
    zval *dict;
//    zend_read_property(jieba_ce, getThis(), "dict", 4, dict);
    dict = zend_read_property(jieba_ce, getThis(), "dict", sizeof("dict")-1, 1, &dict);

    php_printf("%s", (char *)dict);
//    RETURN_STRING(Z_PARAM_STR(dict))
//    char *love;
//    zend_string *keyword;
//    size_t love_len;
//
//    ZEND_PARSE_PARAMETERS_START(1, 2)
//        Z_PARAM_STR(keyword)
//        Z_PARAM_OPTIONAL
//        Z_PARAM_ZVAL_EX(value, 0, 1)
//    ZEND_PARSE_PARAMETERS_END();
}


/* {{{ void jieba_test1()
 */
PHP_FUNCTION(jieba_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	Jieba handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH);

	php_printf("%s", DICT_PATH);

    const char* s = "南京市长江大桥";
    size_t len = strlen(s);
    CJiebaWord* words = Cut(handle, s, len);
    CJiebaWord* x;
    for (x = words; x && x->word; x++) {
        php_printf("%*.*s\n", x->len, x->len, x->word);
    }

    FreeWords(words);
    FreeJieba(handle);
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
	PHP_MINIT(PHPJieba),
	PHP_MSHUTDOWN(PHPJieba),
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
