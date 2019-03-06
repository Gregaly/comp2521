import queue

items = queue.Queue()
items.put(1000000)

limit = 200

for i in range(limit):
    curr = items.get()
    print(curr)
    items.put(curr//2 - 1)
    items.put(curr*2-1)