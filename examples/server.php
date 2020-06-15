<?php

$dict = __DIR__ . "/../dict/jieba.dict.utf8";
$hmm = __DIR__ . "/../dict/hmm_model.utf8";
$user = __DIR__ . "/../dict/user.dict.utf8";
$idf = __DIR__ . "/../dict/idf.utf8";
$stop = __DIR__ . "/../dict/stop_words.utf8";

$jieba = new PHPJieba($dict, $hmm, $user, $idf, $stop);
$jieba->insert("知我探索");

$http = new Swoole\Http\Server("0.0.0.0", 9501, SWOOLE_BASE, SWOOLE_SOCK_TCP);

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
