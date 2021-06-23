package com.example.centerapp.record;

public class Log {

    static public void debug(Object... objs){
        String str = "";
        for (int i = 0; i < objs.length; i++) {
            if(i == (objs.length - 1))
                System.out.print(objs[i]);
            else
                System.out.print(objs[i].toString()+", ");
        }
        System.out.print("\n");

    }
}
