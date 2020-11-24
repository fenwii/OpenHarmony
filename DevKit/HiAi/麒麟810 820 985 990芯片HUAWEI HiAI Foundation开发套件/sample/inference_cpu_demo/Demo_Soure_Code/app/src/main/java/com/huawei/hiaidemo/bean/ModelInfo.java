/**
 *@file ModelInfo.java
 *
 * Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

package com.huawei.hiaidemo.bean;

import java.io.Serializable;


public class ModelInfo implements Serializable{

    private String modelSaveDir = "";

    private String onlineModelLabel = "";

    private String offlineModelName = "";

    private boolean useAIPP = false;

    public boolean getUseAIPP() {
        return useAIPP;
    }

    public void setUseAIPP(boolean use){
        this.useAIPP = use;
    }

    public int getInput_N() {
        return input_N;
    }

    public void setInput_N(int input_N) {
        this.input_N = input_N;
    }

    public int getInput_C() {
        return input_C;
    }

    public void setInput_C(int input_C) {
        this.input_C = input_C;
    }

    public int getInput_H() {
        return input_H;
    }

    public void setInput_H(int input_H) {
        this.input_H = input_H;
    }

    public int getInput_W() {
        return input_W;
    }

    public void setInput_W(int input_W) {
        this.input_W = input_W;
    }

    public int getInput_Number() {
        return input_Number;
    }

    public void setInput_Number(int input_Number) {
        this.input_Number = input_Number;
    }

    public int getOutput_N() {
        return output_N;
    }

    public void setOutput_N(int output_N) {
        this.output_N = output_N;
    }

    public int getOutput_C() {
        return output_C;
    }

    public void setOutput_C(int output_C) {
        this.output_C = output_C;
    }

    public int getOutput_H() {
        return output_H;
    }

    public void setOutput_H(int output_H) {
        this.output_H = output_H;
    }

    public int getOutput_W() {
        return output_W;
    }

    public void setOutput_W(int output_W) {
        this.output_W = output_W;
    }

    public int getOutput_Number() {
        return output_Number;
    }

    public void setOutput_Number(int output_Number) {
        this.output_Number = output_Number;
    }


    private int input_N;

    private int input_C;

    private int input_H;

    private int input_W;

    private int input_Number;

    private int output_N;

    private int output_C;

    private int output_H;

    private int output_W;

    private int output_Number;

//    /**
//     * caffe : xxx.prototxt
//     * tensorflow : xxx.pb
//     * default is "" if don't have online model
//     */
//    private String onlineModel = "";
//    /**
//     * caffe: xxx.caffemodel
//     * tensorflow: ""
//     * default is "" if don't have online model
//     */
//    private String onlineModelPara = "";
    /**
     * xxx.om
     * default is "" if don't have offline model
     */
    private String offlineModel = "";
    /**
     * "" or "100.100.001.010" or "100.150.010.010" ...
     *  default is "100.100.001.010" if don't know offline model version
     */
    private String offlineModelVersion = "100.100.001.010";
    /**
     * caffe or tensorflow
     */
    private String framework = "";

    public String getModelSaveDir() {
        return modelSaveDir;
    }

    public void setModelSaveDir(String modelSaveDir) {
        this.modelSaveDir = modelSaveDir;
    }

    public String getModelPath() {
        return modelSaveDir + offlineModel;
    }

    public String getOnlineModelLabel() {
        return onlineModelLabel;
    }

    public void setOnlineModelLabel(String onlineModelLabel) {
        this.onlineModelLabel = onlineModelLabel;
    }

    public String getOfflineModelName() {
        return offlineModelName;
    }

    public void setOfflineModelName(String offlineModelName) {
        this.offlineModelName = offlineModelName;
    }

    public String getOfflineModel() {
        return offlineModel;
    }

    public void setOfflineModel(String offlineModel) {
        this.offlineModel = offlineModel;
    }

    public String getOfflineModelVersion() {
        return offlineModelVersion;
    }

    public void setOfflineModelVersion(String offlineModelVersion) {
        this.offlineModelVersion = offlineModelVersion;
    }

    public String getFramework() {
        return framework;
    }

    public void setFramework(String framework) {
        this.framework = framework;
    }
}
