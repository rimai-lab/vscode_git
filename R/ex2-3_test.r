species <- unique(iris[,5])

#dev.new()
#par(mfrow = c(2, 2))

#for (i in 1:4) {
#    boxplot(lapply(species, function(s){ iris[iris[,5] == s, i] }),
#            names = species, main = colnames(iris)[i])
#}

for (j in 1:4) {
    for (k in 1:3) {
        cat(paste(colnames(iris)[j], ", ", species[k], " vs. ", species[k %% 3 + 1], "\n"), file = 'ex2-3_result.txt', append = TRUE)

        t_out <- t.test(iris[iris[,5] == species[k], j], iris[iris[,5] == species[k %% 3 + 1], j])
        cat(paste(t_out$p.value * 12, "\n"), file = 'ex2-3_result.txt', append = TRUE)
    }
}


