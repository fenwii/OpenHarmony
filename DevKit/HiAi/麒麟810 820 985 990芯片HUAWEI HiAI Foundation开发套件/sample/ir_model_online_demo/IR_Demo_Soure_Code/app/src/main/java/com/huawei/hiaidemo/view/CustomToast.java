/*
*@file CustomToast.java
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

package com.huawei.hiaidemo.view;

import android.widget.Toast;

import java.util.Timer;
import java.util.TimerTask;

public class CustomToast {

    public static void showToast(final Toast toast, final int time) {
        final Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                toast.show();
            }
        }, 0, 3000);
        new Timer().schedule(new TimerTask() {
            @Override
            public void run() {
                toast.cancel();
                timer.cancel();
            }
        }, time);
    }

}
