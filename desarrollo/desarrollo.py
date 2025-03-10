INF = float('inf')

def floyd_warshall(graph):
    n = len(graph)
    dist = [[graph[i][j] for j in range(n)] for i in range(n)]

    for k in range(n):
        for i in range(n):
            for j in range(n):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

    return dist

def solve():
    n = int(input())
    distances = [list(map(int, input().split())) for _ in range(n)]
    ordered_nodes = list(map(lambda x: int(x) - 1, input().split()))

    result = []

    active_nodes = list()

    for node in reversed(ordered_nodes):
        active_nodes.append(node)
        k = len(active_nodes)
        graph = [[INF] * k for _ in range(k)]

        active_nodes_indices = {active_nodes[i]: i for i in range(k)}

        for i in active_nodes:
            for j in active_nodes:
                graph[active_nodes_indices[i]][active_nodes_indices[j]] = distances[i][j]

        total_distance = sum(sum(row) for row in floyd_warshall(graph))
        result.append(total_distance)

    print(" ".join(map(str, reversed(result))))


if __name__ == "__main__":
    solve()