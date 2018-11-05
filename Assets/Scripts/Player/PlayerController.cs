using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(PlayerMotor))]
public class PlayerController : MonoBehaviour {

	[SerializeField]
	private float mSpeed = 5.0f;
	[SerializeField]
	private float mMouseSensitivity = 3.0f;
	private PlayerMotor mMotor;

	void Start () {
		this.mMotor = GetComponent<PlayerMotor>();
	}
	
	void Update () {
		// Calculate movement velocit as a 3D vector for keyboard controls
		float xMov = Input.GetAxisRaw("Horizontal");
		float zMov = Input.GetAxisRaw("Vertical");

		Vector3 movHorizontal = transform.right * xMov;
		Vector3 movVertical = transform.forward * zMov;

		// Calculate final movement vector
		Vector3 finalVel = (movHorizontal + movVertical).normalized * this.mSpeed;

		// Apply movement vector
		mMotor.Move(finalVel);

		// Calculate rotation as a 3D vector for mouse controls
		float yRot = Input.GetAxisRaw("Mouse X");
		// Calculate final rotation vector
		Vector3 rot = new Vector3(0f, yRot, 0f) * mMouseSensitivity;
		// Apply rotation vector
		mMotor.Rotate(rot);

		float xRot = Input.GetAxisRaw("Mouse Y");
		float camRot = xRot * mMouseSensitivity;
		
		mMotor.RotateCamera(camRot);
	}
}
