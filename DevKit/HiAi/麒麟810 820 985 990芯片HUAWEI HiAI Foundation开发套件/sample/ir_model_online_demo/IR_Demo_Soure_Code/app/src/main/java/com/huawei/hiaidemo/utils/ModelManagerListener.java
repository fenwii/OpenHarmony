/*
*@file ModelManagerListener.java
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

package com.huawei.hiaidemo.utils;

import java.util.ArrayList;

public interface ModelManagerListener {

    void OnProcessDone(int taskId, ArrayList<float[]> output, float inferencetime);

    void onServiceDied();

}
