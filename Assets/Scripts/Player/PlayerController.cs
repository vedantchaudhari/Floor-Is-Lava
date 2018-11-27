using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
[RequireComponent(typeof(PlayerMotor))]
public class PlayerController : MonoBehaviour
{

    private float mSpeed = 5.0f;
    private float mMouseSensitivity = 3.0f;
    private PlayerMotor mMotor;
    public bool mIsJumping = false;
    public bool mIsDoubleJumpAvailable = true;
    public GameObject loseScreen;

    public GameObject pushCollider;
    
    bool beginPush = false;
    bool endPush = false;
    bool canMove = true;

   
    public GameObject handAnchor;
    public GameObject handAnchorPush;
    public GameObject hand;

    void Start()
    {
        this.mMotor = GetComponent<PlayerMotor>();
        Cursor.visible = false;
        pushCollider.SetActive(false);
    }

    void Update()
    {
        CheckState();
        if (canMove)
        {
            GetKeyboardInput();
            GetMouseInput();
        }
        if (beginPush)
            pushHand();
        else if (endPush)
            pullHand();
        else
            pushCollider.SetActive(false);
    }

    /* PRIVATE FUNCTIONS */
    private void CheckState()
    {
        if (mMotor.mIsGrounded == true)
        {

            mIsJumping = false;
            mIsDoubleJumpAvailable = true;
        }
        if (mMotor.MIsDead == true)
        {
            canMove = false;
            loseScreen.SetActive(true);
        }
    }
    private void GetKeyboardInput()
    {
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
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (mIsJumping == false)
            {
                mMotor.Jump();
                mIsJumping = true;
            }
            else if (mIsJumping == true && mIsDoubleJumpAvailable == true && mMotor.mIsGrounded == false)
            {
                mMotor.Jump();
                mIsDoubleJumpAvailable = false;
            }
        }
    }

    private void GetMouseInput()
    {
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


        if(Input.GetMouseButton(0) && !beginPush && !endPush)
        {
            pushCollider.SetActive(true);
            beginPush = true;
        }

    }

    private void pushHand()
    {

        hand.transform.position = Vector3.Lerp(hand.transform.position, handAnchorPush.transform.position,Time.deltaTime * 7);
        if ((hand.transform.position - handAnchorPush.transform.position).magnitude < 0.05)
        {
            hand.transform.position = handAnchorPush.transform.position;
            beginPush = false;
            endPush = true;
        }
    }
    private void pullHand()
    {
        hand.transform.position = Vector3.Lerp(hand.transform.position, handAnchor.transform.position, Time.deltaTime * 7);
        if ((hand.transform.position - handAnchor.transform.position).magnitude < 0.05)
        {
            endPush = false;
            hand.transform.position = handAnchor.transform.position;
        }
        
    }
}
