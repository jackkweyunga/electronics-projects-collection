# MOBILE MONEY TRANSACTIONS LOGGER (M-Pesa/Tigopesa/Airtel Money)

## Documentation

- Materials

| Name | qty |
|---|--|
| Arduino uno | 1 |
| GSM 900A module | 1 |
| Connecting wires | 1 |
| mobile SIM CARD `(vodacom/tigo/airtel)` | 1 |
| 5V Power adapter | 1 |
| Bread Board | 1 |

![materials](https://content.instructables.com/ORIG/FZ3/CVEZ/IV0AGOTN/FZ3CVEZIV0AGOTN.jpg?auto=webp&frame=1&width=525&height=1024&fit=bounds&md=c05df05ebf9fb629036e429b392a372c)

- Specifications

        GMS 900A 
        input voltage : 5 Volts 
        input current : 2 Amps


### Connections Steps

NOTE: Pin 7 and 8 in arduino are reserved as RX (Receiving) and TX (Transimiting) pins.

1. Look for a SIM slot in your arduino GSM module and insert your SIM card

2. Power your GSM module by connecting a 5V power supply to it via its adjucent power pins (VCC, GND).

    | see below   |
    | :---------: |
    | ![power to gsm 900A](https://content.instructables.com/ORIG/F33/VHLR/IV0A5DU9/F33VHLRIV0A5DU9.jpg?auto=webp&frame=1&width=432&height=1024&fit=bounds&md=f72f094d51a324345eb3bbff5c014524) |

3. The GSM module will boot Wait for some time until you see the fast blinking LED starts blinking slowly.

4. Locate pins 5VR, 5VT and 2 GND(s). Then connect them as follows :

        5VR         -> Arduino Pin 8 (TX) 
        5VR         -> Arduino Pin 8 (TX) 
        all GND(S)  -> Arduino GND 

5. Power up your arduino by connecting it to your computer.
    | see below   |
    | :---------: |
    | ![power to gsm 900A](https://content.instructables.com/ORIG/FDI/DPRE/IV0A5DSN/FDIDPREIV0A5DSN.jpg?auto=webp&frame=1&width=768&height=1024&fit=bounds&md=ed3c85a7a5b5fce3325781b7a867ac04) |

view arduino code here -> [ARDUINO CODE](./sms-logger/sms-logger.ino)
