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

WORKDIR /opt/www

ADD . .

RUN ln -s /usr/bin/phpize7 /usr/local/bin/phpize \
    && ln -s /usr/bin/php-config7 /usr/local/bin/php-config \
    && g++ -o libjieba.so -fPIC -c -DLOGGING_LEVEL=LL_WARNING -I./include/ lib/jieba.cpp \
    && phpize \
    && ./configure \
    && make

VOLUME /opt/www/modules
