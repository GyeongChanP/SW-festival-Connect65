// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI �ڵ� �ۼ� ���]

1. char info[]�� �迭 �ȿ�					"TeamName:�ڽ��� ����,Department:�ڽ��� �Ҽ�"					������ �ۼ��մϴ�.
( ���� ) Teamname:�� Department:�� �� ���� �մϴ�.
"�ڽ��� ����", "�ڽ��� �Ҽ�"�� �����ؾ� �մϴ�.

2. �Ʒ��� myturn() �Լ� �ȿ� �ڽŸ��� AI �ڵ带 �ۼ��մϴ�.


[���� �� �Լ�]
myturn(int cnt) : �ڽ��� AI �ڵ带 �ۼ��ϴ� ���� �Լ� �Դϴ�.
int cnt (myturn()�Լ��� �Ķ����) : ���� �� �� �־��ϴ��� ���ϴ� ����, cnt�� 1�̸� ���� ���� ��  �� ����  �δ� ��Ȳ(�� ��), cnt�� 2�̸� �� ���� ���� �δ� ��Ȳ(�� ��)
int  x[0], y[0] : �ڽ��� �� ù �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
int  x[1], y[1] : �ڽ��� �� �� �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.


//int board[BOARD_SIZE][BOARD_SIZE]; �ٵ��� �����Ȳ ��� �־� �ٷλ�� ������. ��, ���������ͷ� ���� �������
// ������ ���� ��ġ�� �ٵϵ��� ������ �ǰ��� ó��.

boolean ifFree(int x, int y) : ���� [x,y]��ǥ�� �ٵϵ��� �ִ��� Ȯ���ϴ� �Լ� (������ true, ������ false)
int showBoard(int x, nt y) : [x, y] ��ǥ�� ���� ���� �����ϴ��� �����ִ� �Լ� (1 = �ڽ��� ��, 2 = ����� ��)

*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
int isFree(int, int);
void mymove(int x[], int y[], int);
int showBoard(int, int);
int isInside(int x, int y);
// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:DUST,Department:Handong University" };
int board[20][20], height = 19, width = 19;
//��� ����
#define MAXXY 19
//1�� ��Ŀ� ���� �¿��Ī�̸� 1�� n���� n/2�� ��Ī �ƴϸ� n�� ������ �ȴ�.
const char pattern[80][12] = {//0�� �ƹ��ų� ��� ����, 1�� ����, 2�� ��뵹, 3�� ���, �̹����� 6��°ĭ�� �ڱⰡ ���� ��ġ
	"00000111111","00001111110","00011111100",//6
	"00003111113","00031111130","00311111300",//5 ���̺�ĭ 0
	"00000131111","00001311110","00131111000","01311110000","13111100000",//5 ���̺�ĭ 1
	"00000113111","00001131110","00113111000","01131110000","11311100000",
	"00003111112","00031111120","00311111200","03111112000","31111120000",
	"00033111133","00331111330",//4 ���̺�ĭ 0
	"00003111133","00031111330","00311113300","03111133000",
	"00002111133","00021111330","00211113300","02111133000",
	"00003111313","00031113130","00311131300","31113130000",//4 ���̺�ĭ 1  --3131113 �� �ʿ� x
	"00003111312","00031113120","00311131200","31113120000",
	"00002111313","00021113130","00211131300","21113130000",
	"00003113113","00031131130",
	"00002113113","00021131130","02113113000","21131130000",
	"00000131131","00013113100",//4 ���̺�ĭ 2
	"00000113311","00001133110",
	"00000133111","00133111000","01331110000","13311100000",
	"00000131311","00013131100","01313110000","13131100000",
	"00033111330","00331113300",//3 ���̺�ĭ 0  ==>3���� ��뵹 ���� ���� 
	"00003111330","00003111330","00311133000",
	"00003131130","00313113000","03131130000",//3 ���̺�ĭ 1
	"00003131313","00313131300",//3 ���̺�ĭ 2
	"00333113330",//2 ���̺�ĭ 0
	"00033113330","00331133300",
	"00003113330","00031133300",
	"00033113300",
	"00033131330",//2 ���̺�ĭ 1
	//"00003131333","00313133300",
	"00003131330","00313133000",


};

const int stoneNum[80] = {
	6,6,6,
	5,5,5,
	5,5,5,5,5,
	5,5,5,5,5,
	5,5,5,5,5,
	4,4,
	4,4,4,4,
	4,4,4,4,
	4,4,4,4,
	4,4,4,4,
	4,4,4,4,
	4,4,
	4,4,4,4,
	4,4,
	4,4,
	4,4,4,4,
	4,4,4,4,
	3,3,
	3,3,3,
	3,3,3,
	3,3,
	2,
	2,2,
	2,2,
	2,
	2,
	2,2//������� 80��
};

const bool connected[80] = {
	true, true, true,
	true, true, true,
	false, false, false, false, false,
	false, false, false, false, false,
	false, false, false, false, false,
	true, true,
	true, true, true, true,
	true, true, true, true,
	false, false, false, false,
	false, false, false, false,
	false, false, false, false,
	false, false,
	false, false, false, false,
	false, false,
	false, false,
	false, false, false, false,
	false, false, false, false,
	true, true,
	true, true, true,
	false, false, false,
	false, false,
	true,
	true, true,
	true, true,
	true,
	false,
	false, false
};
/*
const int category[]={

};
*/
const int score1[81] = {//ù ��° �� �� ����ġ
	2100,2100,2100,
	1000,1000,1000,
	1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,
	110,110,
	109,109,109,109,
	106,106,106,106,
	108,108,108,108,
	105,105,105,105,
	105,105,105,105,
	107,107,
	105,105,105,105,
	103,103,
	103,103,
	104,104,104,104,
	103,103,103,103,
	54,54,
	52,52,52,
	51,51,51,
	53,53,
	24,
	23,23,
	21,21,
	22,
	20,
	20,20,
	0
};
const int score2[81] = {//�� ��° �� �� ����ġ
	1000,1000,1000,
	19,19,19,
	19,19,19,19,19,
	19,19,19,19,19,
	19,19,19,19,19,
	110,110,
	109,109,109,109,
	106,106,106,106,
	108,108,108,108,
	105,105,105,105,
	105,105,105,105,
	107,107,
	105,105,105,105,
	103,103,
	103,103,
	104,104,104,104,
	103,103,103,103,
	54,54,
	52,52,52,
	51,51,51,
	53,53,
	24,
	23,23,
	21,21,
	22,
	20,
	20,20,
	0
};
const int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };//��, ���, ��, ����, ��, ����, ��, �»�

int findpattern(int user, int d, int xpos, int ypos) {
	int curuser = user == 1 ? 2 : 1;//������
	int ptidx, idx;
	char cur;
	int cur2;
	bool check;
	for (ptidx = 0; ptidx < 80; ++ptidx) {
		check = true;
		for (idx = -5; idx < 6; ++idx) {//���� 11ĭ �� Ȯ��
			cur = pattern[ptidx][idx + 5];
			if (idx == 0 || cur == '0')//0�϶��� �� �ʿ䰡 ����.(idx: ���� ���� �ڸ��ϱ�, cur:�����̵� ��� �����ϱ�)
				continue;
			cur2 = (cur == '1' ? user : (cur == '2' ? curuser : 0));//��� �� Ȯ�� �� ���� user�� �̴ϱ� ���� 2���� �ƴ��� Ȯ��
			if ( !isInside(xpos + dx[d] * idx, ypos + dy[d] * idx) || showBoard(xpos + dx[d] * idx, ypos + dy[d] * idx) != cur2) {
				check = false; // �����̶� ��ġ ���ϰų� �ٵ��� ����� false
				break;
			}
		}
		if (check) {
			return ptidx;//���ϰ� ��ġ�ϸ� � �������� ��ȯ(���� ��ġ�� �ϳ��ۿ� ����)(����ġ�� ���� ���� ��ȯ�ϳ�?)
		}
	}
	return -1;
}
void myturn(int cnt) {

	int x[2], y[2];


	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

	srand((unsigned)time(NULL));
	/*
	for (int i = 0; i < cnt; i++) {
	do {
	x[i] = rand() % width;
	y[i] = rand() % height;
	if (terminateAI) return;
	} while (!isFree(x[i], y[i]));

	if (x[1] == x[0] && y[1] == y[0]) i--;
	}
	*/
	for (int i = 0; i < cnt; i++) {
		int iy, ix;
		int patt[8];
		int mybesty = 0, mybestx = 0;
		int mybestRank = 11, mybestscore = 0;

		int opbesty = 0, opbestx = 0;
		int opbestRank = 11, opbestscore = 0;

		int idx, d;
		int p1, p2;
		int rank, score;
		bool fourCheck, threeCheck;
		if (cnt == 1) {
			x[0] = 9;
			y[0] = 9;
		}
		else {
			for (iy = 0; iy < height; iy++) {//�� �� ���� Ȯ��
				for (ix = 0; ix < width; ix++) {
					if (isFree(ix, iy)) {
						rank = 11;
						score = 0;
						fourCheck = false;
						threeCheck = false;
						for (d = 0; d < 8; d++)
							patt[d] = findpattern(1, d, ix, iy);
						for (d = 0; d < 4; d++) {//ī�װ��� ���� ���� 33, 44 �� Ȯ��
							p1 = patt[d];//������
							p2 = patt[d + 4];//������
						}
						for (d = 0; d < 4; d++) {
							p1 = patt[d];
							p2 = patt[d + 4];
							if (p1 != -1 && p2 != -1) {
								if (i == 0) {
									score += score1[p1] > score1[p2] ? score1[p1] : score1[p2];
								}
								else {
									score += score2[p1] > score2[p2] ? score2[p1] : score2[p2];
								}
							}
							else if (p1 != -1 && p2 == -1) {
								if (i == 0) {
									score += score1[p1];
								}
								else {
									score += score2[p1];
								}
							}
							else if (p1 == -1 && p2 != -1) {
								if (i == 0) {
									score += score1[p2];
								}
								else {
									score += score2[p2];
								}
							}

						}
						if (mybestscore < score) {
							mybestscore = score;
							mybesty = iy;
							mybestx = ix;
						}
					}
				}
			}

			for (iy = 0; iy < height; iy++) {//��� �� ���� Ȯ��
				for (ix = 0; ix < width; ix++) {
					if (isFree(ix, iy)) {
						rank = 11;
						score = 0;
						fourCheck = false;
						threeCheck = false;
						for (d = 0; d < 8; d++)
							patt[d] = findpattern(2, d, ix, iy);
						for (d = 0; d < 4; d++) {//ī�װ��� ���� ���� 33, 44 �� Ȯ��
							p1 = patt[d];//������
							p2 = patt[d + 4];//������
						}
						for (d = 0; d < 4; d++) {
							p1 = patt[d];
							p2 = patt[d + 4];
							if (p1 != -1 && p2 != -1) {
								score += score1[p1] > score1[p2] ? score1[p1] : score1[p2];
							}
							else if (p1 != -1 && p2 == -1) {
								score += score1[p1];
							}
							else if (p1 == -1 && p2 != -1) {
								score += score1[p2];
							}
						}
						if (opbestscore < score) {
							opbestscore = score;
							opbesty = iy;
							opbestx = ix;
						}
					}
				}
			}
			//�Ѱ�
			if (mybestscore > opbestscore) {
				x[i] = mybestx;
				y[i] = mybesty;
			}
			else {
				x[i] = opbestx;
				y[i] = opbesty;
			}
			printf("score : %d %d", mybestscore, opbestscore);

		}
		if (i == 0)
			board[x[0]][y[0]] = 1;
	}
	board[x[0]][y[0]] = 0;
	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	mymove(x, y, cnt);
	int a, b;
	for (int j = 0; j < 2; ++j) {
		printf("send :  ");
		scanf("%d %d", &a, &b);
		board[a][b] = 2;
	}
	printf("\n");
}
void mymove(int x[], int y[], int cnt) {
	for (int i = 0; i < cnt; i++) {
		if (isFree(x[i], y[i])) {
			board[x[i]][y[i]] = 1;
		}
	}
	printf("my turn :%d, %d  %d, %d\n", x[0], y[0], x[1], y[1]);
}

int isFree(int x, int y)
{
	return x >= 0 && y >= 0 && x < width && y < height && board[x][y] == 0;
}
int isInside(int x, int y)
{
	return x >= 0 && y >= 0 && x < width && y < height;
}

int showBoard(int x, int y) {
	return board[x][y];
}

int main() {
	printf("p1: %d , p2: %d\n", score1[0], score1[7]);
	myturn(1);
	while (1) {
		myturn(2);
	}
	return 0;
}