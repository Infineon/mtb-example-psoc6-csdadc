# PSoC&trade; 6 MCU: CSD analog-to-digital converter (ADC)

This code example demonstrates the usage of CSDADC in PSoC&trade; 6 MCU. The CSDADC measures the external voltage and displays the conversion result in the terminal application. The CSDADC feature is provided by configuring the CAPSENSE&trade; sigma-delta (CSD) block as an ADC with 10-bit resolution. The CSD block can support both capacitive sensing and CSDADC functions in a time-multiplexed fashion. This example uses the [CSDADC middleware library](https://github.com/Infineon/csdadc).

**Note:** For general analog-to-digital conversion applications, the SAR ADC block in PSoC&trade; 6 MCU devices provides more features and higher resolution (12-bit). The CSDADC can used be if the SAR ADC is not available. The SAR ADC can be accessed using [ADC HAL](https://Infineon.github.io/mtb-hal-cat1/html/group__group__hal__adc.html).

[View this README on GitHub.](https://github.com/Infineon/mtb-example-psoc6-csdadc)

[Provide feedback on this code example.]()

## Requirements

- [ModusToolbox&trade;](https://www.infineon.com/modustoolbox) v3.1 or later (tested with v3.1)
- Board support package (BSP) minimum required version: 4.1.0
- Programming language: C
- Associated parts: All [PSoC&trade; 6 MCU](https://www.infineon.com/cms/en/product/microcontroller/32-bit-psoc-arm-cortex-microcontroller/psoc-6-32-bit-arm-cortex-m4-mcu) parts, [AIROC&trade; CYW20819 Bluetooth&reg; & Bluetooth&reg; LE SoC](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-bluetooth-le-bluetooth-multiprotocol/airoc-bluetooth-le-bluetooth/cyw20819), [AIROC&trade; CYW43012 Wi-Fi & Bluetooth&reg; combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/wi-fi-4-802.11n/cyw43012), [AIROC&trade; CYW4343W Wi-Fi & Bluetooth&reg; combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/wi-fi-4-802.11n/cyw4343w), [AIROC&trade; CYW4373 Wi-Fi & Bluetooth&reg; combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/wi-fi-5-802.11ac/cyw4373), [AIROC&trade; CYW43439 Wi-Fi & Bluetooth&reg; combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/wi-fi-4-802.11n/cyw43439)



## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v11.3.1 (`GCC_ARM`) – Default value of `TOOLCHAIN`
- Arm&reg; Compiler v6.16 (`ARM`)
- IAR C/C++ Compiler v9.30.1 (`IAR`)




## Supported kits (make variable 'TARGET')


- [PSoC&trade; 62S2 Wi-Fi Bluetooth&reg; Prototyping Kit](https://www.infineon.com/CY8CPROTO-062S2-43439) (`CY8CPROTO-062S2-43439`) – Default value of `TARGET`
- [PSoC&trade; 6 Wi-Fi Bluetooth&reg; Prototyping Kit](https://www.infineon.com/CY8CPROTO-062-4343W) (`CY8CPROTO-062-4343W`)
- [PSoC&trade; 6 Wi-Fi Bluetooth&reg; Pioneer Kit](https://www.infineon.com/CY8CKIT-062-WIFI-BT) (`CY8CKIT-062-WIFI-BT`)
- [PSoC&trade; 6 Bluetooth&reg; LE Pioneer Kit](https://www.infineon.com/CY8CKIT-062-BLE) (`CY8CKIT-062-BLE`)
- [PSoC&trade; 6 Bluetooth&reg; LE Prototyping Kit](https://www.infineon.com/CY8CPROTO-063-BLE) (`CY8CPROTO-063-BLE`)
- [PSoC&trade; 62S2 Wi-Fi Bluetooth&reg; Pioneer Kit](https://www.infineon.com/CY8CKIT-062S2-43012) (`CY8CKIT-062S2-43012`)
- [PSoC&trade; 62S1 Wi-Fi Bluetooth&reg; Pioneer Kit](https://www.infineon.com/CYW9P62S1-43438EVB-01) (`CYW9P62S1-43438EVB-01`)
- [PSoC&trade; 62S1 Wi-Fi Bluetooth&reg; Pioneer Kit](https://www.infineon.com/CYW9P62S1-43012EVB-01) (`CYW9P62S1-43012EVB-01`)
- [PSoC&trade; 62S3 Wi-Fi Bluetooth&reg; Prototyping Kit](https://www.infineon.com/CY8CPROTO-062S3-4343W) (`CY8CPROTO-062S3-4343W`)
- [PSoC&trade; 64 "Secure Boot" Wi-Fi Bluetooth&reg; Pioneer Kit](https://www.infineon.com/CY8CKIT-064B0S2-4343W) (`CY8CKIT-064B0S2-4343W`)
- [PSoC&trade; 62S4 Pioneer Kit](https://www.infineon.com/CY8CKIT-062S4) (`CY8CKIT-062S4`)
- [PSoC&trade; 62S2 Evaluation Kit](https://www.infineon.com/CY8CEVAL-062S2) (`CY8CEVAL-062S2`, `CY8CEVAL-062S2-LAI-4373M2`, `CY8CEVAL-062S2-MUR-43439M2`, `CY8CEVAL-062S2-LAI-43439M2`, `CY8CEVAL-062S2-MUR-4373M2`, `CY8CEVAL-062S2-MUR-4373EM2`)
- [PSoC&trade; 64 "Secure Boot" Prototyping Kit](https://www.infineon.com/CY8CPROTO-064B0S3) (`CY8CPROTO-064B0S3`)
- [PSoC&trade; 64 "Secure Boot" Prototyping Kit](https://www.infineon.com/CY8CPROTO-064S1-SB) (`CY8CPROTO-064S1-SB`)




## Hardware setup


This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly. Place a potentiometer as shown in Table 1 to vary the input voltage to be measured by the ADC. To change the CSDADC input pin, modify the [CSDADC configuration](#enabling-the-csdadc-functionality).

**Table 1. CSDADC input pin**

Kit                        | CSDADC input pin
:--------------------------|-----------------
CY8CPROTO-062-4343W        | P10 [0]
CY8CKIT-062-BLE            | P10 [0]
CY8CKIT-062-WIFI-BT        | P10 [0]
CY8CKIT-062S2-43012        | P10 [0]
CY8CPROTO-063-BLE          | P10 [0]
CYW9P62S1-43438EVB-01      | P10 [0]
CYW9P62S1-43012EVB-01      | P10 [0]
CY8CPROTO-062S3-4343W      | P9  [1]
CY8CKIT-064B0S2-4343W      | P10 [0]
CY8CKIT-062S4              | P10 [0]
CY8CEVAL-062S2             | P10 [0]
CY8CEVAL-062S2-LAI-4373M2  | P10 [0]
CY8CEVAL-062S2-MUR-43439M2 | P10 [0]
CY8CPROTO-064B0S3          | P9 [1]
CY8CPROTO-064S1-SB         | P10 [0]
CY8CPROTO-062S2-43439      | P10 [0]
CY8CEVAL-062S2-LAI-43439M2 | P10 [0]
CY8CEVAL-062S2-MUR-4373M2  | P10 [0]
CY8CEVAL-062S2-MUR-4373EM2 | P10 [0]

<br>

> **Note:** The PSoC&trade; 6 Bluetooth&reg; LE Pioneer Kit (CY8CKIT-062-BLE) and the PSoC&trade; 6 Wi-Fi Bluetooth&reg; Pioneer Kit (CY8CKIT-062-WIFI-BT) ship with KitProg2 installed. ModusToolbox&trade; requires KitProg3. Before using this code example, make sure that the board is upgraded to KitProg3. The tool and instructions are available in the [Firmware Loader](https://github.com/Infineon/Firmware-loader) GitHub repository. If you do not upgrade, you will see an error like "unable to find CMSIS-DAP device" or "KitProg firmware is out of date".



## Software setup

See the [ModusToolbox&trade; tools package installation guide](https://www.infineon.com/ModusToolboxInstallguide) for information about installing and configuring the tools package.
Install a terminal emulator if you don't have one. Instructions in this document use [Tera Term](https://teratermproject.github.io/index-en.html).

This example requires no additional software or tools.



## Using the code example

### Create the project

The ModusToolbox&trade; tools package provides the Project Creator as both a GUI tool and a command line tool.

<details><summary><b>Use Project Creator GUI</b></summary>

1. Open the Project Creator GUI tool.

   There are several ways to do this, including launching it from the dashboard or from inside the Eclipse IDE. For more details, see the [Project Creator user guide](https://www.infineon.com/ModusToolboxProjectCreator) (locally available at *{ModusToolbox&trade; install directory}/tools_{version}/project-creator/docs/project-creator.pdf*).

2. On the **Choose Board Support Package (BSP)** page, select a kit supported by this code example. See [Supported kits](#supported-kits-make-variable-target).

   > **Note:** To use this code example for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. On the **Select Application** page:

   a. Select the **Applications(s) Root Path** and the **Target IDE**.

   > **Note:** Depending on how you open the Project Creator tool, these fields may be pre-selected for you.

   b.	Select this code example from the list by enabling its check box.

   > **Note:** You can narrow the list of displayed examples by typing in the filter box.

   c. (Optional) Change the suggested **New Application Name** and **New BSP Name**.

   d. Click **Create** to complete the application creation process.

</details>

<details><summary><b>Use Project Creator CLI</b></summary>

The 'project-creator-cli' tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the 'project-creator-cli' tool. On Windows, use the command-line 'modus-shell' program provided in the ModusToolbox&trade; installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; tools. You can access it by typing "modus-shell" in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

The following example clones the "[mtb-example-csdadc](https://github.com/Infineon/mtb-example-psoc6-csdadc)" application with the desired name "CsdAdc" configured for the *CY8CPROTO-062S2-43439* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id CY8CPROTO-062S2-43439 --app-id mtb-example-psoc6-csdadc --user-app-name CsdAdc --target-dir "C:/mtb_projects"
   ```


The 'project-creator-cli' tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the <id> field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the <id> field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

> **Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project creator tools" section of the [ModusToolbox&trade; tools package user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at {ModusToolbox&trade; install directory}/docs_{version}/mtb_user_guide.pdf).

</details>



### Open the project

After the project has been created, you can open it in your preferred development environment.


<details><summary><b>Eclipse IDE</b></summary>

If you opened the Project Creator tool from the included Eclipse IDE, the project will open in Eclipse automatically.

For more details, see the [Eclipse IDE for ModusToolbox&trade; user guide](https://www.infineon.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; install directory}/docs_{version}/mt_ide_user_guide.pdf*).

</details>


<details><summary><b>Visual Studio (VS) Code</b></summary>

Launch VS Code manually, and then open the generated *{project-name}.code-workspace* file located in the project directory.

For more details, see the [Visual Studio Code for ModusToolbox&trade; user guide](https://www.infineon.com/MTBVSCodeUserGuide) (locally available at *{ModusToolbox&trade; install directory}/docs_{version}/mt_vscode_user_guide.pdf*).

</details>


<details><summary><b>Keil µVision</b></summary>

Double-click the generated *{project-name}.cprj* file to launch the Keil µVision IDE.

For more details, see the [Keil µVision for ModusToolbox&trade; user guide](https://www.infineon.com/MTBuVisionUserGuide) (locally available at *{ModusToolbox&trade; install directory}/docs_{version}/mt_uvision_user_guide.pdf*).

</details>


<details><summary><b>IAR Embedded Workbench</b></summary>

Open IAR Embedded Workbench manually, and create a new project. Then select the generated *{project-name}.ipcf* file located in the project directory.

For more details, see the [IAR Embedded Workbench for ModusToolbox&trade; user guide](https://www.infineon.com/MTBIARUserGuide) (locally available at *{ModusToolbox&trade; install directory}/docs_{version}/mt_iar_user_guide.pdf*).

</details>


<details><summary><b>Command line</b></summary>

If you prefer to use the CLI, open the appropriate terminal, and navigate to the project directory. On Windows, use the command-line 'modus-shell' program; on Linux and macOS, you can use any terminal application. From there, you can run various `make` commands.

For more details, see the [ModusToolbox&trade; tools package user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>



## Operation


If using a PSoC&trade; 64 "Secure" MCU kit (like CY8CKIT-064B0S2-4343W), the PSoC&trade; 64 device must be provisioned with keys and policies before being programmed. Follow the instructions in the ["Secure Boot" SDK user guide](https://www.infineon.com/dgdlac/Infineon-PSoC_64_Secure_MCU_Secure_Boot_SDK_User_Guide-Software-v07_00-EN.pdf?fileId=8ac78c8c7d0d8da4017d0f8c361a7666) to provision the device. If the kit is already provisioned, copy-paste the keys and policy folder to the application folder.

1. Connect the board to your PC using the provided USB cable through the KitProg3 USB connector.

2. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud.

3. Program the board using one of the following:

   <details><summary><b>Using Eclipse IDE</b></summary>

      1. Select the application project in the Project Explorer.

      2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3_MiniProg4)**.
   </details>


   <details><summary><b>In other IDEs</b></summary>

   Follow the instructions in your preferred IDE.
   </details>


   <details><summary><b>Using CLI</b></summary>

     From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. The default toolchain is specified in the application's Makefile but you can override this value manually:
      ```
      make program TOOLCHAIN=<toolchain>
      ```

      Example:
      ```
      make program TOOLCHAIN=GCC_ARM
      ```
   </details>

4. After programming, the application starts automatically. Confirm that "\<PSoC&trade; 6 MCU: CSDADC>" is displayed on the UART terminal.


5. Press and release the user button. Notice the time displayed in seconds. The time corresponds to the interval between the two user button release events.

    **Figure 1. Terminal window on startup**

    ![](images/terminal_output.png)

5. Turn the knob of the potentiometer and observe that the new ADC count is printed on the serial terminal.




## Debugging


You can debug the example to step through the code.


<details><summary><b>In Eclipse IDE</b></summary>

Use the **\<Application Name> Debug (KitProg3_MiniProg4)** configuration in the **Quick Panel**. For details, see the "Program and debug" section in the [Eclipse IDE for ModusToolbox&trade; user guide](https://www.infineon.com/MTBEclipseIDEUserGuide).

<mark> Add the below Note for relevant CEs only, like PSoC 6 MCU based. Remove this note for others.

> **Note:** **(Only while debugging)** On the CM4 CPU, some code in `main()` may execute before the debugger halts at the beginning of `main()`. This means that some code executes twice – once before the debugger stops execution, and again after the debugger resets the program counter to the beginning of `main()`. See [KBA231071](https://community.infineon.com/docs/DOC-21143) to learn about this and for the workaround.

</details>


<details><summary><b>In other IDEs</b></summary>

Follow the instructions in your preferred IDE.
</details>



## Design and implementation

In this example, the CSD block is configured as an ADC with 10-bit resolution, one input channel with the GND-to-VDDA range, and single-shot conversion mode. For details on CSDADC, see the [CSDADC middleware library](https://github.com/Infineon/csdadc).

The CSDADC can be configured by the ModusToolbox&trade; software CSD personality. For details on configuring the CSDADC, see the [Configuration considerations](https://infineon.github.io/csdadc/csdadc_api_reference_manual/html/index.html) section in the CSDADC API reference guide.

A GPIO pin is configured as the analog input to CSDADC, and a UART resource along with the [retarget-io](https://github.com/Infineon/retarget-io) library is used for displaying the terminal messages.

The CSDADC is not enabled in the default board configuration provided by the BSP. This example overrides the `BSP_DESIGN_MODUS` component provided with the BSP to enable and configure the CSDADC. See the "Overriding the BSP configuration files" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/ide_{version}/docs/mtb_user_guide.pdf*).

The *design.modus* file containing the custom device configuration used in this application is present under the respective kit's folder: *\<application_folder>/templates/TARGET_\<BSP-NAME>/config/design.modus*.


### Enabling the CSDADC functionality

This section guides how to set up the CSDADC middleware for the CSDADC operation using ModusToolbox&trade; software.

1. Launch the **Device configurator** tool from the **Quick Panel** of the IDE. This opens the *design.modus* file located in *\<application_folder>/templates/TARGET_\<BSP-NAME>/config/design.modus*.

2. On the **System** tab, configure the **CLK_PERI** frequency to achieve the desired frequency. This is the clock input to the CSDADC.

3. On the **Peripherals** tab (#1 in **Figure 2**), enable the **CSD** personality under **System** (#2 in **Figure 2**) and enter the **Alias** (#3 in **Figure 2**).

4. Go to the **Parameters** pane and configure the CSD personality:

   1. Assign the peripheral clock divider by using the **Clock** combo box (#4 in **Figure 2**). Any free divider can be used.

   2. Set the **Enable CSDADC** check box (#5 in **Figure 2**).

   3. Configure the CSDADC parameters (Resolution, Measurement Range, and Number of Channels (#5 in **Figure 2**)).

   4. Assign pins for the CSDADC channels (#6 in **Figure 2**).

4. Select **File** > **Save** to generate the initialization code. This is executed as  part of the `init_cycfg_all()` function, which is called by `cybsp_init()`.

    **Figure 2. Settings to enable CSDADC functionality**

    ![](images/csdadc_enable.png)

### Operation at a custom power supply voltage

The application is configured to work with the default operating voltage of the kit. **Table 2** lists the power supply voltages supported by each kit along with the default operating voltage.

**Table 2. Operating voltages supported by the kits**

Kit                        | Supported operating voltages | Default operating voltage
:------------------------- | ---------------------------- | -------------------------
CY8CPROTO-062-4343W        | 3.3 V / 1.8 V                | 3.3 V
CY8CKIT-062-BLE            | 3.3 V / 1.8 V                | 3.3 V
CY8CPROTO-063-BLE          | 3.3 V / 1.8 V                | 3.3 V
CY8CKIT-062-WIFI-BT        | 3.3 V / 1.8 V                | 3.3 V
CY8CKIT-062S2-43012        | 3.3 V / 1.8 V                | 3.3 V
CYW9P62S1-43438EVB-01      | 3.3 V only                   | 3.3 V
CYW9P62S1-43012EVB-01      | 1.8 V only                   | 1.8 V
CY8CPROTO-062S3-4343W      | 3.3 V / 1.8 V                | 3.3 V
CY8CKIT-064B0S2-4343W      | 3.3 V / 1.8 V                | 3.3 V
CY8CKIT-062S4              | 3.3 V / 1.8 V                | 3.3 V
CY8CEVAL-062S2             | 3.3 V / 1.8 V                | 3.3 V
CY8CEVAL-062S2-LAI-4373M2  | 3.3 V / 1.8 V                | 3.3 V
CY8CEVAL-062S2-MUR-43439M2 | 3.3 V / 1.8 V                | 3.3 V
CY8CPROTO-064B0S3          | 3.3 V / 1.8 V                | 3.3 V
CY8CPROTO-064S1-SB         | 3.3 V / 1.8 V                | 3.3 V
CY8CPROTO-062S2-43439      | 3.3 V / 1.8 V                | 3.3 V
CY8CEVAL-062S2-LAI-43439M2 | 3.3 V / 1.8 V                | 3.3 V
CY8CEVAL-062S2-MUR-4373M2  | 3.3 V / 1.8 V                | 3.3 V
CY8CEVAL-062S2-MUR-4373EM2 | 3.3 V / 1.8 V                | 3.3 V
<br>

For kits that support multiple operating voltages, do the following to work at a custom power supply, such as 1.8 V:

1. Launch the **Device configurator** tool from the **Quick Panel** of the IDE. This opens the *design.modus* file located in *\<application_folder>/templates/TARGET_\<BSP-NAME>/config/design.modus*.

2. Update the operating conditions as shown in **Figure 3** and select **File** > **Save**.

   **Figure 3. Power settings to work with 1.8 V**

   ![](images/system_power_cfg.png)

3. Change the jumper/switch setting as listed in **Table 3**.

    **Table 3. Jumper/switch position for 1.8 V operation**

     Kit                         | Jumper/switch position         
    :----------------------------|--------------------------------
     CY8CPROTO-062-4343W         | J3 (1-2)                       
     CY8CKIT-062-BLE             | SW5 (1-2)                      
     CY8CKIT-062-WIFI-BT         | SW5 (1-2)                      
     CY8CPROTO-063-BLE           | Populate 0 Ω resistor at R41 
     CY8CKIT-062S2-43012         | J14 (1-2)                      
     CYW9P62S1-43438EVB-01       | J14 (1-2)                      
     CYW9P62S1-43012EVB-01       | J14 (1-2)                      
     CY8CPROTO-062S3-4343W       | J3 (1-2)                       
     CY8CKIT-064B0S2-4343W       | J14 (1-2)                      
     CY8CKIT-062S4               | J12 (1-2)                      
     CY8CEVAL-062S2              | J18 (1-2)                      
     CY8CEVAL-062S2-LAI-4373M2   | J18 (1-2)       
     CY8CEVAL-062S2-MUR-43439M2  | J18 (1-2)   
     CY8CPROTO-064B0S3           | J3 (NC)
     CY8CPROTO-064S1-SB          | J3 (1-2)
     CY8CPROTO-062S2-43439       | J3 (1-2)
     CY8CEVAL-062S2-LAI-43439M2  | J18 (1-2)
     CY8CEVAL-062S2-MUR-4373M2   | J18 (1-2)
     CY8CEVAL-062S2-MUR-4373EM2  | J18 (1-2)
<br>

4. Re-build and program the application to evaluate the application at the new power setting.


### Resources and settings


**Table 1. Application resources**

Resource  |  Alias/object     |    Purpose
:------- | :------------    | :------------
CSDADC (Middleware) | csdadc_context | CSDADC middleware instance that provides an ADC solution using the CSD HW block for measurements
UART (HAL) |cy_retarget_io_uart_obj| UART HAL object used by Retarget-IO for debug UART port

<br />

## Related resources


Resources  | Links
-----------|----------------------------------
Application notes  | [AN228571](https://www.infineon.com/AN228571) – Getting started with PSoC&trade; 6 MCU on ModusToolbox&trade; <br />  [AN215656](https://www.infineon.com/AN215656) – PSoC&trade; 6 MCU: Dual-CPU system design
Code examples  | [Using ModusToolbox&trade;](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub
Device documentation | [PSoC&trade; 6 MCU datasheets](https://documentation.infineon.com/html/psoc6/bnm1651211483724.html) <br /> [PSoC&trade; 6 technical reference manuals](https://documentation.infineon.com/html/psoc6/zrs1651212645947.html)<br /> [PSoC&trade; 4 datasheets](https://www.infineon.com/cms/en/search.html?intc=searchkwr-return#!view=downloads&term=psoc%204&doc_group=Data%20Sheet) <br />[PSoC&trade; 4 technical reference manuals](https://www.infineon.com/cms/en/search.html#!term=psoc%204%20technical%20reference%20manual&view=all)
Development kits | Select your kits from the [Evaluation board finder](https://www.infineon.com/cms/en/design-support/finder-selection-tools/product-finder/evaluation-board).
Libraries on GitHub  | [mtb-pdl-cat1](https://github.com/Infineon/mtb-pdl-cat1) – PSoC&trade; 6 Peripheral Driver Library (PDL)  <br /> [mtb-hal-cat1](https://github.com/Infineon/mtb-hal-cat1) – Hardware Abstraction Layer (HAL) library <br /> [retarget-io](https://github.com/Infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port
Middleware on GitHub  | [capsense](https://github.com/Infineon/capsense) – CAPSENSE&trade; library and documents <br /> [psoc6-middleware](https://github.com/Infineon/modustoolbox-software#psoc-6-middleware-libraries) – Links to all PSoC&trade; 6 MCU middleware
Tools  | [ModusToolbox&trade;](https://www.infineon.com/modustoolbox) – ModusToolbox&trade; software is a collection of easy-to-use libraries and tools enabling rapid development with Infineon MCUs for applications ranging from wireless and cloud-connected systems, edge AI/ML, embedded sense and control, to wired USB connectivity using PSoC&trade; Industrial/IoT MCUs, AIROC&trade; Wi-Fi and Bluetooth&reg; connectivity devices, XMC&trade; Industrial MCUs, and EZ-USB&trade;/EZ-PD&trade; wired connectivity controllers. ModusToolbox&trade; incorporates a comprehensive set of BSPs, HAL, libraries, configuration tools, and provides support for industry-standard IDEs to fast-track your embedded application development.

<br />



## Other resources

Infineon provides a wealth of data at [www.infineon.com](https://www.infineon.com) to help you select the right device, and quickly and effectively integrate it into your design.

For PSoC&trade; 6 MCU devices, see [How to design with PSoC&trade; 6 MCU - KBA223067](https://community.infineon.com/docs/DOC-14644) in the Infineon Developer community.


## Document history


Document title: *CE227251* - *PSoC&trade; 6 MCU: CSD analog to digital converter (ADC)*

 Version | Description of change
 ------- | ---------------------
 1.0.0   | New code example
 1.1.0   | Added support for CY8CPROTO-062S3-4343W, CYW9P62S1-43438EVB-01, and CYW9P62S1-43012EVB-01 kits. <br> Updated to support ModusToolbox&trade; software v2.1<br> Minor formatting changes to code.
 2.0.0   | Major update to support ModusToolbox&trade; software v2.2, added support for new kits.<br> This version is not backward compatible with ModusToolbox&trade; software v2.1.
 2.1.0   | Updated to support ModusToolbox&trade; software v2.3.<br /> Added support for CY8CKIT-062S4.
 2.2.0   | Added support for CY8CEVAL-062S2 and CY8CEVAL-062S2-LAI-4373M2.
 3.0.0   | Major update to support ModusToolbox&trade; v3.0 and BSPs v4.X. This version is not backward compatible with previous versions of ModusToolbox&trade;.
 3.1.0   | Added support for CY8CEVAL-062S2-MUR-43439M2, CY8CPROTO-064B0S3, and CY8CPROTO-064S1-SB.
 3.2.0   | Updated to support ModusToolbox&trade; v3.1 and added support for CY8CPROTO-062S2-43439, CY8CEVAL-062S2-LAI-43439M2, CY8CEVAL-062S2-MUR-4373M2, CY8CEVAL-062S2-MUR-4373EM2
<br />



All referenced product or service names and trademarks are the property of their respective owners.

The Bluetooth&reg; word mark and logos are registered trademarks owned by Bluetooth SIG, Inc., and any use of such marks by Infineon is under license.


---------------------------------------------------------

© Cypress Semiconductor Corporation, 2020-2024. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates ("Cypress").  This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide.  Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights.  If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress's patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products.  Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br>
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  No computing device can be absolutely secure.  Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach").  Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach.  In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes.  It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product.  "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage.  Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices.  "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness.  Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress's published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br>
Cypress, the Cypress logo, and combinations thereof, ModusToolbox, PSoC, CAPSENSE, EZ-USB, F-RAM, and TRAVEO are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit www.infineon.com. Other names and brands may be claimed as property of their respective owners.
