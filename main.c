#include <stdio.h>
#include <stdlib.h>

//練習プログラムなのでバッファのチェックはしていない。
int main(int argc, char* argv[])
{
    int i,j;
    int n;
    int up; //桁上りしてるやつ
    
    scanf("%d", &n);
    
    int rr[n];
    for(i = 0; i < n; i++) rr[i] = 0;//0クリア
    
    rr[0] = 5;
    
    for(i = 1; i < n; i++)// rr * 5をループ 
    {
        for(j = n - 1; j >= 0; j--)
        {
            up = rr[j] * 5; //5倍した数字
            rr[j] = up % 10;
            if(j < n - 1)
            {
                rr[j+1] = rr[j+1] + (up / 10);
            }
        }
    }
    
    for(i = n; i != 0; i--)
    {
        if(i != n && (n - i) % 50 == 0)
        {
            printf("\n");
        }
        printf("%d", rr[i-1]);
    }
    printf("\n");
    return 0;
}