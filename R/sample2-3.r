species <- unique(iris[,5])
dev.new()
boxplot(lapply(species, function(s){ iris[iris[,5]==s, 1] }),
names=species, main=colnames(iris)[1])
lines(c(1,1,2,2), c(6,7.8,7.8,7.5))
# 第1引数はx軸の値, 第2引数はy軸の値
# (1,6) -> (1, 7.8) -> (2, 7.8) -> (2, 7.5) と線を引く
# boxplotの場合、特に指定しなければ、
# 各箱の位置が左から1, 2, 3 … の座標となる。
text(1.5, 7.8, "*", pos=1) # 線の上に出す場合pos=3
# よく使われる記号
# +: 0.1, *: 0.05, **: 0.01
# (分野によるので要確認)