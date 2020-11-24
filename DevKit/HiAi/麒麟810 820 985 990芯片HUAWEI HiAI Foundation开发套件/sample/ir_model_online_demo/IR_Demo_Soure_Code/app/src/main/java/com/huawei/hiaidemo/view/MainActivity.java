/*
*@file MainActivity.java
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

package com.huawei.hiaidemo.view;

import android.content.Context;
import android.content.Intent;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.huawei.hiaidemo.utils.ModelManager;
import com.huawei.hiaidemo.R;
import com.huawei.hiaidemo.bean.ModelInfo;
import com.huawei.hiaidemo.utils.Untils;

import java.io.File;


public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    protected ModelInfo demoModelInfo = new ModelInfo();
    protected RecyclerView rv;
    protected boolean useNPU  = false;
    protected boolean interfaceCompatible = true;
    protected Button btnsync = null;
    protected Button btnasync = null;
    protected LinearLayoutManager manager = null;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        initModels();
        modelCompatibilityProcess();
    }

    private void initView() {
        rv = (RecyclerView) findViewById(R.id.rv);
        manager = new LinearLayoutManager(this);
        rv.setLayoutManager(manager);
        btnsync = (Button) findViewById(R.id.btn_sync);
        btnasync = (Button) findViewById(R.id.btn_async);
        btnsync.setOnClickListener(this);
        btnasync.setOnClickListener(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_sync:
                if(interfaceCompatible) {
                    if (useNPU) {
                        Intent intent = new Intent(MainActivity.this, SyncClassifyActivity.class);
                        intent.putExtra("modelInfo", demoModelInfo);
                        startActivity(intent);
                    } else {
                        Toast.makeText(this, "Model incompatibility or NO online Compiler interface or Compile model failed, Please run it on CPU", Toast.LENGTH_SHORT).show();
                    }
                }else {
                    Toast.makeText(this, "Interface incompatibility, Please run it on CPU", Toast.LENGTH_SHORT).show();
                }
                break;

            case R.id.btn_async:
                if(interfaceCompatible) {
                    if (useNPU) {
                        Intent intent = new Intent(MainActivity.this, AsyncClassifyActivity.class);
                        intent.putExtra("modelInfo", demoModelInfo);
                        startActivity(intent);
                    } else {
                        Toast.makeText(this, "Model incompatibility or NO online Compiler interface or Compile model failed, Please run it on CPU", Toast.LENGTH_SHORT).show();
                    }
                }else{
                    Toast.makeText(this, "Interface incompatibility, Please run it on CPU", Toast.LENGTH_SHORT).show();
                }
                break;
        }

    }

    private void modelCompatibilityProcess(){
        //load hiaijni.so
        boolean isSoLoadSuccess = ModelManager.loadJNISo();

        if (isSoLoadSuccess) {
            Toast.makeText(this, "load libhiai.so success.", Toast.LENGTH_SHORT).show();

            interfaceCompatible = true;
            useNPU = ModelManager.createOmModel(demoModelInfo.getModelSaveDir()+demoModelInfo.getOfflineModel(),getAssets());

        } else {
            interfaceCompatible = false;
            Toast.makeText(this, "load libhiai.so fail.", Toast.LENGTH_SHORT).show();
        }
    }

    protected void initModels(){
        File dir =  getDir("models", Context.MODE_PRIVATE);
        String path = dir.getAbsolutePath() + File.separator ;
        demoModelInfo.setModelSaveDir(path);
        demoModelInfo.setOfflineModel("hiai.om");
        demoModelInfo.setOfflineModelName("hiai");
        demoModelInfo.setOnlineModelLabel("labels_caffe.txt");

        demoModelInfo.setInput_Number(1);
        demoModelInfo.setInput_N(1);
        demoModelInfo.setInput_C(3);
        demoModelInfo.setInput_H(227);
        demoModelInfo.setInput_W(227);
        demoModelInfo.setOutput_Number(1);
        demoModelInfo.setOutput_N(1);
        demoModelInfo.setOutput_C(1000);
        demoModelInfo.setOutput_H(1);
        demoModelInfo.setOutput_W(1);

    }
}
