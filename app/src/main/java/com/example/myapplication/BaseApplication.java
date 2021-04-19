package com.example.myapplication;

import android.app.Application;
import android.os.Debug;

import java.io.File;

public class BaseApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        File file = getExternalFilesDir(null);//注意该方法是Context的方法,故需要调用的地方如果不在Activity中,需要传入Context调用
        Debug.startMethodTracing("enjoy");
    }
}
