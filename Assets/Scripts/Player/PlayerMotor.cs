using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class PlayerMotor : MonoBehaviour {

	[SerializeField]
	private Camera mCam;
	private Vector3 mVelocity = Vector3.zero;
	private Vector3 mRotation = Vector3.zero;
	private float mCamRot = 0.0f;
	private float mCurrCamRot = 0.0f;
	private Rigidbody mRigidbody;

	[SerializeField]
	private float mCamRotMax = 85.0f;
	
	void Start () {
		mRigidbody = GetComponent<Rigidbody>();
	}
	
	void FixedUpdate() {
		ExecuteMovement();
		ExecuteRotation();
	}

	/* PRIVATE FUNCTIONS */
	private void ExecuteMovement() {
		if (mVelocity != Vector3.zero) {
			mRigidbody.MovePosition(mRigidbody.position + mVelocity * Time.fixedDeltaTime);
		}
	}

	private void ExecuteRotation() {
		mRigidbody.MoveRotation(mRigidbody.rotation * Quaternion.Euler(mRotation));

		if (mCam != null) {
			mCurrCamRot -= mCamRot;
			mCurrCamRot = Mathf.Clamp(mCurrCamRot, -mCamRotMax, mCamRotMax);

			mCam.transform.localEulerAngles = new Vector3(mCurrCamRot, 0f, 0f);
		}
	}

	/* PUBLIC FUNCTIONS */
	public void Move(Vector3 velocity) {
		this.mVelocity = velocity;
	}

	public void Rotate(Vector3 rotation) {
		this.mRotation = rotation;
	}

	public void RotateCamera(float camRotation) {
		this.mCamRot = camRotation;
	}
}
