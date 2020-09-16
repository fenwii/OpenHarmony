# Building the Home Page<a name="EN-US_TOPIC_0000001054927705"></a>

The application home page displays air quality information of the current city. There are two screens on the home page. Each screen displays the air quality information of a city, including the AQI and city name. The AQI value can be displayed in the form of a ring progress bar with animation.

1.  The  **<swiper\>**  component is required to implement the switch between the two screens.

    Add a root  **<swiper\>**  to the  **.hml**  file. Note that each  **.hml**  file can contain only one root component. The code snippet is as follows:

    ```
    <swiper class="container" style="left:253px;" index="{{swiperPage}}" duration="500" onchange="swiperChange">
    </swiper>
    ```

    -   **class="container"**  indicates the style used by the component. The  **container**  is a style class in the  **index.css**  file. The code snippet is as follows:

        ```
        .container{
            height: 454px;
            width: 454px;
        }
        ```

        This style class sets the height and width of the component. For device-side development, the component height and width must be explicitly specified. Otherwise, the component may fail to be displayed.


    -   **index="\{\{swiperPage\}\}" duration="500" onchange="swiperChange"**  sets the component attribute and event.  **duration="500"**  indicates that the duration of the swiping animation is 500 ms.
    -   **index="\{\{swiperPage\}\}"**  specifies the index of the child component of  **<swiper\>**.  **\{\{swiperPage\}\}**  indicates that the index value is dynamically bound to the  **swiperPage**  variable in the JavaScript code. The index value changes with the  **swiperPage**  value.
    -   **onchange="swiperChange"**  binds the change event of the  **<swiper\>**  component to the  **swiperChange**  function. The JavaScript code is as follows:

        ```
        // Import the router module for page switch.
        import router from'@system.router'
        export default {
            // Define parameters.
            data: {
              swiperPage:0 // The first page is displayed by default.
            },
            onInit () {
            },
            // Swiping event, which saves the index value of the current <swiper>. The index value is saved to the swiperPage variable each time a swiping occurs.
            swiperChange (e) {
                this.swiperPage = e.index;
            }
        }
        ```


2.  Set the information about each city to be displayed on a screen. In each screen, four types of information need to be displayed using different components.

    Add two child components \(**<stack\>**\) to the  **<swiper\>**. Add the  **<text\>**,  **<image\>**, and  **<progress\>**  components to each  **<stack\>**  to display the information. Code example in the  **.hml**  file is as follows:

    ```
    <!-- The root component is <swiper>. Only one root component is supported. -->
     <swiper class="container" style="left:253px;" index="{{swiperPage}}" duration="500" onchange="swiperChange">
        <!-- The first screen -->
        <stack class="container">
            <text></text>------City
             <text></text>------Air quality
            <progress></progress>-----Progress bar
            <image></image>-------A cloud image
            <text></text>--------AQI value
            <text>AQI</text>------AQI
        </stack>
         <!-- The second screen -->
        <stack class="container">
            <text></text>
            <text></text>
            <progress></progress>
            <image></image>
            <text></text>
            <text></text>
        </stack>
    </swiper>
    ```

3.  Set the style, animation effect, and dynamic data binding for all components. The complete example code is as follows:

    -   **index.hml**

    ```
    <!-- The root component is <swiper>. Only one root component is supported. -->
     <swiper class="container" style="left:253px;" index="{{swiperPage}}" duration="500" onchange="swiperChange">
        <!-- The first screen -->
        <stack class="container">
            <!-- Display air quality and current city -->
            <text class="airquality" style="color:{{textColor1}};">{{airData[0].airQuality}}</text>
            <text class="location-text">{{airData[0].location}}</text>
            <!-- Display the animation effect based on the AQI value. To achieve this, you need to implement dynamic percent1 value changes in the .js file.-->
            <progress class="circleProgress"style="color:{{textColor1}};background-Color:{{bgColor1}};"type="arc"onclick="openDetail"percent="{{percent1}}"></progress>
            <image class="image"src="{{src1}}"></image>
            <!-- AQI, which is obtained dynamically -->
            <text class="pm25-value">{{airData[0].detailData}}</text>
            <text class="pm25-name">AQI</text>
        </stack>
        <!-- The second screen -->
        <stack class="container">
            <text class="airquality"style="color:{{textColor2}};">{{airData[1].airQuality}}</text>
            <text class="location-text">{{airData[1].location}}</text>
            <progress class="circleProgress"style="color: {{textColor2}};background-Color:{{bgColor2}};"type="arc"onclick="openDetail"percent="{{percent2}}"></progress>
            <image class="image"src="{{src2}}"></image>
            <text class="pm25-value">{{airData[1].detailData}}</text>
            <text class="pm25-name">AQI</text>
        </stack>
    </swiper>
    ```

    -   **index.css**

    A  **.css**  file contains many classes. Each class defines the position, size, font, color, and background color of a component. Each child component is added to the parent component, which means that the style file of the parent component affects how the child component will be displayed.

    ```
    .pm25-value{
        text-align:center;
        font-size:38px;
        color:#f0ffff;
        width:454px;
        height:50px;
        top:275px;
    }
    .pm25-name{
        text-align:center;
        color:#a2c4a2;
        width:454px;
        height:50px;
        top:335px;
    }
    .location-text{
        text-align:center;
        color:#f0ffff;
        width:454px;
        height:50px;
        top:20px;
    }
    .container{
        height: 454px;
        width: 454px;;
    }
    .circleProgress{
        centerX:227px;
        centerY:250px;
        radius:180px;
        startAngle:198;
        totalAngle:320;
        strokeWidth:45;
        width:454px;
        height:454px;
    }
    .image{
        top:390px;
        left:217px;
        width:32px;
        height:32px;
    }
    .airquality{
        top:220px;
        text-align: center;
        width:454px;
        height:40px;
    }
    
    ```

    -   **index.js**

    A  **.js**  file is used to implement interaction logic of your application. In the  **.js**  file of the home page, the following features need to be implemented: Dynamic changes of the text content and progress bar color based on numbers, multiple languages, page switch, and animation playback.

    ```
    // Import the router module for page switch.
    import router from'@system.router'
    export default {
        // Define parameters.
        data: {
          textColor1:'#00ff00',// Text color
          textColor2:'#00ff00',
          bgColor1:'#669966',// Background color
          bgColor2:'#669966',
          swiperPage:0,
          percent1:0,// Progress bar
          percent2:0,
          src1:'common/cloud_green.png',
          src2:'common/cloud_green.png',
          airData: [{
            location: 'HangZhou',
            airQuality: 'Good',
            detailData: 10
          }, {
            location: 'ShangHai',
            airQuality: 'Unhealth',
            detailData:90
          }]
        },
        onInit () {
            // Multi-language feature. Use the $t function to obtain content in the required language.
            this.airData[0].location = this.$t(this.airData[0].location);
            this.airData[1].location = this.$t(this.airData[1].location);
            this.airData[0].airQuality = this.$t(this.airData[0].airQuality);
            this.airData[1].airQuality = this.$t(this.airData[1].airQuality);
            if(this.airData[0].detailData > 100){  // Display different colors and images based on indicator values.
                this.src1 = "common/cloud_red.png";
                this.textColor1 = '#ff0000';// Display the text in red.
                this.bgColor1 = '#9d7462';
            } else if(50 < this.airData[0].detailData &&  this.airData[0].detailData <= 100){
                this.src1 = "common/cloud_yellow.png";
                this.textColor1 = '#ecf19a';// Display the text in yellow.
                this.bgColor1 = '#9d9d62';
            }
            if(this.airData[1].detailData > 100){
                this.src2 = "common/cloud_red.png";
                this.textColor2 = '#ff0000';
                this.bgColor2 = '#9d7462';
           } else if(50 < this.airData[1].detailData && this.airData[1].detailData <= 100){
                this.src2 = "common/cloud_yellow.png";
                this.textColor2 = '#ecf19a';
                this.bgColor2 = '#9d9d62';
          }
          if(this.selectedCityIndex){
               this.swiperPage = this.selectedCityIndex;
          }
        },
        onShow () {  // Processing logic during page display
            var self = this;
             var time = 1000/(self.airData[self.swiperPage].detailData);// Complete animation playback in 1s.
            if(time == 0){
                time = 100;
            }
           // Animation effect of the ring progress bar. Start a timer and change the progress bar at a certain interval (calculated based on the AQI value). The animation playback is completed within 1s.
            var interval = setInterval(function () {
                if ((self.swiperPage==0?self.percent1:self.percent2) >= self.airData[self.swiperPage].detailData) {
                    clearInterval(interval);
                    return;
                }
                if(self.swiperPage == 0){
                    self.percent1++;
                }else{
                    self.percent2++
                }
            }, time)
        },
        // Switch to the detail page.
        openDetail () {
          router.replace({
            uri:'pages/detail/detail',
            params:{selectedCityIndex:this.swiperPage}// Selected city
          });
        },
        // Swiping event, which saves the index value of the current <swiper> and directly switches to the specified <swiper> screen from the details page.
        swiperChange (e) {
            this.swiperPage = e.index;
            var self = this;
            var time = 1000/(self.airData[self.swiperPage].detailData);
            if(time == 0){
                time = 100;
            }
            // Play the animation if the user swipe to the page for the first time.
            var interval = setInterval(function () {
                let percent = (self.swiperPage==0?self.percent1:self.percent2);
                if (percent >= self.airData[self.swiperPage].detailData) {
                   clearInterval(interval);
                   return;
                }
                if(self.swiperPage==0){
                    self.percent1++;
                }else{
                    self.percent2++;
                }   
            }, time)
        }
    }
    ```


