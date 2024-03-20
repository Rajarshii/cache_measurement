import matplotlib.pyplot as plt

d = {}
for line in open('Data.txt'):
    t = line.split(',')
    size, stride, time = int(t[0]), int(t[1]), float(t[2])
    d.setdefault(stride, []).append((size,time))

for stride in sorted(d.keys()):
    if stride >= 512: continue

    xs, ys = zip(*d[stride])
    plt.plot(xs, ys, label=str(stride))
    print(stride, len(d[stride]))

plt.xscale('linear')
plt.xlabel('size (B)')
plt.ylabel('access time (ns)')
plt.legend()
plt.show()
