--TEST--
jieba_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('jieba')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = jieba_test1();

var_dump($ret);
?>
--EXPECT--
The extension jieba is loaded and working!
NULL
