/* jieba extension for PHP */

#ifndef PHP_JIEBA_H
# define PHP_JIEBA_H

extern zend_module_entry jieba_module_entry;
# define phpext_jieba_ptr &jieba_module_entry

# define PHP_JIEBA_VERSION "1.1.0"

# if defined(ZTS) && defined(COMPILE_DL_JIEBA)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_JIEBA_H */
