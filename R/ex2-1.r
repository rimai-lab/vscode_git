species <- unique(iris[,5])

dev.new()
par(mfcol = c(3, 4))

xls <- list(c(3, 9), c(1, 6), c(0, 8), c(-1, 4))

for (j in 1:4) {
    for (i in 1:3){
        hist(iris[iris[,5] == species[i], j], xlim = xls[[j]], ylim = c(0, 15), breaks = 15,
            xlab = colnames(iris)[1], main = species[i])
    }  
}
