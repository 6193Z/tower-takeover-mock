#include "main.h"

pros::Controller control(pros::E_CONTROLLER_MASTER);

pros::Motor FLDrive(18);
pros::Motor FRDrive(8);
pros::Motor BLDrive(19);
pros::Motor BRDrive(9);

pros::Motor leftRoller(20);
pros::Motor rightRoller(10);
pros::Motor armMotor(17);
pros::Motor tilter(7);

pros::ADIButton limitSwitch('a');

//////////////////////////////////////////

void opcontrol()
{
	tilter.set_encoder_units(MOTOR_ENCODER_DEGREES);

	while (true)
	{
		int joyLY = control.get_analog(ANALOG_LEFT_Y);
		int joyRX = control.get_analog(ANALOG_RIGHT_X);

		bool btnR1 = control.get_digital(DIGITAL_R1);
		bool btnR2 = control.get_digital(DIGITAL_R2);
		bool btnA = control.get_digital(DIGITAL_A);
		bool btnB = control.get_digital(DIGITAL_B);
		bool btnX = control.get_digital(DIGITAL_X);
		bool btnR1 = control.get_digital(DIGITAL_R1);
		bool btnL1 = control.get_digital(DIGITAL_L1);
		bool btnL2 = control.get_digital(DIGITAL_L2);

		bool degReset = limitSwitch.get_value();

		leftRoller.set_brake_mode(MOTOR_BRAKE_BRAKE);
		rightRoller.set_brake_mode(MOTOR_BRAKE_BRAKE);
		armMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
		tilter.set_brake_mode(MOTOR_BRAKE_HOLD);

		//Arcade drive
		FLDrive.move(joyLY + joyRX);
		FRDrive.move(joyLY - joyRX);
		BLDrive.move(joyLY + joyRX);
		BRDrive.move(joyLY - joyRX);

		//Roller intake and outake
		if (btnR1)
		{
			leftRoller.move(127);
			rightRoller.move(-127);
		}
		else if (btnR2)
		{
			leftRoller.move(-127);
			rightRoller.move(127);
		}

		//Move arms up and down
		if (btnA)
		{
			armMotor.move(127);
		}
		else if (btnB)
		{
			armMotor.move(-127);
		}

		//Move tray titler up and down
		if (btnL1)
		{
			if (tilter.get_position() > 1000)
			{
				tilter.move(55);
			}
			else
			{
				tilter.move(127);
			}
		}
		else if (btnL2)
		{
			tilter.move(-127);
		}
		else if (btnX)
		{
			tilter.move(127);
		}

		if (degReset)
		{
			tilter.move_absolute(0, 60);
		}

		pros::delay(20);
	}
