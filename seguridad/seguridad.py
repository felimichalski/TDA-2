from collections import defaultdict
import heapq

def dijkstra(graph, start, n):
    distances = {node: float('inf') for node in range(n)}
    distances[start] = 0
    
    priority_queue = [(0, start)]
    
    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)
        
        if current_distance > distances[current_node]:
            continue
        
        for neighbor, weight in graph[current_node]:
            distance = current_distance + weight
            
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(priority_queue, (distance, neighbor))
    
    return distances

def solve():
    n, m = list(map(int, input().split()))

    graph = defaultdict(list)
    
    for _ in range(m):
        v, w, c = list(map(int, input().split()))
        graph[v].append((w, c))
        graph[w].append((v, c))

    dist_from_start = dijkstra(graph, 0, n)
    
    dist_from_end = dijkstra(graph, n-1, n)

    min_distance = dist_from_start[n-1]
    
    total_cost = 0
    for v in range(n):
        for w, c in graph[v]:
            if dist_from_start[v] + c + dist_from_end[w] == min_distance or dist_from_start[w] + c + dist_from_end[v] == min_distance:
                total_cost += c
    
    print(total_cost)

solve()