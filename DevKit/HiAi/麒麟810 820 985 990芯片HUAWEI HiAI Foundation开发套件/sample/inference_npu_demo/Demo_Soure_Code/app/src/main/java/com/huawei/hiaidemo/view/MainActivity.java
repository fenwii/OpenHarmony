/**
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
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Toast;
import android.util.Log;
import android.widget.Spinner;


import com.huawei.hiaidemo.utils.ModelManager;
import com.huawei.hiaidemo.R;
import com.huawei.hiaidemo.bean.ModelInfo;
import com.huawei.hiaidemo.utils.Untils;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    private static final String TAG = MainActivity.class.getSimpleName();
    protected ArrayList<ModelInfo> demoModelList = new ArrayList<ModelInfo>();
    protected RecyclerView rv;
    protected boolean useNPU  = false;
    protected boolean interfaceCompatible = true;
    protected Button btnsync = null;
    protected Button btnasync = null;
    protected Spinner spinnerModel;
    protected LinearLayoutManager manager = null;
    static String selectedModelName;
    
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        initModels();
        copyModels();
        modelCompatibilityProcess();
        initSpinner();
    }

    private void initSpinner() {
        spinnerModel = findViewById(R.id.spinner2);
        ArrayList<String> modelNames = new ArrayList<>();
        for(ModelInfo modelInfo : demoModelList) {
            modelNames.add(modelInfo.getOfflineModelName());
        }

        ArrayAdapter<String> adapterModel = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, modelNames);

        spinnerModel.setAdapter(adapterModel);
        spinnerModel.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {

            @Override
            public void onItemSelected(AdapterView<?> parent, View view,
                                       int pos, long id) {

                String result = parent.getItemAtPosition(pos).toString();

                selectedModelName = result;

                Toast.makeText(MainActivity.this, "Model selected:"+selectedModelName, Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
                // Another interface callback
            }

        });
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
                        intent.putExtra("demoModelList", demoModelList);
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
                        intent.putExtra("demoModelList", demoModelList);
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
    private void copyModels(){
        AssetManager am = getAssets();
        for (ModelInfo model : demoModelList) {
            if(!Untils.isExistModelsInAppModels(model.getOfflineModel(),model.getModelSaveDir())){
                Untils.copyModelsFromAssetToAppModels(am, model.getOfflineModel(),model.getModelSaveDir());
            }
        }
    }

    private void modelCompatibilityProcess(){
        //load hiaijni.so
        boolean isSoLoadSuccess = ModelManager.loadJNISo();

        if (isSoLoadSuccess) {
            Toast.makeText(this, "load libhiai.so success.", Toast.LENGTH_SHORT).show();

            interfaceCompatible = true;

            Iterator<ModelInfo> iter = demoModelList.iterator();
            while (iter.hasNext()){
                ModelInfo model = iter.next();
                boolean isCompatible = ModelManager.modelCompatibilityProcessFromFile(model.getModelSaveDir() + model.getOfflineModel());
                //incompatible models are removed.
                if(!isCompatible){
                    Toast.makeText(this, "Model "+model.getOfflineModel()+" is not compatible!", Toast.LENGTH_SHORT).show();
                    iter.remove();
                    continue;
                }
                //true if there is any compatible model.
                useNPU |= isCompatible;
            }//while
            Log.d(TAG, "useNPU : " + useNPU);
        } else {
            interfaceCompatible = false;
            Toast.makeText(this, "load libhiai.so fail.", Toast.LENGTH_SHORT).show();
        }
    }

    protected void initModels(){
        File dir =  getDir("models", Context.MODE_PRIVATE);
        String path = dir.getAbsolutePath() + File.separator;

        // add models to be loaded here
        /*
            AIPP is supported since v310.
            Run the aipp model, you need to remove the comment symbol from the code block below.
        */
        /*
        ModelInfo model_1 = new ModelInfo();
        model_1.setModelSaveDir(path);
        model_1.setUseAIPP(true);
        model_1.setOfflineModel("hiai.om");
        model_1.setOfflineModelName("hiai");
        model_1.setOnlineModelLabel("labels_caffe.txt");
        demoModelList.add(model_1);
        */

        ModelInfo model_2 = new ModelInfo();
        model_2.setModelSaveDir(path);
        model_2.setUseAIPP(false);
        model_2.setOfflineModel("hiai_noaipp.om");
        model_2.setOfflineModelName("hiai_noaipp");
        model_2.setOnlineModelLabel("labels_caffe.txt");
        demoModelList.add(model_2);
    }

}
