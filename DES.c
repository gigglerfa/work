#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int IP[64]={
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};
      
int IP_inv[64]={
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};
      
int Key_1[64] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

int Key_2[64] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32};

int E[48] = {
    32, 1, 2, 3, 4, 5, 4, 5,
    6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1};

int Shift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int P[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
	};

int S[8][64] = {
    {
	14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},

    {
	15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},

    {
	10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},

    {
	7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},

    {
	2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},

    {
	12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},

    {
	4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},

    {
	13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    };

char key_list[16][57];

char *permutation(const char *s, const int *list, int list_size) {
	//实现置换运算
	//用于IP，P，E扩展以及密钥置换
    char *result = (char *)malloc(list_size + 1);
    for (int i = 0; i < list_size; i++) {
        result[i] = s[list[i] - 1];
    }
    result[list_size] = '\0';

    return result;
}

char *leftshift(const char *key, int num) {
	//用于左移两半的密钥
    int key_length = strlen(key);
    char *result = (char *)malloc(key_length + 1);
    if (result == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strncpy(result, key + num, key_length - num);
    strncpy(result + (key_length - num), key, num);
    result[key_length] = '\0';

    return result;
}

void get_key(const char *key) {
    char temp_key[57];
    strncpy(temp_key, permutation(key, Key_1, 64), 56);
    temp_key[56] = '\0';

    char key_left[29];
    strncpy(key_left, temp_key, 28);
    key_left[28] = '\0';

    char key_right[29];
    strncpy(key_right, temp_key + 28, 28);
    key_right[28] = '\0';

    for (int i = 0; i < 16; i++) {
        strncpy(key_left, leftshift(key_left, Shift[i]), 28);
        strncpy(key_right, leftshift(key_right, Shift[i]), 28);

        char combined_key[57];//左右合并 
        strncpy(combined_key, key_left, 28);
        strncpy(combined_key + 28, key_right, 28);
        combined_key[56] = '\0';

        strncpy(key_list[i], permutation(combined_key, Key_2, 56), 56);
        key_list[i][56] = '\0';
    }
}

char *xor(const char *bits, const char *ki) {
	//实现异或运算
    int len = strlen(bits);
    char *result = (char *)malloc(len + 1);

    for (int i = 0; i < len; i++) {
        result[i] = (char)(((bits[i] - '0') ^ (ki[i] - '0')) + '0');
    }
    result[len] = '\0';

    return result;
}

char *s(const char *bits, int i) {
	//拼接获得行和列 
    int row = (bits[0] - '0') * 2 + (bits[5] - '0');
    int col = (bits[1] - '0') * 8 + (bits[2] - '0') * 4 + (bits[3] - '0') * 2 + (bits[4] - '0');
    int num = S[i - 1][row * 16 + col];

    char *result = (char *)malloc(5);
    snprintf(result, 5, "%04d", num);
    return result;
}

char *s_change(const char *bits) {
	//经过S盒变换，由48bit变回32bit 
    char *result = (char *)malloc(33);
    result[0] = '\0';

    for (int i = 0; i < 8; i++) {
        char *temp_result = s(bits + i * 6, i + 1);
        strncat(result, temp_result, 4);
        free(temp_result);
    }
    result[32] = '\0';

    return result;
}

char *F(const char *bits, const char *ki) {
    char *expanded_bits = permutation(bits, E, 48);//E扩展 
    char *xor_result = xor(expanded_bits, ki);//异或操作 
    free(expanded_bits);

    char *s_change_result = s_change(xor_result);//S盒变换 
    free(xor_result);

    char *result = permutation(s_change_result, P, 32);//P置换 
    free(s_change_result);

    return result;
}

char *des(const char *bits, const char *key) {
    char *ip_result = permutation(bits, IP, 64);

    char L[33];
    strncpy(L, ip_result, 32);
    L[32] = '\0';

    char R[33];
    strncpy(R, ip_result + 32, 32);
    R[32] = '\0';
    free(ip_result);

    get_key(key);

    for (int i = 0; i < 16; i++) {
        char *L_next = strdup(R);//复制R到下一个L 

        char *F_result = F(R, key_list[i]);
        char *xor_result = xor(L, F_result);
        strncpy(R, xor_result, 32);
        R[32] = '\0';
        free(F_result);
        free(xor_result);

        strncpy(L, L_next, 32);
        L[32] = '\0';
        free(L_next);
    }

    char *RL = (char *)malloc(65);
    strncpy(RL, R, 32);
    strncpy(RL + 32, L, 32);
    RL[64] = '\0';

    char *result = permutation(RL, IP_inv, 64);
    free(RL);

    return result;
}

void hexToBin(char hex[17],char bin[65])
{
    for (int i=0; i < 16; i++){
    	switch (hex[i])
		{
		    case '0': strcat(bin, "0000"); break;
		    case '1': strcat(bin, "0001"); break;
		    case '2': strcat(bin, "0010"); break;
		    case '3': strcat(bin, "0011"); break;
		    case '4': strcat(bin, "0100"); break;
		    case '5': strcat(bin, "0101"); break;
		    case '6': strcat(bin, "0110"); break;
		    case '7': strcat(bin, "0111"); break;
		    case '8': strcat(bin, "1000"); break;
		    case '9': strcat(bin, "1001"); break;
		    case 'a':
		    case 'A': strcat(bin, "1010"); break;
		    case 'b':
		    case 'B': strcat(bin, "1011"); break;
		    case 'c':
		    case 'C': strcat(bin, "1100"); break;
		    case 'd':
		    case 'D': strcat(bin, "1101"); break;
		    case 'e':
		    case 'E': strcat(bin, "1110"); break;
		    case 'f':
		    case 'F': strcat(bin, "1111"); break;
		}
	}
    strncpy(bin,bin+1,64);
    bin[64]='\0';
}

int main() {
    int T;
    scanf("%d", &T);

    char s_hex[19];
    char k_hex[19];
    scanf("%s", s_hex);
    scanf("%s", k_hex);

    char s[65];
    char k[65];
    hexToBin(s_hex + 2, s);
    hexToBin(k_hex + 2, k);

    for (int i = 0; i < T; i++) {
        char *result = des(s, k);
        strncpy(s, result, 64);
        s[64] = '\0';
        free(result);
    }

    printf("Final result: %s\n", s);
    return 0;
}

