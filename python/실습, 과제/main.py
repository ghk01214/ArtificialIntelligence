from queue import PriorityQueue
import random
import numpy

def attacked_queens_pairs(seqs):
    """
    Calculate the queen logarithm of the attack on the chessboard corresponding to the sequence n]
    We only need to check whether there are other queens on the eight queens of the current chessboard in their respective rows and two diagonals, without judging whether there are other queens in the same column
    """
    a = numpy.array([0] * 81)  # 81개의 0을 가진 1차원 배열 생성
    a = a.reshape(9, 9)  # 9 * 9의 2차원 배열로 변경. 후의 편의를 위해 뒷부분의 8행과 8열만을 판으로 사용한다
    n = 0  # 서로 공격할 수 있는 퀸의 개수

    for i in range(1, 9):
        if seqs[i - 1] != 0: # 만약 시퀸스의 원소가 0이라면 대응되는 행에 퀸이 배치되면 안 된다.
            a[seqs[i - 1]][i] = 1  # Generate the corresponding chessboard sequence, and place it in the order of the first chessboard column

    for i in range(1, 9):
        if seqs[i - 1] == 0:
            continue # If an element of seqs is 0, it represents the corresponding chessboard. If no queen is placed in this column, the next column will be judged directly
        
        for k in list(range(1, i)) + list(range(i + 1, 9)): # 같은 행의 다른 열에 퀸이 없는지 확인
            if a[seqs[i - 1]][k] == 1:  # 다른 퀸이 없으면
                n += 1
        
        up = down = seqs[i - 1]

        for j in range(i - 1, 0, -1):  # 퀸의 위치에서 좌상단/좌하단 방향의 대각선에 다른 퀸 유무 검사
            if up != 1:
                up -= 1
                
                if a[up][j] == 1:
                    n += 1  # 좌상단 대각선 방향에 다른 퀸이 있다

            if down != 8:
                down += 1
                
                if a[down][j] == 1:
                    n += 1  # 좌하단 대각선 방향에 다른 퀸이 있다

        up = down = seqs[i - 1]
        
        for j in range(i + 1, 9):  # 퀸의 위치에서 우상단/우하단 방향의 대각선의 퀸 유무 검사
            if up != 1:
                up -= 1
        
                if a[up][j] == 1:
                    n += 1  # 우상단 대각선 방향에 다른 퀸이 있다

            if down != 8:
                down += 1
           
                if a[down][j] == 1:
                    n += 1  # 우하단 대각선 방향에 다른 퀸이 있다

    return n / 2  # A가 B를 공격하는 것은 B가 A를 공격하는 것과 같으므로 전체 개수의 절반을 return한다.

def display_board(seqs):
    """
     Displays the chessboard corresponding to the sequence
    """
    board = numpy.array([0] * 81)  # Create a one-dimensional array with 81 zeros
    board = board.reshape(9, 9)  # Change to a 9 * 9 two-dimensional array. For the convenience of later use, only the 8 * 8 parts of the last eight rows and columns are used as a blank chessboard

    for i in range(1, 9):
        board[seqs[i - 1]][i] = 1  # According to the sequence, from the first column to the last column, put a queen in the corresponding position to generate the chessboard corresponding to the current sequence
    print('The corresponding chessboard is as follows:')
    for i in board[1:]:
        for j in i[1:]:
            print(j, ' ', end="")  # With end, print doesn't wrap
        print()  # After outputting one line, wrap it. This cannot be print('\n'), otherwise it will be replaced by two lines
    print('The number of queens to attack is' + str(attacked_queens_pairs(seqs)))

def main():
    """
    초기 상태는 Queen이 보드에 없는 상태이다
    g(n) = 배치되지 않은 퀸의 수
    h(n) = 여왕이 서로 공격하는 수의 로그(?) = 28
    """
    priority_queue = [{'unplaced_queens':8, 'pairs':28, 'seqs':[0] * 8}]
    solution = []
    flag = False # 솔루션 발견 여부
    
    while priority_queue:
        first = priority_queue.pop(0)  # Since frontier s are sorted every time, the first sequence is extended

        if first['pairs'] == 0 and first['unplaced_queens'] == 0: # 노드를 확장하기 전에 목표 도달 여부 확인: 만약 h(n)=g(n)=0이면, 목표 노드=솔루션이다
            solution = first['seqs']
            flag = True  # 솔루션 발견
            break
    
        nums = list(range(1, 9))  # 1부터 9까지 들어간 list
        seqs = first['seqs']

        if seqs.count(0) == 0: # Due to the sorting mechanism in the following code, the node that [8 queens have been placed, i.e. g(n)=0, but the number of queens attacking each other is close to 0, but not 0, i.e. h(n)!=0] may be placed in the first place; and this kind of node certainly does not meet the requirements, but such a node cannot be expanded, because the 8 queens have been placed
            continue # You can only skip this kind of node

        for j in range(8):  # 이 시퀸스에서 0의 첫 번째 위치, 즉 퀸이 없는 열 중에서 맨 왼쪽 열에서 퀸을 배치할 행을 선택합니다.
            pos = seqs.index(0) # 퀸이 없는 맨 왼쪽 열의 위치
            temp_seqs = list(seqs)
            temp_column = random.choice(nums)  # 퀸을 배치할 임의의 행을 해당 열에서 선택한다
            temp_seqs[pos] = temp_column # 퀸을 선택된 임의의 행에 배치한다
            nums.remove(temp_column)  # nums list에서 선택된 행의 숫자를 삭제한다.
            priority_queue.append({'unplaced_queens':temp_seqs.count(0), 'pairs':attacked_queens_pairs(temp_seqs),'seqs':temp_seqs})
        
        priority_queue = sorted(priority_queue, key=lambda x:(x['pairs'] + x['unplaced_queens']))

    if solution:
        print('Solution sequence found:' + str(solution))
        display_board(solution)
    else:
        print('Algorithm failed, no solution found')

if __name__ == '__main__':
    main()