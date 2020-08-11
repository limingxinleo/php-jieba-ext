#!/usr/bin/env sh

mkdir "build"

export PHP_VERSION=7.2 && export ALPINE_VERSION=3.9 && docker-compose build jieba-ext
docker run --name jieba7.2-v3.9 hyperf/jieba:7.2-v3.9
docker cp jieba7.2-v3.9:/opt/www/modules/jieba.so build/jieba-7.2-alpine-v3.9.so
docker rm jieba7.2-v3.9

PHPS="7.3 7.4"
ALPINES="3.9 3.10 3.11"

for PHP_VERSION in ${PHPS} ; do
  for ALPINE_VERSION in ${ALPINES} ; do
    export PHP_VERSION=${PHP_VERSION} && export ALPINE_VERSION=${ALPINE_VERSION} && docker-compose build jieba-ext
    docker run --name jieba${PHP_VERSION}-v${ALPINE_VERSION} hyperf/jieba:${PHP_VERSION}-v${ALPINE_VERSION}
    docker cp jieba${PHP_VERSION}-v${ALPINE_VERSION}:/opt/www/modules/jieba.so build/jieba-${PHP_VERSION}-alpine-v${ALPINE_VERSION}.so
    docker rm jieba${PHP_VERSION}-v${ALPINE_VERSION}
  done
done
