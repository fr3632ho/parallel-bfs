import sys

data = sys.stdin.read().strip().split('\n')

assert len(sys.argv) == 2

out_file = sys.argv[1]

N,M, _, _ = map(int, data[0].split(" "))
edges = []
for line in data[1:M+1]:
    a, b, _ = map(int, line.split(" "))
    edges.append((a,b))


old_out = sys.stdout
sys.stdout = open(out_file, 'w')
print(f"{N} {M}")
for a, b in edges:
    print(f"{a} {b}")
sys.stdout = old_out

print(f"Sample with outfile \"{out_file}\" parsed")

