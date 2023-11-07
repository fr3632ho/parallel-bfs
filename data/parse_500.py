import sys

print(sys.argv)
assert len(sys.argv) == 2

out_file = sys.argv[1]

S = set()
data = sys.stdin.read().strip().split('\n')
out = []
for line in data:
    a, b = line.split(" ")
    S.add(a), S.add(b)

print(f"N={len(S)}, M={len(data)}")

old_stdout = sys.stdout
sys.stdout = open(out_file, 'w')

sys.stdout.write(f"{len(S)} {len(data)}\n")

for line in data:
    ll = ' '.join(map(str, map(lambda x : int(x) - 1, line.split(" "))))
    sys.stdout.write(ll + '\n')

sys.stdout = old_stdout
print(f"Data parsed - find input file in {out_file}")
