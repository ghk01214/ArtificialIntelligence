# 2017182004 김건호
# A* 알고리즘을 이용한 N-queen 문제 풀이

from queue import PriorityQueue
from random import randint

class State:
    def __init__(self, board, goal, queen, moves = 0):
        self.board = board
        self.goal = goal
        self.moves = moves
        self.queen = queen

    def MakeNewBoard(self, moves):
        

    # child node를 확장 후 list에 저장하여서 반환
    def expand(self, moves, queen):
        result = []

        for i in range(queen):
            result.append(self.MakeNewBoard())


    # f(n)을 계산하여 반환
    def f(self):
        return self.g() + self.h()
    
    # root node로부터 현재 node까지의 깊이 반환
    def g(self):
        return self.moves

    def h(self):
        return sum([1 if self.board[i]] != self.goal[i] else 0 for i in range(len(self.board)))

    def __eq__(self, other):
        return self.board == other.board

    # Queue 내의 상태와 상태 비교를 위한 less than 연산자 정의
    def __lt__(self, other):
        return self.f() < other.f()

    def __gt__(self, other):
        return self.f() > other.f()

    # def __str__(self):
    #     return "f(n) = g(n) + h(n) ==> " + str(self.f()) + " = " +\
    #         str(self.g()) + " + " + str(self.h()) + "\n" +\
    #         str()

def main():
    print("2017182004 김건호")
    print("A* 알고리즘을 이용한 N-queen 문제 풀이")

    queen = int(input("퀸의 개수를 입력하세요 : "))

    puzzle = []
    goal = []

    InitializeBoard(puzzle, goal, queen)

    # open list는 PriorityQueue로 생성
    # (PriorityQueue는 C++의 Assosiative Container인 Set, Map과 같은 역할을 하는 Queue이다)
    openQueue = PriorityQueue()
    openQueue.put(State(puzzle, goal, queen))
    closedQueue = []
    moves = 0

# 입력받은 Queen의 개수에 따라 초기 상태와 목표 상태를 초기화
def InitializeBoard(board, goal, boardSize):
    for i in range(boardSize):
        # Queen의 위치를 각 열의 중복되지 않는 행 중 랜덤한 위치에 초기화
        startPosition = randint(0, boardSize - 1)

        while startPosition in board:
            startPosition = randint(0, boardSize - 1)

        board.append(startPosition)

        goalPosition = i * 2

        # 입력한 Queen의 개수가 짝수이면 홀수 자리에 먼저 들어간 다음 짝수 자리에 들어간다
        if boardSize % 2 == 0:
            goalPosition += 1

            if goalPosition < boardSize:
                goal.append(goalPosition)
            else:
                goal.append(goalPosition - (boardSize + 1))
        # 입력한 Queen의 개수가 홀수이면 짝수 자리에 먼저 들어간 다음 홀수 자리에 들어간다
        else:
            if goalPosition < boardSize:
                goal.append(goalPosition)
            else:
                goal.append(goalPosition - boardSize)

if __name__ == '__main__':
    main()