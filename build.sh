#!/usr/bin/env sh

export PHP_VERSION=7.2 && docker-compose build jieba-ext
docker run --name jieba7.2 hyperf/jieba:7.2
docker cp jieba7.2:/opt/www/modules/jieba.so build/alpine/7.2/jieba.so
docker rm jieba7.2
