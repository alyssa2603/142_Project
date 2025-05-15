import random

N = 300  # Number of nodes
E = 952  # Number of edges for performance test
MAX_LEN = 20
MAX_WT = 20

start_node = 1
end_node = N
weight_constraint = 250  # Arbitrary but tunable

edges = set()
while len(edges) < E:
    u = random.randint(1, N)
    v = random.randint(1, N)
    if u != v:
        edges.add((u, v))

with open("test22_300.in", "w") as f:
    f.write(f"{N}\n")
    f.write(f"{weight_constraint}\n")
    f.write(f"{start_node}\n")
    f.write(f"{end_node}\n")

    for (u, v) in edges:
        length = random.randint(1, MAX_LEN)
        weight = random.randint(1, MAX_WT)
        f.write(f"+ {u} {v} {length} {weight}\n")

    f.write("#\n")
    f.write("f\n")
    f.write("Q\n")