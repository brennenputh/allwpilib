package edu.wpi.first.wpilibj.simulation.ds;

import org.gazebosim.transport.Node;

public class Main {
	public static void main(String args[]) {
		Node node = new Node("frc");
		try {
			node.waitForConnection();
		} catch (Throwable thr) {
			System.err.println("Could not connect to Gazebo.");
			thr.printStackTrace();
			System.exit(1);
			return;
		}

		JoystickProvider provider = new JoystickProvider();
		DS ds = new DS(provider);
		ds.advertise(node);

		while (true) {
			ds.publish();
			for (int i = 0; i < provider.getJoysticks().size(); i++) {
				ISimJoystick joystick = provider.getJoysticks().get(i);
				joystick.advertise(node, i+1);
				joystick.publish();
			}
			
			try {
				Thread.sleep(19);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
