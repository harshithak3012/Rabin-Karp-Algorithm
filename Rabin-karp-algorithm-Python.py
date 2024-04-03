def search(pat, txt, q):
    M = len(pat)
    N = len(txt)
    d = 256
    h = 1
    found = False

    for i in range(M - 1):
        h = (h * d) % q

    p = 0
    t = 0
    for i in range(M):
        p = (d * p + ord(pat[i])) % q
        t = (d * t + ord(txt[i])) % q

    for i in range(N - M + 1):
        if p == t:
            for j in range(M):
                if txt[i + j] != pat[j]:
                    break
            if j == M - 1:
                print("Pattern found at index", i + 1)
                found = True
        if i < N - M:
            t = (d * (t - ord(txt[i]) * h) + ord(txt[i + M])) % q
            if t < 0:
                t = t + q

    if not found:
        print("Pattern not found.")


if __name__ == "__main__":
    filename = "input.txt"
    numTestCases = 4

    with open(filename, "r") as inputFile:
        for testCase in range(numTestCases):
            txt = inputFile.readline().rstrip('\n')
            pat = inputFile.readline().rstrip('\n')
            print("\nOutput of testcase", testCase + 1, ":")
            search(pat, txt, float('inf'))
