data <- read.csv(file.choose(), header=TRUE, sep=",")


plot ( data$sort ~ data$size, ylab="time (s)", xlab="size")

plot ( data$useIntList ~ data$size, ylab="time (s)", xlab="size")
