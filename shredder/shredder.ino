void turnOnMotor() {
	if (millis() - timeOfLastPull >= debounce && digitalRead(2)) {
		timeOfLastPull = millis();
		digitalWrite(enginePin, HIGH);
	}
	
	if (millis() - lastTimeAskingEngine > engineAskTime && analogRead(A0) < idleLevel) {
		lastTimeAskingEngine = millis();
		digitalWrite(enginePin, LOW);
?		isForward = true;		
	}
	
	if (millis() - blockedTime > turnBackwardInterval && analogRead(A0) < shortCurcuitLevel) {
		blockedTime = millis();
		digitalWrite(enginePin, LOW);
		digitalWrite(relePin, HIGH);
		timeWhenRelayChanged = millis();
		isForward = false;
		if (millis() - timeWhenRelayChanged > turnRelayInterval && analogRead(A0) ){
			digitalWrite(enginePin, HIGH);
		}
	}
	
	if (millis() - unblockedTime > turnBackwardInterval && analogRead(A0) < idleLevel && isForward != true) {
		unblockedTime = millis();
		digitalWrite(enginePin, LOW);
		digitalWrite(relePin, LOW);
	}
}

