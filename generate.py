from scipy.sparse import rand

m = 10000
n = 100
M = rand(m, n, 0.4)
f = open("data.txt", "w")

f.write(str(m) + " " + str(n) + " " + str(len(M.col)) + "\n")
for i in range(0, len(M.col)):
    f.write(str(M.row[i])+ " " + str(M.col[i]) + " " + str(M.data[i]) + '\n')

