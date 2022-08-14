# LINE FOLLOWER ROBOT.

![Project image](/line-follower-robot/line-follower/images/project-image.png)

## Credits

All credits goes to a website [https://create.arduino.cc/projecthub](https://create.arduino.cc/projecthub)
refer from their original post [Line Follower Robot](https://create.arduino.cc/projecthub/saher-iqbal/line-follower-robot-36516b)

## What you will need.

| NAME                                         | QTY |
| -------------------------------------------- | --- |
| Arduino UNO board.                           | 1   |
| Digilent IR Range Sensor                     | 2   |
| SparkFun Dual H-Bridge Motor drivers L298    | 1   |
| DC Motor, 12V                                | 2   |
| LCD Display                                  | 1   |
| Power Bank                                   | 1   |
| Male to Male and Make to Female jumper wires | 20  |
| Breadboard                                   | 1   |

## Understanding the circuit and its components

### Component 1 : The IR Proximity Sensor

> The concept of working of line follower robots is based on the principles of light. White color reflects almost all the light falling on it, whereas balck light absorbs most of the light. In case of a line follower robot we use IR transmitters and receivers also called **photodiodes**. They are used for sending and receiving light. IR transmit infrared lights. When infrared rays falls on white surface, it's reflected back and catched by photodiodes which generate some voltage changes. When IR light falls on a black surface, light is absorbed by the black surface and no rays are reflected back, thus photodiode does not receive any light or rays.\
> Here in this arduino line follower robot when sensor senses white surface then Arduino gets 1, i.e. HIGH as input and when senses black surface the Arduino gets 0, i.e. LOW as input.
> <br>
> <p align="center"><img src="./line-follower/images/IR-proximity-sensors.avif" alt="IR Proximity Sensors"/></p>
> 
> #### Circuit connection of IR Sensors
>
> - The IR sensor is a 3 three wired sensor, in which the brown and the black wire are used to connect the sensor to the power supply, whereas, the red wire is connected to the load, or Arduino, in our circuit.
> - The load wires of the IR sensors are connected to pin 8, 9 and 10 as shown in the schematic

### Component 2 : L298N H-Bridge Motor Driver

> The H-Bridge Motor Drivers L298N is used to drive DC motors as they require much more current that the arduino can provide.\
> The L298N motor controller follows the H-bridge configuration, which is handy when controlling the direction of rotation of a DC motor. The other benefit of using an H-bridge is that we can provide a separate power supply to the motors. This is very significant especially when using an Arduino board where the 5V power source is simply not enough for two DC motors.\
> We have Motor A and Motor B terminals. These connect to the microcontroller. Motor A connects to terminals 1 and 2 while Motor B connects to terminals 3 and 4.
> <br>
> <p align="center"><img src="./line-follower/images/L298N-H-bridge-Motor-Driver.avif" alt="L298N H-Bridge Motor Driver"></p>
> If we want the left motor to rotate in one direction, we apply a high pulse to IN1 and a low pulse to IN2. To reverse the direction, reverse the pulses to IN1 and IN2. The same applies to the right motor.\
> If we want the left motor to rotate in one direction, we apply a high pulse to IN1 and a low pulse to IN2. To reverse the direction, reverse the pulses to IN1 and IN2. The same applies to the right motor.\
> Speed control is also possible with the L298N motor driver. All we need is feed PWM ( Pulse Width Modulation) signals to the motor enable pins. The speed of the motor will vary according to the width of the pulses. The wider the pulses, the faster the motor rotates. In Arduino this can be done using analogWrite(pinNumber, duration). Pins on Arduino with ‘~’ support PWM.


> | IN1 | IN2 | IN3 | IN4 | Directions |
> | --- | --- | --- | --- | ---------- |
> | 0 | 0 | 0 | 0 | Stop |
> | 1 | 0 | 1 | 0 | Forward |
> | 0 | 1 | 0 | 1 | Reverse |
> | 1 | 0 | 0 | 1 | Left |
> | 0 | 1 | 1 | 0 | Right |
> #### Circuit connection of L298N H-Bridge Motor Driver
> - Motor A wires are connected to motor terminal 1 and 2 of L298N, whereas Motor B wires are connected to motor terminal 3 and 4. IN1, IN2, IN3 and IN4 are connected to pin 2, 3, 4, 7 respectively.
> - Now, Motor A and Motor B Enable should be connected to terminals on arduino which have ~ sign, so that speed of these motors can be controlled using PWM. Here, they have been connected to pin 5 and 6.
> - Other connections are clear from the schematic.

## Schematics

![Line follower robot schematics](/line-follower-robot/line-follower/images/line-follower-robot-schematics.png)

## Procedures

**Step 1:** Connect the circuit as shown in the schematic

**Step 2:** Use the Arduino IDE to write your own code.

**Step 3:** Upload your code to the Arduino and connect it to the batteries or you can even use a power bank to run the Arduino.

**Step 4:** Test it on a black path.

## Video

[![Watch the of line follower robot video here!](/line-follower-robot/line-follower/images/project-image.png)](https://youtu.be/UrWKS8XJh2Y)
