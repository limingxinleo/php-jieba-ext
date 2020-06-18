--TEST--
insert() Basic test
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

var_dump($jieba->cut('我在中国海洋大学上学'));
$jieba->insert('中国海洋大学');
var_dump($jieba->cut('我在中国海洋大学上学'));

?>
--EXPECT--
array(5) {
  [0]=>
  string(3) "我"
  [1]=>
  string(3) "在"
  [2]=>
  string(6) "中国"
  [3]=>
  string(12) "海洋大学"
  [4]=>
  string(6) "上学"
}
array(4) {
  [0]=>
  string(3) "我"
  [1]=>
  string(3) "在"
  [2]=>
  string(18) "中国海洋大学"
  [3]=>
  string(6) "上学"
}
