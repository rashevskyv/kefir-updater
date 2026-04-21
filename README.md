# Kefir-updater

<p align="center">
<img src = "https://user-images.githubusercontent.com/18294541/119040795-8880cf80-b9be-11eb-88bd-6dac1d24ebe6.jpg"\><br>
</p>

A Nintendo Switch homebrew app to download and update Kefir, FWs and cheat codes. Based on [AiO-switch-updater](https://github.com/HamletDuFromage/aio-switch-updater) by [HamletDuFromage](https://github.com/HamletDuFromage)

## How to install
Copy the `kefir-updater.nro` directory to `/switch/kefir-updater` on your sdcard.

## Description of the features
### ⬦ Update Kefir
- Download the [Kefir](https://github.com/rashevskyv/kefir). After downloading the CFW archive, the program will extract it and launch [TegraExplorer](https://github.com/suchmememanyskill/TegraExplorer/releases/) for installing CFW in a proper way

### ⬦ Download firmwares
- Download firmare files to `/firmware` that can then be installed using DayBreak.

### ⬦ Download cheats
- Downloads and extracts daily-updated cheat code. The program will only extract cheat codes for the games you own. By default, this homebrew will overwrite the existing cheats. If you have your own cheat files that you'd like to keep as is, you can turn off cheat updates for specific titles in `Tools->Cheat Menu`.
- Since v2.0.0, aio-switch-updater can also download cheat sheets from [`CheatSlips.com`](https://www.cheatslips.com/). 

## Extras (in the `Tools` tab)
- View which of your games got cheat codes from the app.
- Launch the Switch's web browser.

## Screenshots
![2021052023004100](https://user-images.githubusercontent.com/18294541/119041468-5754cf00-b9bf-11eb-9b98-9583f11445ed.jpg)
![2021052023004600](https://user-images.githubusercontent.com/18294541/119041470-57ed6580-b9bf-11eb-80ce-05649d640432.jpg)
![2021052023004800](https://user-images.githubusercontent.com/18294541/119041471-5885fc00-b9bf-11eb-8c9a-0944bc54afb3.jpg)
![2021052023005100](https://user-images.githubusercontent.com/18294541/119041472-5885fc00-b9bf-11eb-93bb-9105c7441132.jpg)
![2021052023005400](https://user-images.githubusercontent.com/18294541/119041473-591e9280-b9bf-11eb-82bc-bbf3364ca9a0.jpg)
![2021052023005500](https://user-images.githubusercontent.com/18294541/119041474-591e9280-b9bf-11eb-8c0e-f668505cd6ce.jpg)
![2021052023010100](https://user-images.githubusercontent.com/18294541/119041476-591e9280-b9bf-11eb-85e3-451d940bbd0c.jpg)

## Build
You need to have installed devkitPro and devkitARM in order to compile this project.

Install the required dependencies:
```bash
$ sudo (dkp-)pacman -Sy
```
```bash
$ sudo (dkp-)pacman -S  switch-glfw \
                        switch-curl \
                        switch-glm \
                        switch-mbedtls \
                        switch-glad \
                        switch-zlib
```
Use [`switch-ex-curl`](https://github.com/eXhumer/switch-ex-curl) instead of `switch-curl` to use this app with an invalid SSL certificate.

Use portlibs and build with libnx provided in this repository

Clone the repository
```bash
$ git clone --recursive https://github.com/HamletDuFromage/aio-switch-updater
$ cd aio-switch-updater
```

Compile 
```bash
$ cd aiosu-forwarder
$ make
$ cd ..
$ make
```

## Disclaimer
I do not own, host nor distribute any of the files that can be downloaded with this homebrew tool. At the owner's request, I will immediately remove the ability to download any problematic file.

## Special thanks
- [natinusala](https://github.com/natinusala) for the Borealis library.
- [tiansongyu](https://github.com/tiansongyu) for bringing support for multi-language and for his Chinese translation.
- [yyoossk](https://github.com/yyoossk) for the Japanese locale.
- [sergiou87](https://github.com/sergiou87) for the Spanish locale.
- [pedruhb](https://github.com/pedruhb) for the Brazilian locale.
- [AD2076](https://github.com/AD2076) for the Italian locale.
- [qazrfv1234](https://github.com/qazrfv1234) for the Traditional Chinese locale.
- [Team Neptune](https://github.com/Team-Neptune) whose rcm code I used.
- [fennectech](https://github.com/fennectech) for helping test the app and providing suggestions.
- Iliak for cheatslips.com.

## Donate to kefir's dev
### Paypal
[![PayPal](https://github.com/rashevskyv/kefir/assets/18294541/5e8a41b1-a15e-4e2c-a1fc-9230379ca1fa)](https://www.paypal.com/donate/?hosted_button_id=S5BLF972J8G92)

### Банка monobank
[![mono](https://github.com/user-attachments/assets/adc1d908-c511-4e03-8d63-f0370a7752bd)](https://send.monobank.ua/jar/9PwYEXHYbs)

## Donate for support Ukraine
### 🇺🇦 UKRAINE NEEDS YOUR HELP NOW!
>
> I'm the creator of this project and I'm Ukrainian.
>
> **My country, Ukraine, [is being invaded by the Russian Federation, right now](https://www.bbc.com/news/world-europe-60504334)**. I've fled Ivano-Frankivs'k and now I'm safe with my family in the western part of Ukraine. At least for now.
> Russia is hitting target all over my country by ballistic missiles.
>
> **Please, save me and help to save my country!**
>
> Ukrainian National Bank opened [an account to Raise Funds for Ukraine’s Armed Forces](https://bank.gov.ua/en/news/all/natsionalniy-bank-vidkriv-spetsrahunok-dlya-zboru-koshtiv-na-potrebi-armiyi):
>
> ```
> SWIFT Code NBU: NBUA UA UX
> JP MORGAN CHASE BANK, New York
> SWIFT Code: CHASUS33
> Account: 400807238
> 383 Madison Avenue, New York, NY 10179, USA
> IBAN: UA843000010000000047330992708
> ```
> 
> [Come Back and Alive found (savelife.in.ua)](https://savelife.in.ua/)
> 
> ```
> BITCOIN
> bc1qkd5az2ml7dk5j5h672yhxmhmxe9tuf97j39fm6
> 
> ETHEREUM (eth, usdt, usdc)
> 0xa1b1bbB8070Df2450810b8eB2425D543cfCeF79b
> 0x93Bda139023d582C19D70F55561f232D3CA6a54c
> 
> TRC20 (tether)
> TX9aNri16bSxVYi6oMnKDj5RMKAMBXWzon
> 
> Solana (sol)
> 8icxpGYCoR8SRKqLYsSarcAjBjBPuXAuHkeJjJx5ju7a
> ```
>
> You can also donate to [charity supporting Ukrainian army](https://savelife.in.ua/en/donate/).
>
> **THANK YOU!**
