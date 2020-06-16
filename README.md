# 结巴分词

## 安装

```
g++ -o libjieba.so -fPIC -c -DLOGGING_LEVEL=LL_WARNING -I./include/ lib/jieba.cpp
phpize 
./configure 
make
```

