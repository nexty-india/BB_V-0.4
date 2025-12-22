SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Git\cmd;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\IVI Foundation\VISA\Win64\Bin\;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin;C:\Program Files\dotnet\;C;C:\YDC\RAMScopeVP\app;C:\Users\shashank.kapoor\AppData\Local\Programs\Python\Python312\Scripts\;C:\Users\shashank.kapoor\AppData\Local\Programs\Python\Python312\;C:\Users\shashank.kapoor\AppData\Local\Microsoft\WindowsApps;C:\Users\shashank.kapoor\AppData\Local\Programs\Microsoft VS Code\bin;C:\Users\shashank.kapoor\Infineon\LauncherService;C:\Program Files (x86)\SDCC\bin
SET CPU_TYPE=ARMCM0P
SET CPU_VENDOR=ARM
SET UV2_TARGET=A31M22x_FOC_1Shunt
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\motorapplicationlayer.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\motordriverlayer_a31m22x.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_system.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_adc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_mpwm.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_pcu.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_scu.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_spi.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_timer.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_uart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_wdt.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_cfmc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_initclock.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\a31m22x_dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\out\parameter.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\out\a31m22x_startup_arm._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\out\A31M22x_FOC_1Shunt.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\out\A31M22x_FOC_1Shunt.axf" --i32combined --output ".\out\A31M22x_FOC_1Shunt.hex"
