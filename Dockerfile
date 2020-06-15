# PHPJIEBA
#
# @link     https://www.hyperf.io
# @document https://doc.hyperf.io
# @contact  group@hyperf.io
# @license  https://github.com/hyperf/hyperf/blob/master/LICENSE

ARG PHP_VERSION

FROM hyperf/hyperf:${PHP_VERSION}-alpine-v3.9-base

LABEL maintainer="Hyperf Developers <group@hyperf.io>" version="1.0" license="MIT"

RUN set -ex \
    && apk update \
    && apk add autoconf dpkg-dev dpkg file g++ gcc libc-dev make php7-dev php7-pear pkgconf re2c pcre-dev zlib-dev libtool automake

ADD . .

RUN g++ -o libjieba.so -c -DLOGGING_LEVEL=LL_WARNING -I./include/ lib/jieba.cpp
