import math

def main():
    testCases = int(input())
    for _ in range(testCases):
        data = input().split()
        n = int(data[0])
        c = int(data[1])
        stalls = []
        for _ in range(n):
            stalls.append(int(input()))

        stalls.sort()
        minPos = stalls[0]
        maxPos = stalls[-1]

        maxDistance = maxPos - minPos

        res = calc(c, stalls, 1, maxDistance)

        print(res)

def calc(cows, positions, minVal, maxVal):
    half = math.trunc((maxVal + minVal) / 2)
    
    if(canAssign(cows, positions, half)):
        if(minVal >= maxVal):
            return half
        else:
            return calc(cows, positions, half + 1, maxVal)
    else:
        return calc(cows, positions, minVal, half - 1)

def canAssign(cows, positions, distance):
    lastPos = positions[0]
    cows -= 1

    for pos in positions:
        if(lastPos + distance <= pos):
            lastPos = pos
            cows -= 1
            if(cows == 0):
                return True

    return False

main()