--TEST--
cut() Basic test
--SKIPIF--
<?php
if (!extension_loaded('jieba')) {
	echo 'skip';
}
?>
--FILE--
<?php
$dict = __DIR__ . "/../dict/jieba.dict.utf8";
$hmm = __DIR__ . "/../dict/hmm_model.utf8";
$user = __DIR__ . "/../dict/user.dict.utf8";
$idf = __DIR__ . "/../dict/idf.utf8";
$stop = __DIR__ . "/../dict/stop_words.utf8";

$jieba = new PHPJieba($dict, $hmm, $user, $idf, $stop);

var_dump($jieba->cut('我去北京广场吃炸鸡'));

?>
--EXPECT--
array(6) {
  [0]=>
  string(3) "我"
  [1]=>
  string(3) "去"
  [2]=>
  string(6) "北京"
  [3]=>
  string(6) "广场"
  [4]=>
  string(3) "吃"
  [5]=>
  string(6) "炸鸡"
}
