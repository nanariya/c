#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

//練習プログラムなのでバッファのチェックはしていない。
int main(int argc, char* argv[])
{
    uintmax_t x;
    
    //受け取れる最大値を受け取るように
    //おそらく 18446744073709551615
    scanf("%ju", &x);
    
    //1バイトが何bitか計算（ucharの最大値で2log→charのサイズで割る）　このプラットフォームではおそらく8
    uintmax_t bit_width_of_byte = (uintmax_t)log2(UCHAR_MAX+1) / sizeof(char);
    
    //bitとint型の乗算。8bit x 8byte = 64bit?
    uintmax_t bit_multi_byte = bit_width_of_byte * sizeof(intmax_t);
    

    //動的メモリ確保ポインタ
    intptr_t *arr_ptr;
    
    //動的メモリ確保の為にとりあえずuintmax_tサイズ毎でcalloc　多分メモリアロケーションもその幅かもしれない
    //あまりがあったら1を足すようにしたい。
    uintmax_t r = x % bit_multi_byte;
    if( r > 0 ) r = 1;

    //intmax_tサイズで割って、余りがあったら+1の長さで確保
    arr_ptr = (intptr_t *)calloc( x / bit_multi_byte + r , sizeof(uintmax_t)); 
    
    if ( !arr_ptr ) {
        fprintf(stderr, "メモリが確保できなかった…\n");
        return -1;
    }
    
    //----
    // メイン処理
    //----
    
    //探す素数の最大値
    double sq_x = sqrt(x);
    
    uintmax_t prime_index,i;

    prime_index = 2; //素数探索は2から始める
    *(arr_ptr) |= (1ul << 0);//1は素数じゃない
    
    uintmax_t byte_offset; //64bit事のoffset
    uintmax_t byte_index; //8byte(64bit)の中でのindex
    
    while(prime_index < sq_x)
    {
        i = prime_index;
        
        //素数を篩で落とす処理
        while(i <= x)
        {
            if(i != prime_index)
            {
                //オフセットとインデックスを計算
                byte_offset = (i - 1) / bit_multi_byte;
                byte_index = (i - 1) % bit_multi_byte;

                *(arr_ptr + byte_offset) |= (1ul << byte_index); //素数じゃないフラグを立てる
            }
            i += prime_index; //倍数にする
        }

        //次の素数を探す
        prime_index++;
        byte_offset = (prime_index - 1) / bit_multi_byte;
        byte_index = (prime_index - 1) % bit_multi_byte;

        //素数フラグ立ってる間インクリメント
        while(*(arr_ptr + byte_offset) & (1ul << byte_index))
        {
            prime_index++;
            byte_offset = (prime_index - 1) / bit_multi_byte;
            byte_index = (prime_index - 1) % bit_multi_byte;
        }
    }
    
    //表示部分
    if(x < 100)
    {
        for(i=2; i<x; i++)
        {
            byte_offset = (i - 1) / bit_multi_byte;
            byte_index = (i - 1) % bit_multi_byte;
            if(!(*(arr_ptr + byte_offset) & (1ul << byte_index)))
            {
                printf(" %ld", i);
            }
        }
        printf("\n");
    }
    else
    {
        uintmax_t j = 0, max;
        for(i=2; i<=x; i++)
        {
            byte_offset = (i - 1) / bit_multi_byte;
            byte_index = (i - 1) % bit_multi_byte;
            
            if(!( *(arr_ptr + byte_offset) & (1ul << byte_index) ) )
            {
                j++;
                max = i;
            }
        }
        printf("%jd\n%jd\n", j, max);
    }
    
    //freeにptrを投げると警告が出るのでvoid *へキャスト。これでいいのか不明。
    free((void *)arr_ptr);
    
    return 0;
}
