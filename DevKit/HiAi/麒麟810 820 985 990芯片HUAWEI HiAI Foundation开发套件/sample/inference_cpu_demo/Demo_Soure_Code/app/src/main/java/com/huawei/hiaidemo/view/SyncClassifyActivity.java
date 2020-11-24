/**
 *@file SyncClassifyActivity.java
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


import static com.huawei.hiaidemo.utils.Constant.AI_OK;


import java.util.ArrayList;

public class SyncClassifyActivity extends NpuClassifyActivity {

    private static final String TAG = SyncClassifyActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getSupportActionBar().hide();
    }

    @Override
    protected void runModel(ModelInfo modelInfo, ArrayList<byte[]> inputData) {
        outputDataList = ModelManager.runModelSync(modelInfo, inputData);

        if (outputDataList == null) {
            Log.e(TAG, "Sync runModel outputdata is null");

            return;
        }

        inferenceTime = ModelManager.GetTimeUseSync();
        for(float[] outputData : outputDataList){
            Log.i(TAG, "runModel outputdata length : " + outputData.length);

            postProcess(outputData);
        }
    }

    @Override
    protected ArrayList<ModelInfo> loadModel(ArrayList<ModelInfo> modelInfo) {
        return ModelManager.loadModelSync(modelInfo);
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
