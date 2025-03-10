from collections import defaultdict

# Clase para la estructura de conjuntos disjuntos (Union-Find) con compresión de caminos y unión por tamaño
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)
        if root_u != root_v:
            if self.size[root_u] < self.size[root_v]:
                root_u, root_v = root_v, root_u
            self.parent[root_v] = root_u
            self.size[root_u] += self.size[root_v]
            return True
        return False


def filter_bridges(edges, bridges):
    normalized_egdes = [(min(u, v), max(u, v), idx) for u, v, idx in edges]
    
    count = {}
    
    for u, v, idx in normalized_egdes:
        edge = (u, v)
        if edge in count:
            count[edge].append(idx)
        else:
            count[edge] = [idx]
    
    # Filtramos aquellas combinaciones cuya lista de idx tenga solo un elemento
    non_repeated_idx = [idx[0] for edge, idx in count.items() if len(idx) == 1]

    return [bridge for bridge in bridges if bridge in non_repeated_idx]


# Algoritmo de Tarjan para encontrar puentes en un grafo
def find_bridges(n, edges):
    graph = defaultdict(list)
    for u, v, idx in edges:
        graph[u].append((v, idx))
        graph[v].append((u, idx))

    discovery_time = [-1] * n
    low = [-1] * n
    bridges = set()
    time = 0

    def dfs(u, parent):
        nonlocal time
        discovery_time[u] = low[u] = time
        time += 1
        for v, idx in graph[u]:
            if discovery_time[v] == -1:  # Si v no fue visitado
                dfs(v, u)
                low[u] = min(low[u], low[v])
                if low[v] > discovery_time[u]:  # Es un puente
                    bridges.add(idx)
            elif v != parent:  # No consideres la arista de regreso a `parent`
                low[u] = min(low[u], discovery_time[v])

    for i in range(n):
        if discovery_time[i] == -1:
            dfs(i, -1)

    return filter_bridges(edges, bridges)


# Función principal para resolver el problema
def classify_edges(n, unordered_edges):
    # Ordenar aristas por peso y guardar sus índices originales
    edges = sorted((w, a - 1, b - 1, idx) for idx, (a, b, w) in enumerate(unordered_edges))
    uf = UnionFind(n)
    result = [""] * len(edges)

    i = 0
    while i < len(edges):
        weight = edges[i][0]
        same_weight_edges = []
        while i < len(edges) and edges[i][0] == weight:
            _, u, v, idx = edges[i]
            same_weight_edges.append((u, v, idx))
            i += 1

        bridges = []
        if(len(same_weight_edges) > 1):
            # Construir grafo auxiliar con componentes actuales del AGM parcial
            component_edges = []
            for u, v, idx in same_weight_edges:
                if uf.find(u) != uf.find(v):  # Solo considerar aristas que conecten componentes diferentes
                    component_edges.append((uf.find(u), uf.find(v), idx))

            # Encontrar puentes en el grafo auxiliar
            bridges = find_bridges(n, component_edges)
        else:
            bridges = [same_weight_edges[0][2]]

        # Clasificar las aristas de igual peso
        for u, v, idx in same_weight_edges:
            if uf.find(u) == uf.find(v):
                result[idx] = "none"
            elif idx in bridges:
                result[idx] = "any"
            else:
                result[idx] = "at least one"

        # Unir componentes para las aristas de peso actual
        for u, v, idx in same_weight_edges:
            uf.union(u, v)

    return result

# Lectura de datos de entrada
n, m = map(int, input().split())
edges = [tuple(map(int, input().split())) for _ in range(m)]

# Clasificar cada arista y mostrar el resultado
result = classify_edges(n, edges)
print("\n".join(result))
