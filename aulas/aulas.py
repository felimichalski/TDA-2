from collections import deque

def edmonds_karp(capacity, source, sink):
    n = len(capacity)
    flow = [[0] * n for _ in range(n)]
    parent = [-1] * n

    def bfs():
        nonlocal parent
        parent = [-1] * n
        parent[source] = source
        queue = deque([source])
        while queue:
            u = queue.popleft()
            for v in range(n):
                if parent[v] == -1 and capacity[u][v] - flow[u][v] > 0:
                    parent[v] = u
                    if v == sink:
                        return True
                    queue.append(v)
        return False

    max_flow = 0
    while bfs():
        path_flow = float('Inf')
        v = sink
        while v != source:
            u = parent[v]
            path_flow = min(path_flow, capacity[u][v] - flow[u][v])
            v = u

        v = sink
        while v != source:
            u = parent[v]
            flow[u][v] += path_flow
            flow[v][u] -= path_flow
            v = u

        max_flow += path_flow

    return max_flow, flow

def solve_problem(n, m, a, b, edges):
    total_excess = 0
    total_deficit = 0
    source = n
    sink = n + 1
    graph_size = n + 2
    capacity = [[0] * graph_size for _ in range(graph_size)]

    for i in range(n):
        if a[i] > b[i]:
            capacity[source][i] = a[i] - b[i]
            total_excess += a[i] - b[i]
        elif a[i] < b[i]:
            capacity[i][sink] = b[i] - a[i]
            total_deficit += b[i] - a[i]

    for p, q in edges:
        capacity[p][q] = 100  # Capacidad suficientemente grande
        capacity[q][p] = 100

    if total_excess != total_deficit:
        return "NO"

    max_flow, flow = edmonds_karp(capacity, source, sink)

    if max_flow != total_excess:
        return "NO"

    # Construir la matriz de movimientos
    moves = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if flow[i][j] > 0:
                moves[i][j] = flow[i][j]

    return "YES", moves

if __name__ == "__main__":
    n, m = map(int, input().split())

    a_values = list(map(int, input().split()))
    b_values = list(map(int, input().split()))

    edges = []

    for _ in range(m):
        p, q = map(int, input().split())
        edges.append((p - 1, q - 1))

    # Resolver el problema
    result = solve_problem(n, m, a_values, b_values, edges)

    if result == "NO":
        print("NO")
    else:
        print("YES")
        moves = result[1]
        for row in moves:
            print(" ".join(map(str, row)))
