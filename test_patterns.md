# Test Patterns

### Test 1: Emergency stop button stops Stepper Motor

Expected Behavior: Pump shuts off when the emergency stop button is pressed by the user

Result: PASS

### Test 2: Emergency stop button stops Pump

Expected Behavior: Stepper shuts off when the emergency stop button is pressed by the user.

Result: PASS

### Test 3: Cup queue maintained

Expected Behavior: If the cups are placed in sensor order 3, 1, 2 then the motor will travel to those locations in that order.

Result: PASS

### Test 4: Cup queue maintained when a cup is being filled

Expected Behavior: If new cups are added when a cup is already being filled, those cups would still be placed into the cup queue in the appropriate order.

Result: PASS

### Test 5: Cup queue maintained when stepper is moving

Expected Behavior: If new cups are added when the stepper motor is active,  those cups would still be placed into the cup queue in the appropriate order.

Result: PASS

### Test 6: Cup removed while pump is active

Expected Behavior: If a cup is suddenly removed from the weight sensor while it is being filled, then the pump should stop.

Result: PASS

### Test 7: Full cup placed on pump

Expected Behavior: If an already full cup is placed on a weight sensor, the pump should remain inactive.

Result: PASS

### Test 8: Full cup placed motor

Expected Behavior: If an already full cup is placed on a weight sensor, the motor should not travel to its location.

Result: PASS

### Test 9: Sensor 1 location

Expected Behavior: When an empty cup is placed on sensor 1, the motor travels to the sensor 1 location.

Result: PASS

### Test 10: Sensor 2 location

Expected Behavior: When an empty cup is placed on sensor 2, the motor travels to the sensor 2 location.

Result: PASS

### Test 11: Sensor 3 location

Expected Behavior: When an empty cup is placed on sensor 3, the motor travels to the sensor 3 location.

Result: PASS

### Test 12: Full cup

Expected Behavior: When a cup reaches a weight of 210g, the cup is perceived as full and the pumps shuts down.

Result: PASS

### Test 13: No cup

Expected Behavior: If there is no cup at a location by the time the motor reaches it, then the pump will remain inactive.

Result: PASS
