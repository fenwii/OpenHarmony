# Building the Detail Page<a name="EN-US_TOPIC_0000001053577188"></a>

The  **detail**  page displays air quality data, such as CO, NO2, PM10, PM2.5, and SO2. Use multiple  **<text\>**  components to display the information, and use the  **<list\>**  component to continuously swipe up and down on the page. Note that  **<list-item\>**  can have multiple child components, which must be  **<list\>**. For the  **detail**  page, you need to develop for the page typesetting and styles. The detailed code is as follows:

## detail.hml<a name="section1039826103212"></a>

```
<list style="top:67px;left:320px;width:321px;height:350px;">
    <list-item style="width:321px;height:300px;">
        <div style="width: 321px;height:300px;background-color:#000000;flex-direction:column;align-items:flex-start;">
        <text style="width:321px;height:40px; color:#dcdcdc;">{{location}}</text>
        <div class="line-div"></div>
         <!- Display all indicator values. -->
        <div class="info-div-width-height" style="margin-top:10px;">
            <text class="gas-name">CO</text>
            <text class="gas-value">{{airData[0]}}</text>
        </div>
        <div class="info-div-width-height" style="margin-top:10px;">
            <text class="gas-name">NO2</text>
            <text class="gas-value">{{airData[1]}}</text>
        </div>
        <div class="info-div-width-height" style="margin-top:10px;">
            <text class="gas-name">PM10</text>
            <text class="gas-value">{{airData[2]}}</text>
        </div>
        <div class="info-div-width-height" style="margin-top:10px;">
            <text class="gas-name">PM2.5</text>
            <text class="gas-value">{{airData[3]}}</text>
        </div>
        <div class="info-div-width-height" style="margin-top:10px;">
            <text class="gas-name">SO2</text>
            <text class="gas-value">{{airData[4]}}</text>
        </div>
        </div>
    </list-item>
    <list-item style="width:321px;height:220px;">
        <div style="width:321px;height:220px;background-color:#000000;flex-direction:column;align-items:flex-start;">
            <!-- Update time -->
            <text class="config-info">{{updated}}:{{updateStatus}}</text>
            <!- Data source -->
            <text class="config-info">{{dataSourceName}}:{{dataSource}}</text>
            <div class="line-div"></div>
            <!- Page switching button -->
            <div style="width:321px; height:55px;align-items:center; margin-top:20px;">
                <input type="button" value="History" style="border-width: 3px;margin-left:10px; border-color: #90ee90;width:146px;height:50;" onclick="openHistory"/>
                <input type="button" value="Close" style="border-width: 3px;margin-left:5px; border-color:#ff0000;width:146px;height:50;" onclick="backMain"/>
            </div>
        </div>
    </list-item>
</list>
```

## detail.css<a name="section4931125119322"></a>

```
.line-div{
    background-color:#f5fffa;
    height:2px;
    width:454px;
}
.info-div-width-height{
    width:321px;
    height:60px;
    margin-top: 20px;
}
.gas-name{
    color:#f5fffa;
    width:160px;
    height:30px;
}
.gas-value{
    text-align:right;
    color:#00fa9a;
    width:160px;
    height:30px;
}
.config-info {
    height:40px;
    width:321px;
    color:#f5fffa;
}
```

## detail.js<a name="section1547613143337"></a>

```
import router from '@system.router'
export default {
     data:{// Initialization information
        location:"HangZhou",
        udpateStatus:"1h ago",
        dataSource:"tianqi.com",
        updateTime:"15:13",
        updated:'Updated',
        dataSourceName:'Data Source',
        sampledOn:'Sampled on',
        cityIndex:0,
        airData:['100', '90', '120', '50', '150', '40', '25']
    },
    onInit(){
        // Process information in multiple languages.
        this.location = this.$t(this.location);
        this.updated = this.$t("updated");
        this.dataSourceName = this.$t("dataSourceName");
        this.sampledOn = this.$t("sampledOn");
        this.monitoringStation = this.$t("monitoringStation");
        if(this.selectedCityIndex != null){  // Save city information sent from the home page.
            this.cityIndex= this.selectedCityIndex;
        }
    },
    openHistroy(){// Switch to the history page.
        router.replace({
            uri:'pages/history/history'
        });
    },
    backMain(){  // Go back to the home page and return the information about the selected city.
        router.replace({
            uri:'pages/index/index',
            params:{selectedCityIndex:this.cityIndex}
        });
    }
}
```

