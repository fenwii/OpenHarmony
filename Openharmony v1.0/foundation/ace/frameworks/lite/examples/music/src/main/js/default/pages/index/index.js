/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import audio from '@system.audio'
import file from '@system.file'
import app from '@system.app'

var modeImages = ['common/ic_music_listorder.png', 'common/ic_music_listcycle.png', 'common/ic_music_shuffle.png', 'common/ic_music_singlecycle.png'];

export default {
  data: {
    showMusicList: false,
    playMode: 1,  //0:sequential,1:list loop,2:random,3:single
    modeImage: 'common/ic_music_listcycle.png',
    playImage: 'common/ic_music_play.png',
    playProgress: 0,  //progress
    curMusicIndex: 0,  //music index
    playStatus: 2,  //0:play,1:pause,2:stop
    curMusic: {  //current music info
      curMusicName: "",
      songer: "",
      playTime: "00:00",
      allTime: "00:00"
    },
    musicList: []
  },
  onInit() {
    //get music duration
    audio.onplay = () => {
      console.log("onplay start");
      this.curMusic.allTime = this.timeChange(audio.duration);
      this.playStatus = 0;
    };
    //update play progress
    audio.ontimeupdate = () => {
      console.log("ontime update:");
      this.curMusic.playTime = this.timeChange(audio.currentTime);
      console.log("ontime update:" + this.curMusic.playTime);
      this.playProgress = Math.floor(audio.currentTime * 100 / audio.duration);
      console.log("ontime update progress:" + this.playProgress + ",duration:" + audio.duration);
    };
    //play next song when meet an error
    audio.onerror = () => {
      console.log("onerror");
      this.changeSong();
    };
    //perform operations based on the playback mode.
    audio.onended = () => {
      console.log("onend");
      this.playStatus = 2;
      //after played the last song in sequential mode ,stop playback
      if (this.playMode == 0 && this.curMusicIndex == (this.musicList.length - 1)) {
        this.playStatus = 2;
        this.playImage = "common/ic_music_play.png";
        console.log("played the last song in sequential mode");
        return;
      }
      let mode = "";
      if (this.playMode == 2) {
        console.log("random");
        mode = "random";
      }
      this.changeSong(mode);
    };
    this.getMusicList();
  },
  onDestroy() {
    this.stopPlay();
  },
  clickListItem(index) {
    console.log("listItemClick:start:" + index);
    if (index == undefined || index == null) {
      index = 0;
    }
    this.curMusicIndex = index;
    this.playStatus = 2;
    this.playMusic();
    this.showMusicList = false;
    console.log("listItemClick:end");
  },
  changeProgress(value) {
    console.log("changeProgress start:" + value.progress);
    if (value == null || value.progress == null) {
      return;
    }
    if (this.playStatus == 2) {
      return;
    }
    let val = Math.floor((value.progress / 100) * audio.duration);
    console.log("changeProgress change:" + val);
    audio.currentTime = val;
    console.log("changeProgress end:");
  },
  playMusic() {
    console.log("playMusic:start");
    //play music when is paused
    this.playImage = "common/ic_music_pause.png";
    if (this.playStatus == 1) {
      audio.play();
      this.playStatus = 0;
      console.log("playMusic:play");
      return;
    } else if (this.playStatus == 0) {
      this.playImage = "common/ic_music_play.png";
      audio.pause();
      this.playStatus = 1;
      console.log("playMusic:pause");
      return;
    }
    if (this.curMusicIndex == null) {
      this.curMusicIndex = 0;
    }
    let music = this.musicList[this.curMusicIndex];
    if (music != null) {
      this.playProgress = 0;
      this.curMusic.curMusicName = music.name;
      this.curMusic.songer = music.songer;
      audio.src = music.src;
      console.log("playMusic:src:" + music.src);
      audio.play();
      if (this.playMode == 3) {
          audio.loop = true;
      } else {
          audio.loop = false;
      }
      console.log("playMusic:end");
    }
  },
  stopPlay() {
    console.log("stopPlay");
    audio.src = null;
    audio.onstop = null;
    audio.onplay = null;
    audio.ontimeupdate = null;
    audio.onerror = null;
  },
  changeMode() {
    console.log("changeMode start");
    if (this.playMode == 3) {
      this.playMode = 0;
    } else {
      this.playMode++;
    }
    if (this.playMode == 3) {
      audio.loop = true;
    } else {
      audio.loop = false;
    }
    console.log("changeMode:" + this.playMode);
    this.modeImage = modeImages[this.playMode];
  },
  changeSong(mode) {
    console.log("ChangeSong:start");
    if (this.playStatus == 0 || this.playStatus == 1) {
      this.playStatus = 2;
    }
    if (this.playMode == 2) {
      mode = "random";
    }
    //previous
    if (mode == "previous") {
      this.curMusicIndex == 0 ? (this.curMusicIndex = (this.musicList.length - 1)) : this.curMusicIndex--;
      console.log("ChangeSong:previous:" + this.curMusicIndex);
    } else if (mode == "random") {  //random
      this.curMusicIndex = parseInt(Math.random() * (this.musicList.length), 10);
      console.log("ChangeSong:random:" + this.curMusicIndex);
    } else {  //next
      (this.curMusicIndex == this.musicList.length - 1) ? this.curMusicIndex = 0 : this.curMusicIndex++;
      console.log("ChangeSong:next" + this.curMusicIndex);
    }
    this.curMusic.curMusicName = this.musicList[this.curMusicIndex].name;
    this.curMusic.songer = this.musicList[this.curMusicIndex].songer;
    this.playMusic(this.curMusicIndex);
    if(this.showMusicList){
      this.$refs.musicList.scrollTo({ index: (this.curMusicIndex == 0?0:this.curMusicIndex-1) });
    }
    console.log("ChangeSong:end");
  },
  timeChange(seconds) {
    console.log("timeChange:start:" + seconds);
    if (seconds == null || seconds < 0) {
      return "00:00";
    }
    let minute, second = 0;
    minute = Math.floor(seconds / 60);
    second = Math.floor(seconds % 60);
    let result = (minute > 9 ? minute : "0" + minute) + ":" + (second > 9 ? second : "0" + second);
    console.log("timeChange:end:" + result);
    return result;
  },
  changePage(operation) {
    console.log("changePage:start");
    if (operation != null && operation == "close") {
      this.showMusicList = false;
      return;
    }
    this.showMusicList = !this.showMusicList;
    if(this.showMusicList){
      this.$refs.musicList.scrollTo({ index: (this.curMusicIndex == 0?0:this.curMusicIndex-1) });
    }
  },
  exitApp(){
    console.log("start exit");
    app.terminate();
    console.log("end exit");
  },
  swipeEvent(e){
    if(e.direction == "right"){
      console.log("start exit");
      this.exitApp();
    }
  },
  getMusicList(){
      let that = this;
        //get all music file
        file.readText({
            uri:"internal://app/musicList.txt",
            success(data){
                console.log(data.text);
                let music = JSON.parse(data.text);
                if(music != null){
                    that.musicList = music;
                }
            },
            fail(data,code){
                console.log("get music list failed :"+code);
            }
        });
  }
}
