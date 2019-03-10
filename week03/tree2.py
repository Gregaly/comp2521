import queue
start = ord('o') + ord('w') + ord('o') 
upper = 2 * start
lower = 0
limit = 32

DEBUG = False
dprint = print if DEBUG else lambda *x:...

items = queue.Queue()
items.put((start,start//2))

limit = start

count = 0

while True:
	if count > limit:
		break

	if items.empty():
		break

	curr, diff = items.get()
	print(curr)
	count += 1

	if diff == 0 :
		dprint("breaking cuz 0 @", curr)
		continue;
	dprint("now: ", curr, "adding", ((curr-diff), diff//2), ((curr+diff), diff//2))
	items.put(((curr-diff), diff//2))
	items.put(((curr+diff), diff//2))

