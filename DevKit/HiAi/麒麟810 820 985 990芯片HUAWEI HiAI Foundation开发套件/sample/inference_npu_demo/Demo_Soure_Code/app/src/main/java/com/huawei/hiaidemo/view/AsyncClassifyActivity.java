/**
 *@file AsyncClassifyActivity.java
 *
 * Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
package com.huawei.hiaidemo.view;

import android.os.Bundle;

import android.util.Log;

import android.widget.Toast;

import com.huawei.hiaidemo.bean.ModelInfo;
import com.huawei.hiaidemo.utils.ModelManager;
import com.huawei.hiaidemo.utils.ModelManagerListener;

import java.util.ArrayList;

public class AsyncClassifyActivity extends NpuClassifyActivity {

    private static final String TAG = AsyncClassifyActivity.class.getSimpleName();


    ModelManagerListener listener = new ModelManagerListener() {

        @Override
        public void OnProcessDone(final int taskId, final ArrayList<float[]> outputList, final float inferencetime) {

            Log.e(TAG, " java layer OnProcessDone: " + taskId);
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (taskId > 0) {
                       for(float[] output:outputList){
                            Toast toast = Toast.makeText(AsyncClassifyActivity.this, "run model success. taskId is:" + taskId, Toast.LENGTH_SHORT);
                            Log.i(TAG, " run model success. taskId is: " + taskId);
                            CustomToast.showToast(toast, 50);
                            outputData = output;
                            inferenceTime = inferencetime/1000;
                            Log.i(TAG, " run model success. outputData is: " + outputData);
                            postProcess(outputData);
                       }
                    } else {
                        Toast toast = Toast.makeText(AsyncClassifyActivity.this, "run model fail. taskId is:" + taskId, Toast.LENGTH_SHORT);
                        CustomToast.showToast(toast, 50);
                    }
                }
            });

        }

        @Override
        public void onServiceDied() {
            Log.e(TAG, "onServiceDied: ");
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getSupportActionBar().hide();
    }

    @Override
    protected void runModel(ModelInfo modelInfo, ArrayList<byte[]> inputDataList) {
        ModelManager.runModelAsync(modelInfo, inputDataList, listener);
    }

    @Override
    protected ArrayList<ModelInfo> loadModel(ArrayList<ModelInfo> modelInfo) {
        return ModelManager.loadModelAsync(modelInfo);
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}
