require(graphics)
lm <- c(-1, 2)
# a 2-dimensional example
par(mfrow = c(2, 2))
# 正規分布に従う乱数列を生成
x <- rbind(matrix(rnorm(100, sd = 0.3), ncol = 2),
           matrix(rnorm(100, mean = 1, sd = 0.3), ncol = 2))
colnames(x) <- c("x", "y")
# クラスタリング-2分割
(cl <- kmeans(x, 2))
plot(x, col = cl$cluster, xlim = lm, ylim = lm)
points(cl$centers, col = 1:2, pch = 8, cex = 2)

# sum of squares
# scaleで中心化、2乗和を返す
ss <- function(x) sum(scale(x, scale = FALSE)^2)

## cluster centers "fitted" to each obs.:
# 回帰分析

fitted.x <- fitted(cl); # head(fitted.x)
plot(fitted.x, col = cl$cluster, xlim = lm, ylim = lm)
resid.x <- x - fitted(cl)
## Equalities : ----------------------------------
#cbind(cl[c("betweenss", "tot.withinss", "totss")], # the same two columns
#         c(ss(fitted.x), ss(resid.x),    ss(x)))
#stopifnot(all.equal(cl$ totss,        ss(x)),
#          all.equal(cl$ tot.withinss, ss(resid.x)),
#          ## these three are the same:
#          all.equal(cl$ betweenss,    ss(fitted.x)),
#          all.equal(cl$ betweenss, cl$totss - cl$tot.withinss),
#          ## and hence also
#          all.equal(ss(x), ss(fitted.x) + ss(resid.x))
#          )
#
#kmeans(x,1)$withinss # trivial one-cluster, (its W.SS == ss(x))
#
## random starts do help here with too many clusters
## (and are often recommended anyway!):
#(cl <- kmeans(x, 5, nstart = 25))
#plot(x, col = cl$cluster, xlim = lm, ylim = lm)
#points(cl$centers, col = 1:5, pch = 8)
#
#fitted.x <- fitted(cl); # head(fitted.x)
#plot(fitted.x, col = cl$cluster, xlim = lm, ylim = lm)