# Communicate over Sigfox with STM32L MCU and S2LP

This project is a demo project on how to configure a STM32L053R8 board with a S2LP StMicroelectronic solution for transmitting over Sigfox Network.

The project is used as a documentation for supporting a blog post. Check this blog post to understand how to use it.
See here : https://www.disk91.com/?p=3388

### Step 1
* A led is blinking - see Tag/Release STEP1

### Step 2
* Send a Sigfox Frame - see Tag/Release STEP2

### Step 3
* Send an encrypted Sigfox Frame with AES + SPECK32 encryption - see Tag/Release STEP3

### Step 4
* Send a Sigfox encrypted Frame using the Sigfox AES-CTR feature - see Tag/Release STEP4

The project have different tag for the different step of realization.

# Installation

Clone this repository and open it with AC6 environment [See here on how to install it](https://www.disk91.com/2018/technology/hardware/getting-started-with-nucleo32-stm32l031/)

Clone the [STM32 ItSdk repository](https://github.com/disk91/stm32-it-sdk) in the Project root directory to add the needed sdk dependencies.

# CubeMx configuration

The Cube MX configuration is provided in the project.
Some important key point for custom confguration
- EXTI interrupt needs to be activated
- S2LP/GPIO3 -> PC0 have a pull-up 


# License

This code and ItSdk are under GPLv3. You can use it freely, you can modify, redistribute but *you must* to publish your source code. Other licenses can be obtained by contacting me on [disk91.com](https://www.disk91.com)

