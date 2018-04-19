require(graphics)

### Example 1: Violent crime rates by US state
#
#hc <- hclust(dist(USArrests), "ave")
## dist: 距離行列を生成
#plot(hc)
#plot(hc, hang = -1)
## hang = -1: ラベルの高さを揃える
#
## Do the same with centroid clustering and *squared* Euclidean distance,
## cut the tree into ten clusters and reconstruct the upper part of the
## tree from the cluster centers.

## 重心クラスタリングと*二乗*ユークリッド距離を同じにしてツリーを10個のクラスターに分割し、
## クラスターの中心からツリーの上部を再構成します。

hc <- hclust(dist(USArrests)^2, "cen")
## 二乗距離でクラスター分析
memb <- cutree(hc, k = 10)
## 個体が10クラスターのどれに属するかの情報を返す
cent <- NULL
for(k in 1:10){
  cent <- rbind(cent, colMeans(USArrests[memb == k, , drop = FALSE]))
}
## cent: クラスタごとの中心
hc1 <- hclust(dist(cent)^2, method = "cen", members = table(memb))
## 10の中心を用いてクラスター分析
opar <- par(mfrow = c(1, 2))
plot(hc,  labels = FALSE, hang = -1, main = "Original Tree")
plot(hc1, labels = FALSE, hang = -1, main = "Re-start from 10 clusters")
par(opar)

### Example 2: Straight-line distances among 10 US cities
##  Compare the results of algorithms "ward.D" and "ward.D2"

data(UScitiesD)
## データセット UScitiesD をロード
mds2 <- -cmdscale(UScitiesD)
## 主座標分析を行う

plot(mds2, type="n", axes=FALSE, ann=FALSE)
text(mds2, labels=rownames(mds2), xpd = NA)
## ２次元グラフにプロット

## Ward 法 (最小分散法)
## OTU間の距離平方和の増加量が最小となるよう併合

hcity.D  <- hclust(UScitiesD, "ward.D") # "wrong"
hcity.D2 <- hclust(UScitiesD, "ward.D2")

opar <- par(mfrow = c(1, 2))
plot(hcity.D,  hang=-1)
plot(hcity.D2, hang=-1)
par(opar)
