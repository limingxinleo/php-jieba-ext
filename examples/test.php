<?php

$dict = __DIR__ . "/../dict/jieba.dict.utf8";
$hmm = __DIR__ . "/../dict/hmm_model.utf8";
$user = __DIR__ . "/../dict/user.dict.utf8";
$idf = __DIR__ . "/../dict/idf.utf8";
$stop = __DIR__ . "/../dict/stop_words.utf8";

$jieba = new PHPJieba($dict, $hmm, $user, $idf, $stop);

var_dump($jieba->cut('我去北京广场吃炸鸡'));

var_dump($jieba->cut('我在知我探索工作'));
var_dump($jieba->cutAll('和恋人和好'));

$jieba->insert('知我探索');
$jieba->insert('和好');

var_dump($jieba->cutAll('我在知我探索工作'));
var_dump($jieba->cutAll('和恋人和好'));

var_dump($jieba->cut('我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。'));

var_dump($jieba->cutWithoutTagName('我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。', 'x'));

