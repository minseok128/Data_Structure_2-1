#include <iostream>
#include <random>

#define EXIT_ROW 10
#define EXIT_COL 30
using namespace std;
int main()
{
    int maze[EXIT_ROW + 2][EXIT_COL + 2] = {0};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    
    // 미로 외벽 초기화
    for (int i = 0; i < EXIT_ROW + 2; ++i) {
        maze[i][0] = maze[i][EXIT_COL + 1] = 1;
    }
    for (int i = 0; i < EXIT_COL + 2; ++i) {
        maze[0][i] = maze[EXIT_ROW + 1][i] = 1;
    }
    
    // 미로 내부 생성
    for (int i = 1; i <= EXIT_ROW; ++i) {
        for (int j = 1; j <= EXIT_COL; ++j) {
            maze[i][j] = dis(gen);
        }
    }
    
    // 미로 출력
    cout << "\n#define EXIT_ROW " << EXIT_ROW << '\n';
    cout << "#define EXIT_COL " << EXIT_COL << '\n';
    cout << "int mark[EXIT_ROW + 2][EXIT_COL + 2];\n";
    cout << "int maze[EXIT_ROW + 2][EXIT_COL + 2] = {\n";
    for (int i = 0; i <= EXIT_ROW + 1; ++i) {
        cout << "\t{";
        for (int j = 0; j <= EXIT_COL + 1; ++j) {
            cout << maze[i][j];
            if (j != EXIT_COL + 1)
                cout << ",";
        }
        cout << "},";
        cout << endl;
    }
    cout << "};";
    
    return 0;
}
