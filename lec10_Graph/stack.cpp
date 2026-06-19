#include "Maze.h"
#include <stack>
#include <deque>
using namespace std;

// 미로 데이터
const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] =
{
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'}
};

// 이동 가능 여부 검사

bool isValidLoc(int r, int c)
{
    if (r < 0 || c < 0 ||
        r >= MAZE_SIZE || c >= MAZE_SIZE)
        return false;

    else return (map[r][c] == '0' ||
        map[r][c] == 'x');
}

// DFS 미로 탐색
void main()
{
    stack<Location2D> locStack; //위치 스택 객체 생성
    deque<Location2D> locDeque; //위치 덱 객체 생성

    Location2D entry(1, 0);

    locStack.push(entry);
   
    
    int num;
    printf("입력하세요, \n");
    scanf_s("%d", &num);

    if (num == 1) {     //스택 구현
        while (locStack.empty() == false)
        {
            Location2D here = locStack.top();
            locStack.pop();

            int r = here.row;
            int c = here.col;

            printf("(%d,%d)", r, c);

            if (map[r][c] == 'x')
            {
                printf("미로 탐색 성공!\n");
                return;
            }
            else {
                map[r][c] = '.';
                if (isValidLoc(r - 1, c))
                    locStack.push(Location2D(r - 1, c));

                if (isValidLoc(r + 1, c))
                    locStack.push(Location2D(r + 1, c));

                if (isValidLoc(r, c - 1))
                    locStack.push(Location2D(r, c - 1));

                if (isValidLoc(r, c + 1))
                    locStack.push(Location2D(r, c + 1));
            }


        }
        printf("미로 탐색 실패\n");

    }
   
    else if (num == 2) {        //덱 구현
        locDeque.push_front(entry); //덱에 입구 위치 삽입

        while (locDeque.empty() == false) { //덱이 비어있지 않는 동안
            Location2D here = locDeque.front();     //덱에 front 상단 객체 복사
            locDeque.pop_front();   //덱 상단 객체 삭제

            int r = here.row;
            int c = here.col;

            printf("(%d,%d)", r, c);

            if (map[r][c] == 'x')
            {
                printf("미로 탐색 성공!\n");
                return;
            }

            else {      //출구가 아니면 현재 위치를
                map[r][c] = '.';    //현재 위치를 '지나옴' 처리
                if (isValidLoc(r - 1, c))
                    locDeque.push_front(Location2D(r - 1, c));
                if (isValidLoc(r + 1, c))
                    locDeque.push_front(Location2D(r + 1, c));
                if (isValidLoc(r, c - 1))
                    locDeque.push_front(Location2D(r, c - 1));
                if (isValidLoc(r, c + 1))
                    locDeque.push_front(Location2D(r, c + 1));

            }
        }
        printf("미로탐색실패\n");
    }

    else if (num == 3) { //BFS
        locDeque.push_back(entry);

        while (!locDeque.empty())
        {
            Location2D here = locDeque.front();
            locDeque.pop_front();

            int r = here.row;
            int c = here.col;

            printf("(%d,%d) ", r, c);

            if (map[r][c] == 'x')
            {
                printf("미로 탐색 성공!\n");
                return ;
            }

            map[r][c] = '.';

            if (isValidLoc(r - 1, c))
                locDeque.push_back(Location2D(r - 1, c));

            if (isValidLoc(r + 1, c))
                locDeque.push_back(Location2D(r + 1, c));

            if (isValidLoc(r, c - 1))
                locDeque.push_back(Location2D(r, c - 1));

            if (isValidLoc(r, c + 1))
                locDeque.push_back(Location2D(r, c + 1));
        }

        printf("미로 탐색 실패\n");
    
    }
}
