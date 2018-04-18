outMatrix <- matrix(data = co2, ncol = 12, byrow = T, dimnames = list(1959:1997))

mtrName <- rownames(outMatrix)
mtrMax <- apply(outMatrix, 1, max)
mtrAve <- apply(outMatrix, 1, mean)
mtrMin <- apply(outMatrix, 1, min)
mtrStd <- apply(outMatrix, 1, sd)

mtrs <- c(mtrMax, mtrAve, mtrMin)
cols <- c(4, 1, 3, 2)
pchs <- c(2, 0, 6, 1)
ltys <- c(2, 4, 3, 1)

plot(mtrName, mtrMax, type = "o", col = cols[1], pch = pchs[1], lty = ltys[1], lwd = 1, 
    ylim = c(310, 370), xlim = c(1956, 2000), ylab = "Atmospheric concentrations of CO2 [ppm]", xlab = "Year", 
    main = "max., ave., min., and s.d. of each year")

par(new = T)

plot(mtrName, mtrAve, type = "o", col = cols[2], pch = pchs[2], lty = ltys[2], lwd = 1, 
    ylab = "", xlab = "", ylim = c(310, 370), xlim = c(1956, 2000), axes = F)

par(new = T)

plot(mtrName, mtrMin, type = "o", col = cols[3], pch = pchs[3], lty = ltys[3], lwd = 1, 
    ylab = "", xlab = "", ylim = c(310, 370), xlim = c(1956, 2000), axes = F)

par(new = T)

plot(mtrName, mtrStd, type = "o", col = cols[4], pch = pchs[4], lty = ltys[4], lwd = 1, 
    ylab = "", xlab = "", ylim = c(1.5, 2.5), xlim = c(1956, 2000), axes = F)

axis(side = 4)

legend("topleft", legend = c("Max.", "Ave.", "Min."), col = cols, pch = pchs, lty = ltys)

legend("topright", legend = "s.d.", col = cols[4], pch = pchs[4], lty = ltys[4])