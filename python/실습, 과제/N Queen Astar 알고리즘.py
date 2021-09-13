# 2017182004 김건호
# A* 알고리즘을 이용한 N-queen 문제 풀이

from queue import PriorityQueue
import random
import numpy
import time

class State:
    def __init__(self, chessBoard, queen, attackablePairs, placeOrder):
        self.chessBoard = chessBoard                 # 출력할 체스판
        self.queen = queen                           # 체스판에 배치되지 않은 Queen
        self.attackablePairs = attackablePairs       # Queen이 다른 Queen을 공격할 수 있는 총 경우의 수
        self.placeOrder = placeOrder                 # 열순대로 Queen의 행 위치를 표시한 배열


    def GetNewchessBoard(self, placeOrder, boardSize):
        newQueen = placeOrder.count(0)
        newattackablePairs = self.FindQueenattackablePairs(placeOrder, boardSize)

        return State(self.chessBoard, newQueen, newattackablePairs, placeOrder)

    # 서로 공격할 수 있는 Queen의 수를 계산하여 반환
    def FindQueenattackablePairs(self, placeOrder, boardSize):
        attackablePairs = 0                                          # 서로 공격할 수 있는 퀸의 개수
        chessBoard = numpy.array([0] * boardSize * boardSize)        # 81개의 0을 가진 1차원 배열 생성
        chessBoard = chessBoard.reshape(boardSize, boardSize)        # 9 * 9의 2차원 배열로 변경. 후의 편의를 위해 뒷부분의 8행과 8열만을 판으로 사용한다

        for i in range(1, boardSize):
            if placeOrder[i - 1] != 0:                     # 만약 시퀸스의 원소가 0이라면 대응되는 행에 퀸이 배치되면 안 된다.
               chessBoard[placeOrder[i - 1]][i] = 1        # Queen이 놓인 자리를 1로 표시한다

        for i in range(1, boardSize):
            if placeOrder[i - 1] == 0:
                continue                                   # 해당 열에 Queen이 놓이지 않았으면 다음 열을 로드한다.
            
            for j in list(range(1, i)) + list(range(i + 1, boardSize)):    # 같은 행의 다른 열에 퀸이 없는지 확인
                if chessBoard[placeOrder[i - 1]][j] == 1:                  # 다른 퀸이 있으면
                    attackablePairs += 1
            
            up = down = placeOrder[i - 1]

            for j in range(i - 1, 0, -1):                      # 퀸의 위치에서 좌상단/좌하단 방향의 대각선에 다른 퀸 유무 검사
                if up != 1:
                    up -= 1
                    
                    if chessBoard[up][j] == 1:
                        attackablePairs += 1                   # 좌상단 대각선 방향에 다른 퀸이 있다

                if down != boardSize - 1:
                    down += 1
                    
                    if chessBoard[down][j] == 1:
                        attackablePairs += 1                   # 좌하단 대각선 방향에 다른 퀸이 있다

            up = down = placeOrder[i - 1]
            
            for j in range(i + 1, boardSize):                  # 퀸의 위치에서 우상단/우하단 방향의 대각선의 퀸 유무 검사
                if up != 1:
                    up -= 1
            
                    if chessBoard[up][j] == 1:
                        attackablePairs += 1                   # 우상단 대각선 방향에 다른 퀸이 있다

                if down != boardSize - 1:
                    down += 1
            
                    if chessBoard[down][j] == 1:
                        attackablePairs += 1                   # 우하단 대각선 방향에 다른 퀸이 있다
        
        self.chessBoard = chessBoard
 
        return int(attackablePairs / 2)                        # A가 B를 공격하는 것은 B가 A를 공격하는 것과 같으므로 전체 개수의 절반을 return한다.

    # child node 확장
    def expand(self, boardSize):
        results = []
        nums = list(range(1, boardSize))

        for i in range(boardSize - 1):
            emptyRow = self.placeOrder.index(0)
            tempSeq = list(self.placeOrder)
            tempLine = random.choice(nums)
            tempSeq[emptyRow] = tempLine

            nums.remove(tempLine)

            results.append(self.GetNewchessBoard(tempSeq, boardSize))

        return results

    # 체스판 출력
    def PrintchessBoard(self):
        for i in self.chessBoard[1:]:
            for j in i[1:]:
                print(j, ' ', end = "")

            print()

    # f(n)을 계산하여 반환
    def f(self):
        return self.g() + self.h()
    
    # 현재 배치되지 않은 Queen의 수 = root node로부터 현재 node까지의 거리(깊이)
    def g(self):
        return self.queen

    # Queen이 다른 Queen을 공격할 수 있는 총 경우의 수
    def h(self):
        return self.attackablePairs

    # Queue 내의 상태와 상태 비교를 위한 less than 연산자 정의
    def __lt__(self, other):
        return self.f() < other.f()

    def __gt__(self, other):
        return self.f() > other.f()

def main():
    print("2017182004 김건호")
    print("A* 알고리즘을 이용한 N-queen 문제 풀이")

    queen = int(input("퀸의 개수를 입력하세요 : "))

    startTime = time.time()

    boardSize = queen + 1
    attackablePairs = queen * (queen - 1) / 2 # 한 개의 퀸이 공격할 수 있는 퀸의 개수는 전체 퀸의 개수 중 자기 자신을 제외한 나머지
    placeOrder = [0] * queen

    chessBoard = numpy.array([0] * boardSize * boardSize)  # 81개의 0을 가진 1차원 배열 생성
    chessBoard = chessBoard.reshape(boardSize, boardSize)  # 9 * 9의 2차원 배열로 변경. 후의 편의를 위해 뒷부분의 8행과 8열만을 판으로 사용한다

    # open list는 PriorityQueue로 생성
    # (PriorityQueue는 C++의 Assosiative Container인 Set, Map과 같은 역할을 하는 Queue이다)
    openQueue = PriorityQueue()

    openQueue.put(State(chessBoard, queen, attackablePairs, placeOrder))
    closedQueue = []

    while not openQueue.empty():
        currentState = openQueue.get()
        
        if currentState.f() == 0:
            print("\n탐색 성공")
            print(currentState.placeOrder)
            currentState.PrintchessBoard()
            break

        if (currentState.placeOrder.count(0) == 0):
            continue

        for state in currentState.expand(boardSize):
            if state not in closedQueue:
                openQueue.put(state)
        
        closedQueue.append(currentState)

    endTime = time.time()
    print('탐색 경과 시간 : ' + str('%2f' % (endTime - startTime)) + '초')

if __name__ == '__main__':
    main()