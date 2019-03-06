a = [1000000]
b = []

end = False

while len(a) < 200:
    for i in range(0, len(a)):
        print(a[i])
        #print("a: ", a)
        b.append((a[i]//2)-1)
        b.append((a[i]*2)-1)
        #print("b: ", b)
    a = b
    b = []
