#include <iostream>
#include <cstdio>
using namespace std;

///<summary>
///This function prints the introduction
///</summary>
void introduction() {
	cout << "In this program, I will give you the sum and subtraction of 2 big numbers that no numeric datatype could able to store." << endl;
	cout << "When you enter each input, the program will automatically delete non_numeric characters that you have entered." << endl;
	cout << "For example: \"-123 89A/219.21,1878-0192*as265\" is equal to the number of 123892192118780192265" << endl;
	cout << "First number is called, 'A' and the second one is called, 'B'" << endl;
}

void takeInput(int X[], int& len) {
	char character;
	cout << "Please enter your number: ";
	do {
		character = getchar();
		if (character >= '0' && character <= '9') {
			X[len] = int(character - '0');
			len++;
		}
	} while (character != '\n');
}

void insertZeros(int X[], int& lenX, int diff) {
	for (int i = lenX - 1; i >= 0; i--) {
		X[i + diff] = X[i];
	}
	for (int i = 0; i < diff; i++) {
		X[i] = 0;
	}
	lenX += diff;
}

void addZeroBeforeSmallerNumber(int X[], int Y[], int& len_x, int& len_y) {
	if (len_x < len_y) {
		insertZeros(X, len_x, len_y - len_x + 1);
		insertZeros(Y, len_y, 1);
	}

	else if (len_x > len_y) {
		insertZeros(Y, len_y, len_x - len_y + 1);
		insertZeros(X, len_x, 1);
	}
	else {
		insertZeros(X, len_x, 1);
		insertZeros(Y, len_y, 1);
	}
}

///<summary>
///This function finds the larger number
/// <para>determind whether X is bigger than Y, return 1. 
/// if X is smaller, return -1.
/// otherwise, return 0
/// </para>
///</summary>
int findBiggerNumber(int X[], int Y[], int len) {
	for (int i = 0; i < len; i++) {
		if (X[i] == Y[i]) continue;
		if (X[i] > Y[i]) return 1; //when X is bigger than Y, return 1
		else return -1; //when X is smaller, return -1
	}
	return 0;
}

void reverseNumber(int X[], int len) {
	int temp;
	for (int i = 0; i < len / 2; i++) {
		temp = X[i];
		X[i] = X[len - 1 - i];
		X[len - 1 - i] = temp;
	}
}

///<summary>
///This function calculates the sum of 2 numbers
///</summary>
void addBigNumber(int X[], int Y[], int& len, int result[]) {
	int carry = 0;
	char temp;
	for (int i = 0; i < len; i++) {
		temp = carry + X[i] + Y[i];
		if (temp >= 10) {
			carry = 1;
			result[i] = temp - 10;
		}
		else if (temp >= 0 && temp < 10) {
			carry = 0;
			result[i] = temp;
		}
	}
}

///<summary>
///This function prints the sum of 2 numbers
///</summary>
void processAndPrintSumOfBigNumbers(int X[], int Y[], int len) {
	int sumResult[50];
	addBigNumber(X, Y, len, sumResult);
	for (int i = len - 1; i >= 0; i--) {
		if (sumResult[i] == 0 && i == len - 1) continue;
		else cout << sumResult[i];
	}
	cout << endl;
}

///<summary>
///This function calculates X minus Y (X - Y)
///</summary>
void subtractBigNumber(int X[], int Y[], int& len, int result[]) {
	int carry = 0;
	int temp;
	int final_temp_position = 0;
	for (int i = 0; i < len; i++) {
		temp = carry + Y[i];
		if (X[i] < temp) {
			result[i] = X[i] - temp + 10;
			carry = 1;
		}
		else {
			result[i] = X[i] - temp;
			carry = 0;
		}
		if (result[i] != 0) final_temp_position = i + 1;
	}
	len = final_temp_position;
}

///<summary>
///This function prints the subtraction of 2 numbers
///</summary>
void processAndPrintSubtractionOfBigNumbers(int X[], int Y[], int len, int flag) {
	int subtractResult[50];
	if (flag == 1) {//x > y
		subtractBigNumber(X, Y, len, subtractResult);
		for (int i = len - 1; i >= 0; i--) {
			if (subtractResult[i] == 0 && i == 0) continue;
			else cout << subtractResult[i];
		}
		cout << endl;
	}
	else if (flag == -1) {//x < y
		subtractBigNumber(Y, X, len, subtractResult);
		cout << '-';
		for (int i = len - 1; i >= 0; i--) {
			if (subtractResult[i] == 0 && i == 0) continue;
			else cout << subtractResult[i];
		}
		cout << endl;
	}
	else if (flag == 0) cout << 0 << endl;
}

///<summary>
///This function takes input of 2 numbers, processes them and determinds which one is the larger number
/// <para>determind whether X is bigger than Y, return 1. 
/// if X is smaller, return -1.
/// otherwise, return 0
/// </para>
///</summary>
int numberProcess(int X[], int Y[], int& len_x, int& len_y) {
	takeInput(X, len_x);
	takeInput(Y, len_y);
	addZeroBeforeSmallerNumber(X, Y, len_x, len_y);
	int determind_bigger_number_whether_X_or_Y = findBiggerNumber(X, Y, len_x);
	reverseNumber(X, len_x);
	reverseNumber(Y, len_y);
	return determind_bigger_number_whether_X_or_Y;
}

/// <summary>
/// This function acts like an ALU
/// </summary>
/// <returns></returns>
void controller(int A[], int B[], int len_A, int determind_bigger_number_whether_X_or_Y) {
	cout << "Which one you want me to do? Enter a valid number in the below list:" << endl;
	cout << "1. A+B" << endl;
	cout << "2. A-B" << endl;
	cout << "3. B-A" << endl;

	int decision;
	do {
		cin >> decision;
	} while (decision < 1 && decision > 3);

	if (decision == 1) processAndPrintSumOfBigNumbers(A, B, len_A);
	else if (decision == 2) processAndPrintSubtractionOfBigNumbers(A, B, len_A, determind_bigger_number_whether_X_or_Y);
	else if (decision == 3) processAndPrintSubtractionOfBigNumbers(B, A, len_A, -determind_bigger_number_whether_X_or_Y);
}


int main() {
	introduction();
	int A[50], B[50];
	int len_A = 0, len_B = 0; //number of digit in each big number
	int determind_bigger_number_whether_X_or_Y = numberProcess(A, B, len_A, len_B);

	controller(A, B, len_A, determind_bigger_number_whether_X_or_Y);
	
	return 0;
}