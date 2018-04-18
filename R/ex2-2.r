species <- unique(iris[,5])

dev.new()
par(mfrow = c(2, 2))

for (i in 1:4) {
    boxplot(lapply(species, function(s){ iris[iris[,5] == s, i] }),
            names = species, main = colnames(iris)[i])
}