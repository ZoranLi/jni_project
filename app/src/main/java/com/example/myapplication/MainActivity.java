package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Debug;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private static final int A = 815;

    public String name = "derry";

    public static int age = 29;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv = findViewById(R.id.sample_text);
//        tv.setText(getStringPwd());
        changeName();
        tv.setText(name);
        changeAge();
        tv.setText(String.valueOf(age));
        callAddMethod();

        int[] ints = {1, 2, 3, 4, 5};


        String[] strs = {"aaaa", "bb", "cc"};
        testArrayAction(5, "aaa", ints, strs);

        for (String str : strs) {
            Log.e(getClass().getName(), str);
        }

        for (int item : ints) {
            Log.e(getClass().getName(), Integer.toString(item));
        }
    }
    




    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        Debug.stopMethodTracing();
    }

    /**
     * @param count
     * @param textInfo
     * @param ints     基本类型的数组
     * @param strs     引用类型的数组
     */
    public native void testArrayAction(int count, String textInfo, int[] ints, String[] strs);

    /**
     * 让native调用
     *
     * @param num
     * @param num2
     * @return
     */
    public int add(int num, int num2) {
        return num2 + num;
    }

    public native void changeName();

    public static native void changeAge();

    public native void callAddMethod();

    /**
     * 实现在native层
     *
     * @return
     */
    public native String getStringPwd();

    public static native String getStringPwd2();

    /**
     * java 的boolen ----------- z//注意
     * byte                      B
     * char                     c
     * short                    s
     * int                      I
     * long                     J//注意
     * float                    F
     * double                   D
     * void                     V
     * object                   L包名/类名;
     * String                   Ljava/lang/String;
     * Array int[]              [I
     * double[][][]             [[[D
     *
     * javap -s -p xxx.class  -s 输出.class的所有属性和方法的签名
     * -p 忽略
     *
     */
}