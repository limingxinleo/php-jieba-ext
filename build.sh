#!/usr/bin/env sh

export PHP_VERSION=7.2 && docker-compose build jieba-ext
docker run --name jieba7.2 hyperf/jieba:7.2
docker cp jieba7.2:/opt/www/modules/jieba.so build/alpine/jieba-7.2.so
docker rm jieba7.2

export PHP_VERSION=7.3 && docker-compose build jieba-ext
docker run --name jieba7.3 hyperf/jieba:7.3
docker cp jieba7.3:/opt/www/modules/jieba.so build/alpine/jieba-7.3.so
docker rm jieba7.3

export PHP_VERSION=7.4 && docker-compose build jieba-ext
docker run --name jieba7.4 hyperf/jieba:7.4
docker cp jieba7.4:/opt/www/modules/jieba.so build/alpine/jieba-7.4.so
docker rm jieba7.4
