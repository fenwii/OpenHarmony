/**
 *@file ModelManager.java
 *
 * Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

package com.huawei.hiaidemo.utils;

import android.content.res.AssetManager;
import android.util.Log;
import android.widget.Toast;

import com.huawei.hiaidemo.bean.ModelInfo;
import java.util.ArrayList;

public class ModelManager {

    private static final String TAG = ModelManager.class.getSimpleName();

    private ModelManager() {
    }

    public static boolean loadJNISo() {
        try {
            System.loadLibrary("hiaijni");

            return true;
        } catch (UnsatisfiedLinkError e) {
            Log.e(TAG, "failed to load native library: " + e.getMessage());

            return false;
        }
    }

    public static native ArrayList<float[]> runModelSync(ModelInfo modelInfo, ArrayList<byte[]> buf);

    public static native long GetTimeUseSync();

    public static native void runModelAsync(ModelInfo modelInfo, ArrayList<byte[]> buf, ModelManagerListener listener);

    public static native ArrayList<ModelInfo> loadModelAsync(ArrayList<ModelInfo> modelInfo);

    public static native ArrayList<ModelInfo> loadModelSync(ArrayList<ModelInfo> modelInfo);

    /**
     *
     * @param offlinemodelpath   /xxx/xxx/xxx/xx.om
     * @return ture : it can run on NPU
     *          false: it should run on CPU
     */
    public static native boolean modelCompatibilityProcessFromFile(String offlinemodelpath);

    //public static native boolean modelCompatibilityProcessFromBuffer(byte[] onlinemodelbuffer,byte[] modelparabuffer,String framework,String offlinemodelpath);
}
