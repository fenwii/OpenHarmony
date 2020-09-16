# Building the History Page<a name="EN-US_TOPIC_0000001055687636"></a>

The  **history**  page displays the air quality data of a week in a chart. On this page, multiple  **<div\>**  components are used to replace the  **<chart\>**  component to display the chart. The sample code is as follows:

## history.hml<a name="section275215487291"></a>

```
<list style="width:321px;height:321px;top:67px;left:320px;">
    <list-item class="info-list-item">
        <div style="width:321px;height:80px;flex-direction:column;align-items:flex-start;">
             <text class="div-info-historical-data">{{historicalData}}</text>
        </div>
    </list-item>
    <!-- Use the for attribute to dynamically generate listitem. The {{datasets}} corresponds to the datasets variable in history.js. Create components based on the number of elements in the variable array. -->
    <list-item style="width:321px;height:160px;"for="{{datasets}}">
       <div style="width:321px;height:160px;flex-direction:column;">
       <div style="width:321px;height:2px;background-color:#f5fffa;"></div>
       <!-- $item is an element of datasets. -->
       <text class="gas-name">{{$item}}</text>
       <div style="width:321px;height:100px;margin-top:4px;justify-content:flex-start;align-items:flex-end;">
          <!-- The color in the code example is a fixed value. You can use dynamic binding. -->
          <div style="width:21px;margin-left:21px;height:10px;backgroundColor:#00ff00;"></div>
          <div style="width:21px;margin-left:21px;height:20px;;backgroundColor:#00ff00;"></div>
          <div style="width:21px;margin-left:21px;height:90px;backgroundColor:#ff0000;"></div>
          <div style="width:21px;margin-left:21px;height:80px;backgroundColor:#ff0000;"></div>
          <div style="width:21px;margin-left:21px;height:60px;backgroundColor:#999999;"></div>
          <div style="width:21px;margin-left:21px;height:50px;backgroundColor:#999999;"></div>
          <div style="width:21px;margin-left:21px;height:100px;backgroundColor:#ff0000;"></div>
      </div>
      <!-- The x-axis icons of the chart are images. -->
      <image style="width:321px;height:20px;"src="common/week.png"></image>
      </div>
   </list-item>
   <list-item class="info-list-item">
       <!-- Button for returning to the detail page -->
       <input type="button"value="Back"style="border-width:2px;border-color:#90ee90;width:256px;height:60px;margin-left: 30px;"onclick="backDetail"/>
   </list-item>
</list>
```

## history.css<a name="section2589154215301"></a>

```
.div-info-location{
    color:#dcdcdc;
    width:321px;
    height:40px;
}
.div-info-historical-data{
    color:#f5fffa;
    width:321px;
    height:40px;
}
.gas-name{
    color:#f0ffff;
    text-align:right;
    width:321px;
    height:32px;
}
.info-list-item{
    width:321px;
    height:80px;
}
```

## history.js<a name="section163410883117"></a>

```
import router from'@system.router'
module.exports = {
    data: {
        historicalData:"historicalData",
        datasets:["CO","O3","NO2","NO","PM25","SO2"]
    },
    onInit(){
        // Process information in multiple languages.
        this.historicalData = this.$t(this.historicalData);
    },
    backDetail(){
        router.replace({  // Return to the detail page.
            uri:'pages/detail/detail'
        });
    }
}
```

