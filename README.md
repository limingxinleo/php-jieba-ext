# 结巴分词

鸣谢 [yanyiwu/cppjieba](https://github.com/yanyiwu/cppjieba)

## 安装

```
g++ -o libjieba.so -fPIC -c -DLOGGING_LEVEL=LL_WARNING -I./include/ lib/jieba.cpp
phpize 
./configure 
make
```

## 使用

使用方法详见 examples

