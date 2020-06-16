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

zend_class_entry *jieba_ce;
zend_object_handlers jieba_object_handlers;

typedef struct _jieba_object {
    Jieba* handler;
    zend_object std;
}jieba_object;

static inline jieba_object *jieba_object_fetch(zend_object *obj) {
    return (jieba_object *)((char*)(obj) - XtOffsetOf(jieba_object, std));
}

static zend_object * jieba_object_create(zend_class_entry *type TSRMLS_DC)
{
    jieba_object *obj = (jieba_object *)ecalloc(1, sizeof(jieba_object) + zend_object_properties_size(type));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.handlers = &jieba_object_handlers;
    return &obj->std;
}

void jieba_object_free_storage(zend_object *object)
{
    jieba_object *intern = jieba_object_fetch(object);
    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(PHPJieba, __construct);
PHP_METHOD(PHPJieba, __destruct);
PHP_METHOD(PHPJieba, cut);
PHP_METHOD(PHPJieba, cutAll);
PHP_METHOD(PHPJieba, cutWithoutTagName);
PHP_METHOD(PHPJieba, insert);

ZEND_BEGIN_ARG_INFO_EX(arginfo_php_jieba_cut, 0, 0, 1)
    ZEND_ARG_INFO(0, keyword)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_php_jieba_cut_all, 0, 0, 1)
    ZEND_ARG_INFO(0, keyword)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_php_jieba_cut_without_tag_name, 0, 0, 2)
    ZEND_ARG_INFO(0, keyword)
    ZEND_ARG_INFO(0, tag_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_php_jieba_insert, 0, 0, 1)
    ZEND_ARG_INFO(0, keyword)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_php_jieba_construct, 0, 0, 5)
    ZEND_ARG_INFO(0, dict)
    ZEND_ARG_INFO(0, hmm)
    ZEND_ARG_INFO(0, user)
    ZEND_ARG_INFO(0, idf)
    ZEND_ARG_INFO(0, stop_words)
ZEND_END_ARG_INFO()

const zend_function_entry php_jieba_methods[] = {
    PHP_ME(PHPJieba, __construct, arginfo_php_jieba_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(PHPJieba, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    PHP_ME(PHPJieba, cut, arginfo_php_jieba_cut, ZEND_ACC_PUBLIC)
    PHP_ME(PHPJieba, cutAll, arginfo_php_jieba_cut_all, ZEND_ACC_PUBLIC)
    PHP_ME(PHPJieba, cutWithoutTagName, arginfo_php_jieba_cut_without_tag_name, ZEND_ACC_PUBLIC)
    PHP_ME(PHPJieba, insert, arginfo_php_jieba_insert, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(PHPJieba)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "PHPJieba", php_jieba_methods);

    jieba_ce = zend_register_internal_class(&ce);
    jieba_ce->create_object = jieba_object_create;
    memcpy(&jieba_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    jieba_object_handlers.clone_obj = NULL;
    jieba_object_handlers.offset = XtOffsetOf(jieba_object, std);
    jieba_object_handlers.free_obj = jieba_object_free_storage;

    zend_declare_property_null(jieba_ce, "dict", sizeof("dict") - 1, ZEND_ACC_PUBLIC);
    zend_declare_property_null(jieba_ce, "hmm", sizeof("hmm") - 1, ZEND_ACC_PUBLIC);
    zend_declare_property_null(jieba_ce, "user", sizeof("user") - 1, ZEND_ACC_PUBLIC);
    zend_declare_property_null(jieba_ce, "idf", sizeof("idf") - 1, ZEND_ACC_PUBLIC);
    zend_declare_property_null(jieba_ce, "stop_words", sizeof("stop_words") - 1, ZEND_ACC_PUBLIC);

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
    zval *self = getThis();

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_STRING(dict, dict_len)
        Z_PARAM_STRING(hmm, hmm_len)
        Z_PARAM_STRING(user, user_len)
        Z_PARAM_STRING(idf, idf_len)
        Z_PARAM_STRING(stop_words, stop_words_len)
    ZEND_PARSE_PARAMETERS_END();

    zend_update_property_string(jieba_ce,  self, ZEND_STRL("dict"), dict);
    zend_update_property_string(jieba_ce,  self, ZEND_STRL("hmm"), hmm);
    zend_update_property_string(jieba_ce,  self, ZEND_STRL("user"), user);
    zend_update_property_string(jieba_ce,  self, ZEND_STRL("idf"), idf);
    zend_update_property_string(jieba_ce,  self, ZEND_STRL("stop_words"), stop_words);

    Jieba handle = NewJieba(dict, hmm, user, idf, stop_words);

    jieba_object *obj = jieba_object_fetch(Z_OBJ_P((self)));
    obj->handler = handle;
}

PHP_METHOD(PHPJieba, __destruct)
{
    zval *self = getThis();
    jieba_object *obj = jieba_object_fetch(Z_OBJ_P((self)));
    FreeJieba(obj->handler);
    RETURN_TRUE;
}

PHP_METHOD(PHPJieba, cutWithoutTagName)
{
    zval *self = getThis();
    char *keyword;
    size_t keyword_len;
    char *tag_name;
    size_t tag_name_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(keyword, keyword_len)
        Z_PARAM_STRING(tag_name, tag_name_len)
    ZEND_PARSE_PARAMETERS_END();

    jieba_object *obj = jieba_object_fetch(Z_OBJ_P((self)));

    CJiebaWord* words = CutWithoutTagName(obj->handler, keyword, keyword_len, tag_name);
    CJiebaWord* x;
    array_init(return_value);
    for (x = words; x && x->word; x++) {
        add_next_index_stringl(return_value, x->word, x->len);
    }

    FreeWords(words);

    return;
}

PHP_METHOD(PHPJieba, cut)
{
    zval *self = getThis();
    char *keyword;
    size_t keyword_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(keyword, keyword_len)
    ZEND_PARSE_PARAMETERS_END();

    jieba_object *obj = jieba_object_fetch(Z_OBJ_P((self)));

    CJiebaWord* words = Cut(obj->handler, keyword, keyword_len);
    CJiebaWord* x;
    array_init(return_value);
    for (x = words; x && x->word; x++) {
        add_next_index_stringl(return_value, x->word, x->len);
    }

    FreeWords(words);

    return;
}

PHP_METHOD(PHPJieba, cutAll)
{
    zval *self = getThis();
    char *keyword;
    size_t keyword_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(keyword, keyword_len)
    ZEND_PARSE_PARAMETERS_END();

    jieba_object *obj = jieba_object_fetch(Z_OBJ_P((self)));

    CJiebaWord* words = CutAll(obj->handler, keyword, keyword_len);
    CJiebaWord* x;
    array_init(return_value);
    for (x = words; x && x->word; x++) {
        add_next_index_string(return_value, x->word);
    }

    FreeWords(words);

    return;
}

PHP_METHOD(PHPJieba, insert)
{
    zval *self = getThis();
    char *keyword;
    size_t keyword_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(keyword, keyword_len)
    ZEND_PARSE_PARAMETERS_END();

    jieba_object *obj = jieba_object_fetch(Z_OBJ_P((self)));

    bool res = JiebaInsertUserWord(obj->handler, keyword);
    if(res){
        RETURN_TRUE;
    }
    RETURN_FALSE;
}


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

/* {{{ jieba_functions[]
 */
static const zend_function_entry jieba_functions[] = {
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
