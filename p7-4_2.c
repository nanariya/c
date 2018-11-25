#include <stdio.h>
#include <stdlib.h>

// charのHとLで2桁分使う省メモリ版プログラム

void addDigit2Array(char *arr, int index, char d)
{
    //char 1byte = 8bit ?
    char offset = sizeof(char) * 8 / 2;
    
    char bOdd = index % 2;
    if(bOdd == 1)
    {
        arr[index / 2] &= ~0x0F;
        arr[index / 2] |= d;
    }
    else
    {
        arr[index / 2] &= ~0xF0;
        arr[index / 2] |= d << offset;
    }
}

char loadDigitfromArray(char *arr, int index)
{
    //char 1byte = 8bit ?
    char offset = sizeof(char) * 8 / 2;
    
    char bOdd = index % 2;
    if(bOdd == 1)
    {
        return arr[index / 2] & 0x0F;
    }
    else
    {
        return (arr[index / 2] & 0xF0) >> offset;
    }
}

int main(int argc, char* argv[])
{
    int i,j,n;
    int arrChar;
    int up; //桁上りしてるやつ
    
    scanf("%d", &n);
    
    //必要な配列長 charに2文字ずつ
    arrChar = n / 2 + n % 2;
    
    //配列の用意
    char rr[arrChar];
    //0クリア
    for(i = 0; i < n; i++)
    {
        addDigit2Array(rr, i, 0);
    }
    
    
    addDigit2Array(rr, 0, 5);
    
    for(i = 1; i < n; i++)// rr * 5をループ 
    {
        for(j = n - 1; j >= 0; j--)
        {
            up = loadDigitfromArray(rr, j) * 5;
            addDigit2Array(rr, j, up % 10);
            if(j < n - 1)
            {
                addDigit2Array( rr,
                                j + 1,
                                loadDigitfromArray(rr, j + 1) + (up / 10)
                                );
            }
        }
    }
    
    for(i = n; i != 0; i--)
    {
        if(i != n && (n - i) % 50 == 0)
        {
            printf("\n");
        }
        printf("%d", loadDigitfromArray(rr, i - 1));
    }
    printf("\n");
    return 0;
}