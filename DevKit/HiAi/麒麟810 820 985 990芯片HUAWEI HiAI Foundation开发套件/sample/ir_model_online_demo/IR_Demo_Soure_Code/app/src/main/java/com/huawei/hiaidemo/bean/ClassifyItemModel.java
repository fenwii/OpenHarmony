/*
*@file ClassifyItemModel.java
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

package com.huawei.hiaidemo.bean;

import android.graphics.Bitmap;

public class ClassifyItemModel {
    private String top1Result;
    private String otherResults;
    private String classifyTime;
    private Bitmap classifyImg;

    public ClassifyItemModel(String top1Result, String otherResults, String classifyTime, Bitmap classifyImg) {
        this.top1Result = top1Result;
        this.otherResults = otherResults;
        this.classifyTime = classifyTime;
        this.classifyImg = classifyImg;
    }

    public String getTop1Result() {
        return top1Result;
    }

    public String getOtherResults() {
        return otherResults;
    }

    public String getClassifyTime() {
        return classifyTime;
    }

    public Bitmap getClassifyImg() {
        return classifyImg;
    }
}


