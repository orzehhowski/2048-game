//2048 game by orzehhowski


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>


void red() {
	printf("\033[0;31m");
}

void green() {
	printf("\033[0;32m");
}

void yellow() {
	printf("\033[0;33m");
}

void blue() {
	printf("\033[0;34m");
}

void purple() {
	printf("\033[0;35m");
}

void cyan() {
	printf("\033[0;36m");
}

void reset() {
	printf("\033[0m");
}

void printing_field(int nums[4][4]) {
	int i, j;
	system("cls");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (nums[i][j] == 2) 
				yellow();
			if (nums[i][j] == 4)
				green();
			if (nums[i][j] == 8)
				cyan();
			if (nums[i][j] == 16)
				blue();
			if (nums[i][j] == 32)
				purple();
			if (nums[i][j] == 64)
				red();
			if (nums[i][j] == 128)
				yellow();
			if (nums[i][j] == 256)
				green();
			if (nums[i][j] == 512)
				cyan();
			if (nums[i][j] == 1024)
				blue();
			if (nums[i][j] == 2048)
				red();
			printf("%5d", nums[i][j]);
			reset();
		}
		printf("\n\n");
	}
}

void add_rand_num(int nums[4][4]) {
	int rand_x, rand_y;

	do {
		rand_x = rand() % 4;
		rand_y = rand() % 4;
	} while (nums[rand_x][rand_y] != 0);

	printing_field(nums);
	Sleep(150);
	int two_or_four = rand() % 5;
	if (two_or_four)				//20% szans na 4, 80% na 2
		nums[rand_x][rand_y] = 2;
	else nums[rand_x][rand_y] = 4;
}

void copy_nums(int nums[4][4], int aux[4][4]) {
	int row, col;
	for (row = 0; row < 4; row++)
		for (col = 0; col < 4; col++)
			aux[row][col] = nums[row][col];
}

bool was_move(int before[4][4], int nums[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (nums[i][j] != before[i][j])
				return 1;
	return 0;
}

int move_up(int nums[4][4], int result) {
	int row, row_b, col, aux[4][4], before[4][4];
	int i;
	copy_nums(nums, aux);
	copy_nums(nums, before);

	for (col = 0; col < 4; col++) {				//dla kazdej kolumny osobno
		for (row = 0; row < 3; row++) {
			for (row_b = row + 1; row_b < 4; row_b++) {
				if ((aux[row][col] == aux[row_b][col]) && (aux[row][col] != 0)) {
					if (((row + 1 < row_b) && (aux[row + 1][col] != 0)) || ((row + 2 < row_b) && (aux[row + 2][col] != 0)))
						break;
					nums[row][col] <<= 1;
					result += nums[row][col];
					nums[row_b][col] = 0;
					copy_nums(nums, aux);
					break;
				} 
			}
		}
		for (i = 0; i < 4; i++) {
			for (row = 1; row < 4; row++) {
				if ((aux[row - 1][col] == 0) && (aux[row][col] != 0)) {
					nums[row - 1][col] = aux[row][col];
					nums[row][col] = 0;
				}
			}
			copy_nums(nums, aux);
		}
	}
	if (was_move(before, nums))
		add_rand_num(nums);
	return result;
}

int move_down(int nums[4][4], int result) {
	int row, row_b, col, aux[4][4], before[4][4];
	int i;
	copy_nums(nums, aux);
	copy_nums(nums, before);

	for (col = 0; col < 4; col++) {				//dla kazdej kolumny osobno
		for (row = 3; row > 0; row--) {
			for (row_b = row - 1; row_b >= 0; row_b--) {
				if ((aux[row][col] == aux[row_b][col]) && (aux[row][col] != 0)) {
					if (((row - 1 > row_b) && (aux[row - 1][col] != 0)) || ((row - 2 > row_b) && (aux[row - 2][col] != 0)))
						break;
					nums[row][col] <<= 1;
					result += nums[row][col];
					nums[row_b][col] = 0;
					copy_nums(nums, aux);
					break;
				}
			}
		}
		for (i = 0; i < 3; i++) {
			for (row = 2; row >= 0; row--) {
				if ((aux[row + 1][col] == 0) && (aux[row][col] != 0)) {
					nums[row + 1][col] = aux[row][col];
					nums[row][col] = 0;
				}
			}
			copy_nums(nums, aux);
		}
	}
	if (was_move(before, nums))
		add_rand_num(nums);
	return result;
}

int move_right(int nums[4][4], int result) {
	int row, col_b, col, aux[4][4], before[4][4];
	int i;
	copy_nums(nums, aux);
	copy_nums(nums, before);

	for (row = 0; row < 4; row++) {
		for (col = 3; col > 0; col--) {
			for (col_b = col - 1; col_b >= 0; col_b--) {
				if ((aux[row][col] == aux[row][col_b]) && (aux[row][col] != 0)) {
					if (((col - 1 > col_b) && (aux[row][col - 1] != 0)) || ((col - 2 > col_b) && (aux[row][col - 2] != 0)))
						break;
					nums[row][col] <<= 1;
					result += nums[row][col];
					nums[row][col_b] = 0;
					copy_nums(nums, aux);
					break;
				}
			}
		}
		for (i = 0; i < 3; i++) {
			for (col = 2; col >= 0; col--) {
				if ((aux[row][col + 1] == 0) && (aux[row][col] != 0)) {
					nums[row][col + 1] = aux[row][col];
					nums[row][col] = 0;
				}
			}
			copy_nums(nums, aux);
		}
	}
	if (was_move(before, nums))
		add_rand_num(nums);
	return result;
}

int move_left(int nums[4][4], int result) {
	int row, col_b, col, aux[4][4], before[4][4];
	int i;
	copy_nums(nums, aux);
	copy_nums(nums, before);

	for (row = 0; row < 4; row++) {		
		for (col = 0; col < 3; col++) {
			for (col_b = col + 1; col_b < 4; col_b++) {
				if ((aux[row][col] == aux[row][col_b]) && (aux[row][col] != 0)) {
					if (((col + 1 < col_b) && (aux[row][col + 1] != 0)) || ((col + 2 < col_b) && (aux[row][col + 2] != 0)))
						break;
					nums[row][col] <<= 1;
					result += nums[row][col];
					nums[row][col_b] = 0;
					copy_nums(nums, aux);
					break;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			for (col = 1; col < 4; col++) {
				if ((aux[row][col - 1] == 0) && (aux[row][col] != 0)) {
					nums[row][col - 1] = aux[row][col];
					nums[row][col] = 0;
				}
			}
			copy_nums(nums, aux);
		}
	}
	if (was_move(before, nums))
		add_rand_num(nums);
	return result;
}

bool can_move(int nums[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (nums[i][j] == 0)
				return 1;

    //sprawdzanie elementow srodkowych
	for (i = 1; i < 3; i++) {
		for (j = 1; j < 3; j++) {
			if ((nums[i][j] == nums[i][j + 1]) || (nums[i][j] == nums[i][j - 1]) || (nums[i][j] == nums[i + 1][j]) || 
				(nums[i][j] == nums[i - 1][j]))
				return 1;
		}
	}

    //sprawdzanie elementow skrajnych
	for (i = 0; i < 3; i++) {
		if ((nums[i][0] == nums[i + 1][0]))
			return 1;
		if ((nums[i][3] == nums[i + 1][3]))
			return 1;
		if ((nums[0][i] == nums[0][i + 1]))
			return 1;
		if ((nums[3][i] == nums[3][i + 1]))
			return 1;
	}
	return 0;
}

int new_game(int nums[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			nums[i][j] = 0;
    add_rand_num(nums);
	return 0;
}

bool is_it_win(int nums[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (nums[i][j] == 2048)
				return 1;
	return 0;
}

int main() {
	srand(time(NULL));
	int record, breaker = 1, result = 0;
	int result_before = 0;
	char c;
	int nums_before[4][4];
	int nums[4][4] = {	{0, 0, 0, 0},
						{0, 0, 0, 0},
						{0, 0, 0, 0},
						{0, 0, 0, 0}  };
	FILE* record_file_in;
	FILE* record_file_out;
	record_file_in = fopen("record.txt", "r");
	fscanf(record_file_in, "%d", &record);
	fclose(record_file_in);

	add_rand_num(nums);
	printing_field(nums);
	printf("\n\nscore: %d\n", result);
	printf("record: %d\n", record);
	printf("WASD - moving\nQ - new game\nE - move back\nR - exit\n");
	while (breaker) {
		if (! is_it_win(nums)) {
			if (can_move(nums)) {
				c = _getch();
				switch (c) {
				case 'w':
					copy_nums(nums, nums_before);
					result_before = result;
					result = move_up(nums, result);
					break;
				case 's':
					copy_nums(nums, nums_before);
					result_before = result;
					result = move_down(nums, result);
					break;
				case 'd':
					copy_nums(nums, nums_before);
					result_before = result;
					result = move_right(nums, result);
					break;
				case 'a':
					copy_nums(nums, nums_before);
					result_before = result;
					result = move_left(nums, result);
					break;
				case 'e':
					copy_nums(nums_before, nums);
					result = result_before;
					break;
				case 'q':
					copy_nums(nums, nums_before);
					result_before = result;
					result = new_game(nums);
					break;
				case 'r':
					breaker = 0;
					break;
				default:
					break;
				}
				if (result > record)
					record = result;
				printing_field(nums); 
				printf("\n\nscore: %d\n", result);
				printf("record: %d\n", record);
				printf("WASD - moving\nQ - new game\nE - move back\nR - exit\n");
			}
			else {
				printing_field(nums);
				printf("\n\nyou lost!!");
				printf("\nscore: %d\n", result);
				printf("record: %d\n", record);
				printf("\nQ - new game\nE - move back\nR - exit\n");
				c = _getch();
				switch (c) {
				case 'e':
					copy_nums(nums_before, nums);
					result = result_before;
					break;
				case 'q':
					copy_nums(nums_before, nums);
					result = new_game(nums);
					break;
				case 'r':
					breaker = 0;
					break;
				default:
					break;
				}
				if (result > record)
					record = result;
				printing_field(nums);
				printf("\n\nscore: %d\n", result);
				printf("record: %d\n", record);
				printf("WASD - moving\nQ - new game\nE - move back\nR - exit\n");
			}
		}
		else {
			printing_field(nums);
			printf("\n\n you are the winner!!!");
			printf("\n\nscore: %d\n", result);
			printf("record: %d\n", record);
			printf("Q - new game\nR - exit\n");
			c = _getch();
			switch (c) {
			case 'q':
				copy_nums(nums_before, nums);
				result = new_game(nums);
				break;
			case 'r':
				breaker = 0;
				break;
			default:
				break;
			}
		}
	}
	record_file_out = fopen("record.txt", "w");
	fprintf(record_file_out, "%d", record);
	fclose(record_file_out);
    return 0;
}