<?php

$dict = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/jieba.dict.utf8";
$hmm = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/hmm_model.utf8";
$user = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/user.dict.utf8";
$idf = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/idf.utf8";
$stop = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/stop_words.utf8";

$jieba = new PHPJieba($dict, $hmm, $user, $idf, $stop);

// var_dump($jieba->cut('我去北京广场吃炸鸡'));

// var_dump($jieba->cut('我在知我探索工作'));

$jieba->insert('知我探索');

var_dump($jieba->cut('我在知我探索工作'));
var_dump($jieba->cut('我在知我探索工作'));
var_dump($jieba->cut('我在知我探索工作'));
