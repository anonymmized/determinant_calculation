def determinant(matrix):
    n = len(matrix)
    A = [row[:] for row in matrix]
    det = 1
    swaps = 0
    for i in range(n):
        if A[i][i] == 0:
            for k in range(i + 1, n):
                if A[k][i] != 0:
                    A[i], A[k] = A[k], A[i]
                    swaps += 1
                    break
            else:
                return 0
        
        for j in range(i + 1, n):
            factor = A[j][i] / A[i][i]
            for k in range(i, n):
                A[j][k] -= factor * A[i][k]
    for i in range(n):
        det *= A[i][i]
    
    if swaps % 2 == 1:
        det = -det
    
    return round(det)

def main(columns, rows):

    opred = []

    for i in range(columns):
        rc = []
        for j in range(rows):
            num = int(input(f"Enter [A]{i + 1}{j + 1} elem: "))
            rc.append(num)
        opred.append(rc)

    max_len = max(len(str(x)) for row in opred for x in row)

    answ = determinant(opred)
    mid_row = rows // 2
    for i, row in enumerate(opred):
        if i == mid_row:
            print("|", " ".join(f"{x:>{max_len}}" for x in row), f"| = {answ}")
        else:
            print("|", " ".join(f"{x:>{max_len}}" for x in row), f"|")

if __name__ == "__main__":
    columns = int(input("Enter rows count: "))
    rows = int(input("Enter columns count: "))
    main(columns, rows)