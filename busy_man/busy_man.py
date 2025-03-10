test_cases = int(input())
for _ in range(test_cases):
    activities = int(input())
    pairs = []
    for _ in range(activities):
        data = input().split(" ")
        pairs.append((int(data[0]), int(data[1])))

    pairs.sort(key=lambda x: x[1])

    if(len(pairs) > 0):
        solution = [pairs.pop(0)]
        for element in pairs:
            if solution[-1][1] <= element[0]:
                solution.append(element)

    print(len(solution))