<?php

$dict = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/jieba.dict.utf8";
$hmm = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/hmm_model.utf8";
$user = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/user.dict.utf8";
$idf = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/idf.utf8";
$stop = "/Users/limx/Applications/GitHub/limingxinleo/php-jieba-ext/dict/stop_words.utf8";

$jieba = new PHPJieba($dict, $hmm, $user, $idf, $stop);
$jieba->insert("知我探索");

$http = new Swoole\Http\Server("127.0.0.1", 9501, SWOOLE_BASE, SWOOLE_SOCK_TCP);

$http->set([
    'enable_coroutine' => true,
    'worker_num' => 1,
    'open_tcp_nodelay' => true,
    'max_coroutine' => 100000,
    'open_http2_protocol' => true,
    'max_request' => 0,
    'socket_buffer_size' => 2 * 1024 * 1024,
    'package_max_length' => 2 * 1024 * 1024,
]);

$http->on('request', function ($request, $response) use ($jieba) {
    $keyword = $request->get['keyword'] ?? '';
    $result = [];
    if ($keyword) {
        $result = $jieba->cut($keyword);
    }
    $response->header('Content-Type', 'application/json');
    $response->end(json_encode([
        'code' => 0,
        'data' => $result,
    ], JSON_UNESCAPED_UNICODE));
});

$http->start();
