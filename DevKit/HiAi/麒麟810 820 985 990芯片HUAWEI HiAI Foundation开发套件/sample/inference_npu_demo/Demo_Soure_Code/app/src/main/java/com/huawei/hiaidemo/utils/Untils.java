/**
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

    public static byte[] getPixels(String framework, Bitmap bitmap,
                                   int resizedWidth, int resizedHeight) {
        int channel = 3;
        float[] buff = new float[channel * resizedWidth * resizedHeight];

        int rIndex;
        int gIndex;
        int bIndex;

        for (int i = 0; i < resizedHeight; i++) {
            for (int j = 0; j < resizedWidth; j++) {
                bIndex = (i * resizedWidth) + j;
                gIndex = bIndex + (resizedWidth * resizedHeight);
                rIndex = gIndex + (resizedWidth * resizedHeight);

                int color = bitmap.getPixel(j, i);

                buff[bIndex] = (float) (blue(color) - meanValueOfBlue);
                buff[gIndex] = (float) (green(color) - meanValueOfGreen);
                buff[rIndex] = (float) (red(color) - meanValueOfRed);
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

    public static byte[] getPixelsAIPP(String framework,Bitmap bitmap, int resizedWidth, int resizedHeight){
        Log.i(TAG, "resizedWidth : " + resizedWidth +  " resizedHeight : " + resizedHeight);
        return getNV12(resizedWidth,resizedHeight, bitmap);
    }

    private static byte [] getNV12(int inputWidth, int inputHeight, Bitmap scaled) {
        // Reference (Variation) : https://gist.github.com/wobbals/5725412

        int [] argb = new int[inputWidth * inputHeight];

        Log.i(TAG, "scaled : " + scaled);
        scaled.getPixels(argb, 0, inputWidth, 0, 0, inputWidth, inputHeight);

        byte [] yuv = new byte[inputWidth*inputHeight*3/2];
        encodeYUV420SP(yuv, argb, inputWidth, inputHeight);

        //scaled.recycle();

        return yuv;
    }

    private static void encodeYUV420SP(byte[] yuv420sp, int[] argb, int width, int height) {
        final int frameSize = width * height;

        int yIndex = 0;
        int uvIndex = frameSize;

        int a, R, G, B, Y, U, V;
        int index = 0;
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {

                a = (argb[index] & 0xff000000) >> 24; // a is not used obviously
                R = (argb[index] & 0xff0000) >> 16;
                G = (argb[index] & 0xff00) >> 8;
                B = (argb[index] & 0xff) >> 0;

                // well known RGB to YUV algorithm
                Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16;
                U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128;
                V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128;

                // NV21 has a plane of Y and interleaved planes of VU each sampled by a factor of 2
                //    meaning for every 4 Y pixels there are 1 V and 1 U.  Note the sampling is every other
                //    pixel AND every other scanline.
                yuv420sp[yIndex++] = (byte) ((Y < 0) ? 0 : ((Y > 255) ? 255 : Y));
                if (j % 2 == 0 && index % 2 == 0) {
                    yuv420sp[uvIndex++] = (byte)((U<0) ? 0 : ((U > 255) ? 255 : U));
                    yuv420sp[uvIndex++] = (byte)((V<0) ? 0 : ((V > 255) ? 255 : V));
                }

                index ++;
            }
        }
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
