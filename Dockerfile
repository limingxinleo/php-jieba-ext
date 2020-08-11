# PHPJIEBA
#
# @link     https://www.hyperf.io
# @document https://doc.hyperf.io
# @contact  group@hyperf.io
# @license  https://github.com/hyperf/hyperf/blob/master/LICENSE

ARG PHP_VERSION
ARG ALPINE_VERSION

FROM hyperf/hyperf:${PHP_VERSION}-alpine-v${ALPINE_VERSION}-dev

LABEL maintainer="Hyperf Developers <group@hyperf.io>" version="1.0" license="MIT"

WORKDIR /opt/www

ADD . .

RUN g++ -o libjieba.so -fPIC -c -DLOGGING_LEVEL=LL_WARNING -I./include/ lib/jieba.cpp \
    && phpize \
    && ./configure \
    && make

VOLUME /opt/www/modules
