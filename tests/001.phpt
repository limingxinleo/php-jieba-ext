--TEST--
Check if jieba is loaded
--SKIPIF--
<?php
if (!extension_loaded('jieba')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "jieba" is available';
?>
--EXPECT--
The extension "jieba" is available
