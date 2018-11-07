using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(PlayerMotor))]
public class PlayerController : MonoBehaviour {

	private float mSpeed = 5.0f;
	private float mMouseSensitivity = 3.0f;
	private PlayerMotor mMotor;
	public bool mIsJumping = false;
	public bool mIsDoubleJumpAvailable = true;

	void Start () {
		this.mMotor = GetComponent<PlayerMotor>();
	}
	
	void Update () {
		CheckState();
		GetKeyboardInput();
		GetMouseInput();
	}

	/* PRIVATE FUNCTIONS */
	private void CheckState() {
		if (mMotor.mIsGrounded == true) {
			mIsJumping = false;
			mIsDoubleJumpAvailable = true;
		}
	}
	private void GetKeyboardInput() {
		// Calculate movement velocit as a 3D vector for keyboard controls
		float xMov = Input.GetAxisRaw("Horizontal");
		float zMov = Input.GetAxisRaw("Vertical");

		Vector3 movHorizontal = transform.right * xMov;
		Vector3 movVertical = transform.forward * zMov;

		// Calculate final movement vector
		Vector3 finalVel = (movHorizontal + movVertical).normalized * this.mSpeed;

		// Apply movement vector
		mMotor.Move(finalVel);

		// Check if the player pressed the spacebar
		if (Input.GetKeyDown(KeyCode.Space)) {
			if (mIsJumping == false) {
				mMotor.Jump();
				mIsJumping = true;
			}
			else if (mIsJumping == true && mIsDoubleJumpAvailable == true && mMotor.mIsGrounded == false) {
				mMotor.Jump();
				mIsDoubleJumpAvailable = false;
			}
		}		
	}

	private void GetMouseInput() {
		// Calculate rotation as a 3D vector for mouse controls
		float yRot = Input.GetAxisRaw("Mouse X");
		// Calculate final rotation vector
		Vector3 rot = new Vector3(0f, yRot, 0f) * mMouseSensitivity;
		// Apply rotation vector
		mMotor.Rotate(rot);

		// Calculate and apply camera rotation
		float xRot = Input.GetAxisRaw("Mouse Y");
		float camRot = xRot * mMouseSensitivity;
		mMotor.RotateCamera(camRot);
	}
}
