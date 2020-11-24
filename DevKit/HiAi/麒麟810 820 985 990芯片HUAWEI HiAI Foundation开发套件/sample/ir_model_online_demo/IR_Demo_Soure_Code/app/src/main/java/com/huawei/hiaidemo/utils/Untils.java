/*
*@file Untils.java
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

package com.huawei.hiaidemo.utils;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.util.Log;


import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.Closeable;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import static android.graphics.Color.blue;
import static android.graphics.Color.green;
import static android.graphics.Color.red;
import static com.huawei.hiaidemo.utils.Constant.meanValueOfBlue;
import static com.huawei.hiaidemo.utils.Constant.meanValueOfGreen;
import static com.huawei.hiaidemo.utils.Constant.meanValueOfRed;


public class Untils {

    private static final String TAG = Untils.class.getSimpleName();
    private static BufferedInputStream bis = null;
    private static InputStream fileInput = null;
    private static FileOutputStream fileOutput = null;
    private static ByteArrayOutputStream byteOut = null;

    public static byte[] getModelBufferFromModelFile(String modelPath){
        try{
            bis = new BufferedInputStream(new FileInputStream(modelPath));
            byteOut = new ByteArrayOutputStream(1024);
            byte[] buffer = new byte[1024];
            int size = 0;
            while((size = bis.read(buffer,0,1024)) != -1){
                byteOut.write(buffer,0,size);
            }
            return byteOut.toByteArray();

        }catch (Exception e){
            return  new byte[0];
        }finally {
            releaseResource(byteOut);
            releaseResource(bis);
        }
    }

    private static void releaseResource(Closeable resource){

        if(resource != null){
            try {
                resource.close();
                resource = null;
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static byte[] getPixels(String framework,Bitmap bitmap, int resizedWidth, int resizedHeight){
        if(framework == null){
            return  null;
        }
        return getPixelForIRSqueezenet(bitmap,resizedWidth, resizedHeight);
    }

    private static byte[] getPixelForIRSqueezenet(Bitmap bitmap, int resizedWidth, int resizedHeight) {
        int channel = 3;
        float[] buff = new float[channel * resizedWidth * resizedHeight];

        int rIndex, gIndex, bIndex;
        for (int i = 0; i < resizedHeight; i++) {
            for (int j = 0; j < resizedWidth; j++) {
                bIndex = i * resizedWidth + j;
                gIndex = bIndex + resizedWidth * resizedHeight;
                rIndex = gIndex + resizedWidth * resizedHeight;

                int color = bitmap.getPixel(j, i);

                buff[bIndex] = (float)(blue(color) - meanValueOfBlue);
                buff[gIndex] = (float)(green(color) - meanValueOfGreen);
                buff[rIndex] = (float)(red(color) - meanValueOfRed);
            }
        }
        int pixCount = channel * resizedWidth * resizedHeight;
        byte[] ret = new byte[pixCount * 4];

        for (int i = 0; i < pixCount; ++i) {
            int int_bits = Float.floatToIntBits(buff[i]);
            ret[(i * 4) + 0] = (byte) int_bits;
            ret[(i * 4) + 1] = (byte) (int_bits >>> 8);
            ret[(i * 4) + 2] = (byte) (int_bits >>> 16);
            ret[(i * 4) + 3] = (byte) (int_bits >>> 24);
        }

        return ret;
    }

    public static boolean copyModelsFromAssetToAppModels(AssetManager am,String sourceModelName,String destDir){

        try {
            fileInput = am.open(sourceModelName);
            String filename = destDir + sourceModelName;

            fileOutput = new FileOutputStream(filename);
            byteOut = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int len = -1;
            while ((len = fileInput.read(buffer)) != -1) {
                byteOut.write(buffer, 0, len);
            }
            fileOutput.write(byteOut.toByteArray());
            return true;
        } catch (Exception ex) {
            Log.e(TAG, "copyModelsFromAssetToAppModels : " + ex);
            return false;
        }finally {
            releaseResource(byteOut);
            releaseResource(fileOutput);
            releaseResource(fileInput);
        }
    }

    public static boolean isExistModelsInAppModels(String modelname,String savedir){

        File dir = new File(savedir);
        File[] currentfiles = dir.listFiles();
        if(currentfiles == null){
            return false;
        }else{
            for(File file: currentfiles){
                if(file.getName().equals(modelname)){
                    return true;
                }
            }
        }
        return false;
    }


}
