# Touchscreen Development Guidelines<a name="EN-US_TOPIC_0000001052537515"></a>

Regardless of the OS and system on a chip \(SoC\), the Touchscreen driver is developed based on the HDF, Platform, and OSAL APIs to provide a unified driver model for touchscreens.

1.  The HDF provides a unified driver management model. The HDF identifies and loads drivers through the module configuration information. The HDF starts drivers in sequence using the  **Init**  function.
2.  Implement the following operations in  **Init**:
    -   Use an OSAL interface to create device node  **/dev/input/event**_x_  and implement operation functions such as  **open**,  **close**,  **read**,  **write**, and  **ioctl**  for the node, enabling the node to transmit touch reporting data and instructions.
    -   Based on the hardware connection to the touchscreen, use the GPIO interfaces provided by the Platform to configure and perform operations for the reset pins and interrupt pins.
    -   Use the I2C or SPI interfaces provided by the Platform to implement data communication depending on the communication interfaces selected by the touchscreen.


## Limitations and Constraints<a name="section355831574414"></a>

None.

## How to Develop<a name="section1255740132616"></a>

1.  Start the driver using the  **Init**  function.

    Currently, the driver is developed based on the HDF driver model and is loaded and started by the HDF. Register the driver information in the configuration file. Then, the HDF starts the registered driver modules one by one. For details about the driver configuration, see  [How to Develop](driver-development.md#section1969312275533).

2.  Initialize the I/O status and input configurations.

    Configure the required I/O pins. For example, configure a register for the I2C pin reserved for the touchscreen to use I2C for transmitting data.

3.  Perform power sequence.

    Use the Platform interfaces to perform operations for the reset pins, interrupt pins and power based on the communications interfaces designed for boards. For details about the GPIO-related operations, see  [GPIO Usage Guidelines](gpiousage-guidelines.md).

4.  Implement the ISR function.
5.  Obtain the power status and take proper actions.
6.  Download the required touchscreen firmware.
7.  Create a device node and implement the operation function for the node.

    Create an input device node based on service requirements. For example, create the device file  **dev/input/event0**. Then, implement functions such as  **open**,  **close**,  **read**,  **write**,  **ioctl**  and  **poll**  for the file. You can add or delete them as required.


## FAQs<a name="section18129131212275"></a>

None.

