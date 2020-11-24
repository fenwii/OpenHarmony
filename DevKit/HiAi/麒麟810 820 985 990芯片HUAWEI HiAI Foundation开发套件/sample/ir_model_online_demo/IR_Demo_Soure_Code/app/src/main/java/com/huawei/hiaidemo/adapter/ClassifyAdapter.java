/*
*@file ClassifyAdapter.java
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

package com.huawei.hiaidemo.adapter;

import android.support.v7.widget.CardView;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.huawei.hiaidemo.R;
import com.huawei.hiaidemo.bean.ClassifyItemModel;

import java.util.List;

public class ClassifyAdapter extends RecyclerView.Adapter<ClassifyAdapter.ClassifyViewHolder> {

    private List<ClassifyItemModel> details;

    public static final int TYPE_HEADER = 0;//头部布局
    public static final int TYPE_NORMAL = 2;//正常布局

    private View headView;

    public void setHeaderView(View headerView) {
        headView = headerView;
        notifyItemInserted(0);
    }

    public ClassifyAdapter(List<ClassifyItemModel> details) {
        this.details = details;
    }

    @Override
    public int getItemViewType(int position) {
        if (headView == null) {
            return TYPE_NORMAL;
        }
        if (position == 0) {
            return TYPE_HEADER;
        }

        return TYPE_NORMAL;
    }

    @Override
    public ClassifyViewHolder onCreateViewHolder(ViewGroup viewGroup, int viewType) {

        if (headView != null && viewType == TYPE_HEADER) {
            return new ClassifyViewHolder(headView);
        }

        View v = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.classify_item, viewGroup, false);
        ClassifyViewHolder cvh = new ClassifyViewHolder(v);
        return cvh;
    }

    @Override
    public void onBindViewHolder(ClassifyViewHolder holder, int position) {

        if (getItemViewType(position) == TYPE_NORMAL) {
            if (holder instanceof ClassifyViewHolder) {
                holder.classifyTop1Result.setText(details.get(position - 1).getTop1Result());
                holder.classifyOthersResult.setText(details.get(position - 1).getOtherResults());
                holder.classifyTime.setText(details.get(position - 1).getClassifyTime());

                holder.classifyImg.setImageBitmap(details.get(position - 1).getClassifyImg());

                return;
            }

            return;
        } else if (getItemViewType(position) == TYPE_HEADER) {
            return;
        } else {
            return;
        }
    }

    @Override
    public int getItemCount() {
        if (headView == null) {
            return details.size();
        } else {
            return details.size() + 1;
        }
    }

    class ClassifyViewHolder extends RecyclerView.ViewHolder {
        CardView cv;
        TextView classifyTop1Result;
        TextView classifyOthersResult;
        TextView classifyTime;
        ImageView classifyImg;

        ClassifyViewHolder(View itemView) {
            super(itemView);

            if (itemView == headView) {
                return;
            }

            cv = itemView.findViewById(R.id.classify_item);
            classifyTop1Result = itemView.findViewById(R.id.tv_top1Result);
            classifyOthersResult = itemView.findViewById(R.id.tv_otherResults);
            classifyTime = itemView.findViewById(R.id.tv_inferenceTime);
            classifyImg = itemView.findViewById(R.id.imgClassify);
        }
    }
}
