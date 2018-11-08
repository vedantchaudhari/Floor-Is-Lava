using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class PlayerMotor : MonoBehaviour {

	public Camera mCam;
	private Vector3 mVelocity = Vector3.zero;
	private Vector3 mRotation = Vector3.zero;
	private float mCamRot = 0.0f;
	private float mCurrCamRot = 0.0f;
	private Rigidbody mRigidbody;
	private float mCamRotMax = 90.0f;
	
	public bool mIsGrounded = true;
    private bool mIsDead = false;
    private float jumpModifier = 15.0f;

    public bool MIsDead
    {
        get
        {
            return mIsDead;
        }

        set
        {
            mIsDead = value;
        }
    }

    void Start () {
		mRigidbody = GetComponent<Rigidbody>();
	}
	
	void FixedUpdate() {
		ExecuteMovement();
		ExecuteRotation();
	}

	void OnCollisionEnter(Collision collision) {
		if (collision.gameObject.tag == "Platform") {
			mIsGrounded = true;
		}
        if (collision.gameObject.tag == "Lava")
        {
            MIsDead = true;
        }
    }

	void OnCollisionExit(Collision collision) {
		if (collision.gameObject.tag == "Platform") {
			mIsGrounded = false;	
		}
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

	public void Jump() {
		mRigidbody.AddForce(Vector2.up * jumpModifier, ForceMode.Impulse);
	}
}
