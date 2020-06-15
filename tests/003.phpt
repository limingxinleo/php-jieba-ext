--TEST--
jieba_test2() Basic test
--SKIPIF--
<?php
if (!extension_loaded('jieba')) {
	echo 'skip';
}
?>
--FILE--
<?php
var_dump(jieba_test2());
var_dump(jieba_test2('PHP'));
?>
--EXPECT--
string(11) "Hello World"
string(9) "Hello PHP"
