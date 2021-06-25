#!/usr/bin/env sh

mkdir "build"

if [ -f ".env" ]; then
  source ".env"
fi

docker-compose build jieba-ext
docker run --name jieba${PHP_VERSION}-v${ALPINE_VERSION} hyperf/jieba:${PHP_VERSION}-v${ALPINE_VERSION}
docker cp jieba${PHP_VERSION}-v${ALPINE_VERSION}:/opt/www/modules/jieba.so build/jieba-${PHP_VERSION}-alpine-v${ALPINE_VERSION}.so
docker rm jieba${PHP_VERSION}-v${ALPINE_VERSION}
