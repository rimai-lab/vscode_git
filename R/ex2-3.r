species <- unique(iris[,5])

pdf("ex2-3.pdf")
par(mfrow = c(2, 2))
yls = list(c(4, 10), c(2, 6.5), c(1, 9), c(0, 4.2))
linepos =
list(
    list(c(6, 7.8, 7.8, 7.5), c(8, 9, 9, 8.4), c(9.2, 10, 10, 8)),
    list(c(5, 5.6, 5.6, 4.8), c(4, 4.6, 4.6, 4.2), c(5, 6.4, 6.4, 6)),
    list(c(2.4, 6, 6, 5.6), c(6.4, 7.8, 7.8, 7.4), c(8, 8.8, 8.8, 6.4)),
    list(c(1, 2.4, 2.4, 2.1), c(2.6, 3.2, 3.2, 2.8), c(3.6, 4, 4, 2.8))
)

for (j in 1:4) {
    boxplot(lapply(species, function(s){ iris[iris[,5] == s, j] }),
            ylim = yls[[j]], names = species, main = colnames(iris)[j])
    for (k in 1:3) {
        lines(c(k, k, k %% 3 + 1, k %% 3 + 1), linepos[[j]][[k]])

        t_out <- t.test(iris[iris[,5] == species[k], j], iris[iris[,5] == species[k %% 3 + 1], j])
        p_bonf <- p.adjust(t_out$p.value, method="bonferroni", n = 12)

        if (p_bonf < 0.01) {
            tx <- "**"
        } else if (p_bonf < 0.05) {
            tx <- "*"
        } else if (p_bonf < 0.1) {
            tx <- "+"
        } else tx <- ""

        text((k + k %% 3 + 1) / 2, linepos[[j]][[k]][[2]], tx, pos=1)
    }
}

dev.off()
