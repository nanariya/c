using System;
using System.Linq;
using System.Collections.Generic;

public class Point{
    public int X;
    public int Y;
    
}
public class Hello{
    public static void Main(){
        // 自分の得意な言語で
        // Let's チャレンジ！！

        int[] line = System.Console.ReadLine().Split(' ').Select(i => Int32.Parse(i)).ToArray();
        int L = line[0]+1; //線の長さ
        int n = line[1]; //縦線の数
        int m = line[2]; //横線の数
        
        int[,] map = new int[n, L];
        Point[,] nextmap = new Point[n, L];
        
        for(int i = 0; i < nextmap.GetLength(0); i++)
        {
            for(int j = 0; j < nextmap.GetLength(1); j++)
            {
                nextmap[i, j] = new Point();
            }
        }
        
        for(int i=0; i < m; i++)
        {
            int[] arr = System.Console.ReadLine().Split(' ').Select(moji => Int32.Parse(moji)).ToArray();
            int ax = arr[0]-1;
            int ay = arr[1];
            int bx = ax + 1;
            int by = arr[2];
            
            nextmap[ax, ay].X = bx; 
            nextmap[ax, ay].Y = by;
            
            nextmap[bx, by].X = ax;
            nextmap[bx, by].Y = ay;
            
            map[ax, ay] = 1;
            map[bx, by] = 1;
        }
        /*
        for(int i = 0; i < nextmap.GetLength(1); i++)
        {
            for(int j = 0; j < nextmap.GetLength(0); j++)
            {
                System.Console.Write(nextmap[j, i].X + ":" + nextmap[j,i].Y + " ");
            }
            System.Console.WriteLine("\n");
        }
        */
        Point player = new Point();
        player.X = 0;
        player.Y = L-1;
        
        while(player.Y != 0)
        {
            player.Y--;
            if(map[player.X, player.Y] == 1)
            {
                player = nextmap[player.X, player.Y];
            }
        }
        System.Console.WriteLine(player.X + 1);
    }
}