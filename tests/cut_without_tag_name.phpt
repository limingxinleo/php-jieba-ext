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

var_dump($jieba->cutWithoutTagName('我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。', 'x'));
?>
--EXPECT--
array(19) {
  [0]=>
  string(3) "我"
  [1]=>
  string(3) "是"
  [2]=>
  string(9) "拖拉机"
  [3]=>
  string(6) "学院"
  [4]=>
  string(15) "手扶拖拉机"
  [5]=>
  string(6) "专业"
  [6]=>
  string(3) "的"
  [7]=>
  string(6) "不用"
  [8]=>
  string(6) "多久"
  [9]=>
  string(3) "我"
  [10]=>
  string(3) "就"
  [11]=>
  string(3) "会"
  [12]=>
  string(6) "升职"
  [13]=>
  string(6) "加薪"
  [14]=>
  string(6) "当上"
  [15]=>
  string(3) "CEO"
  [16]=>
  string(6) "走上"
  [17]=>
  string(6) "人生"
  [18]=>
  string(6) "巅峰"
}
