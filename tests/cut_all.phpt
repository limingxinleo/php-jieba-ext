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

var_dump($jieba->cutAll('我是山东大学计算机科学与技术专业'));
?>
--EXPECT--
array(14) {
  [0]=>
  string(3) "我"
  [1]=>
  string(3) "是"
  [2]=>
  string(6) "山东"
  [3]=>
  string(12) "山东大学"
  [4]=>
  string(6) "东大"
  [5]=>
  string(6) "大学"
  [6]=>
  string(6) "计算"
  [7]=>
  string(9) "计算机"
  [8]=>
  string(15) "计算机科学"
  [9]=>
  string(6) "算机"
  [10]=>
  string(6) "科学"
  [11]=>
  string(3) "与"
  [12]=>
  string(6) "技术"
  [13]=>
  string(6) "专业"
}
