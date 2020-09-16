# FAQs<a name="EN-US_TOPIC_0000001054708517"></a>

1.  Is there a global variable that can be accessed by all pages?

    No such global variable is available for all pages.

2.  How do I obtain DOM elements?

    You can obtain DOM elements via the  **ref**  attribute. You can only use methods of the obtained elements and cannot change their attributes. The following figure shows an example.

    ```
    <!--index.hml-->
    <div class="container">
       <!-- Set the ref attribute of the component to animator -->.
       <image-animator class="image-player" ref="ainmator" images="{{images}}" duration="1s" onclick="handleClick"></image-animator>
    </div>
    
    /* index.js */
    export default {
        data: {
            images:[
                {src:"common/frame1.png"},
                {src:"common/frame2.png"},
                {src:"common/frame3.png"}
            ]
        },
        handleClick(){
            // Obtain the component through the $refs attribute. (The ref attribute of the component has been set to animator in the HML file.)
            const animator = this.$refs.animator;
            const state = animator.getState();
            if(state == "paused"){
                animator.resume();
            }else if(state == "stopped"){
                animator.start();
            }else{
                animator.pause();
            }
        }
    }
    ```

3.  How do I pass values between pages?

    You can pass values through  **params**  of the  **router.replace**  method. The sample code is as follows:

    Set  **params**  to the values to be passed on a page.

    ```
    router.replace({
         uri:'pages/detail/detail',  // URI of the page to be redirected to.
        params:{transferData:this.data} // Data to be transferred. You need to define the data amount and name.
    });
    ```

    Receive the passed values on another page.

    ```
    onInit(){
        const data = this.transferData; // Receive the transferred data by the onInit function.
    }  
    ```

4.  How do I scroll a list to an item?

    Call the  **scrollTo**  method of the list. The input parameter of this method is the index of the target item. You can specify an item index, or obtain the index through the  **scrollend**  event.

5.  Does the  **<text\>**  component support multiple lines?

    Yes. You can use the Enter key to start a new line. Alternatively, you can choose not to set the height attribute of the text, and the component automatically starts a new line based on the content.

6.  Why is a component not displayed?

    **Description**

    The component added to the  **.hml**  file cannot be displayed.

    **Possible Causes**

    -   The width and height of the component may not be set.
    -   The style setting may be incorrect.

    **Solution**

    \(1\) Check whether the width and height values are set explicitly.

    \(2\) Check whether the style of the component is set correctly.

7.  How do I implement scrolling on a page?

    There are three ways to implement page scrolling:  **scroll**,  **<list\>**, or  **<swiper\>**. For a root component with  **scroll**  set, the scrolling effect is automatically implemented when the component size exceeds the screen size. For details, see the  _HarmonyOS Development Specifications_.

8.  Why do not the  **left**  and  **top**  attributes take effect?

    In addition to the root component,  **left**  and  **top**  attributes must work with the  **<stack\>**  component.

9.  Why does dynamic binding not take effect?

    The object or its attributes are not defined before dynamic binding.

10. How do I implement relative and absolute positioning?

    You can use the  **<div\>**  and  **<stack\>**  \(with  **top**  and  **left**  attributes\) components.

11. How do I set component transparency?

    For the  **<image\>**  component, set the  **opacity**  attribute to adjust the transparency. For other components, set the alpha value \(in RGBA color channels\) of a component.

12. How do I display or hide a component?

    You can use  **display**,  **show**, or  **if**. When an  **if**  clause evaluates to  **false**, the corresponding component will be removed from the VDOM. When  **show**  is set to  **false**, the component will be invisible during rendering, but will not be removed from the VDOM.

13. What are the precautions for using the  **margin**  attribute?

    The  **margin**  attribute cannot be set for child components of the  **<stack\>**  component.

14. What are the precautions for event subscription?

    Only one page exists when the application is running. Therefore, the  **router.replace**  function destroys the previous page and then creates a new one. For event subscription pages, the event should be subscribed every time a page is created, and unsubscribed before a page switch.

15. What are the precautions for using dynamic binding?

    Do not use too many dynamic bindings because they consume too much memory.

16. How does the  **loop**  attribute take effect for  **<swiper\>**?

    If the total length of the child components, except for the first and last ones, is greater than the length of  **<swiper\>**, the  **loop**  attribute takes effect.

17. What are the precautions for using an array?

    Do not include too many elements in an array. Avoid frequent operations on a large array.


