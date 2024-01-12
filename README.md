# Refresh-o-Matic:

Authors: Volodymyr Semenov, Vasilisa Ignatova
                                                                                                       
![robot_img](images/labeled_robot.png)

## Project Overview
Refresh-o-Matic is a drink dispensing system created with the goal of automating the process of filling and refilling drinks at a social event. The system seeks to accurately identify empty and partially filled cups given to the system and fill those cups while operating on a first-come-first-serve basis. 

## BOM
- [Arduino](https://store.arduino.cc/products/uno-r4-wifi)
- [Strain Gauges + HX711 Amplifier](https://www.amazon.com/dp/B07BGRDKG5?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- Breadboard
- Wires
- [Perilastic Pump](https://www.amazon.com/gp/product/B01IUVHB8E/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
- [NEMA17 Stepper Motor](https://www.amazon.com/gp/product/B0B38GX54H/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&th=1)
- [A4988 Stepper Motor Driver](https://www.amazon.com/HiLetgo-Stepstick-Stepper-Printer-Compatible/dp/B07BND65C8/ref=sr_1_18?crid=191ZJP7PP2AXW&keywords=pololu+A4988&s=industrial&sprefix=pololu+a4988%2Cindustrial%2C63&sr=1-18)
- [12v PSU](https://www.amazon.com/gp/product/B091XSVV1Y/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1)
- Reservoir (2 Liter Bottle)
- [Belt for axis](https://www.amazon.com/dp/B08R93QQ8Z?ref=ppx_yo2ov_dt_b_product_details&th=1)
- [12V Relays](https://www.amazon.com/dp/B08PNHHC65?ref=ppx_yo2ov_dt_b_product_details&th=1)
- Tubing
- 10k+ Ohm Resistors
- 100 uF Capacitor
- 2-Pin Push Buttons

## Operation:

1) Prior to activating the system, the stepper has to be manually put at the zero position. To calibrate the stepper motor, manually move the belt connector to the middle of the backboard/at the position of the middle cup coaster.

2) Plug the 12V adapter attached to the back of the robot into a power supply to activate the system.

3) Place an empty or partially filled cup on one of the locations marked circular coasters located on the body of the robot.

The system will sense the presence of the cup as well as the amount of liquid located in the cup, and add it to a queue of cups that are ready to be filled.

Once all the earlier-placed cups are filled, the pump will travel to your cup and your drink will be poured, after which you can remove the cup from its position.

4) To deactivate the system, unplug the 12V adapter from the power supply.

## Notes:

- You may remove the cup prematurely and the pump will cease its operation.

- An **emergency stop button** is located on the top right side of the robot backboard should you need to stop the system for any reason.

- The belt system should always be kept clear of obstructions for successful operation.
- The cup coasters/weight sensors should be kept clear of obstructions other than cups, for successful operation.

- The current system is designated to work **only** with standardized red solo cups, but the system code can be adjusted to support addition-sized cups and different desired pour amounts.

## Future Work:

- A more efficient version of our system would include a pump capable of pumping water at a much faster rate than the current peristaltic pump used. 

- Add a second stabilizing rod for the belt connector to keep that part from rotating.
