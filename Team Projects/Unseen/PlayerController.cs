using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.Events;

public class PlayerController : MonoBehaviour
{
    public CharacterController controller;
    public Vector3 playerVelocity;
    public bool groundedPlayer;
    [SerializeField]
    private float originalSpeed;
    public float playerSpeed;
    public bool reducedSpeed;
    public float jumpHeight;
    public float gravityValue = -9.81f;
    [SerializeField] float rotatespeed;
    public Animator anim;
    public float animSpeed;
    [SerializeField] float groundlength;
    [SerializeField] float blendTreeMaxSpeed;
    public bool isFacingFoward;
    //private float revertPlayerSpeed;
    //[SerializeField] float speedReduce;

    public bool isPushing = false;
    public bool moveableObjectCollision;

    public bool controllable = true;
    public Vector3 move;
    int timesJumped = 0;
    [SerializeField]
    public bool canJump = true;

    //private Rigidbody rb;
    [SerializeField]
    private GameObject child = null;
    private Rigidbody childRB;

    // Player status checks
    public bool canInvisible = true;
    public bool haselevatorkey = true;
    public bool onGoo;
    public bool isParalyzed;
    public bool reset;
    public GameObject _playerCollision;


    //[SerializeField] bool isCrouched = false;

    public bool isCrouched;
    public bool cooldown;
    public bool canCrouch = true;
    [SerializeField] float crouchSpeed = 2f;
    [SerializeField] bool onLadder = false;
    [SerializeField] bool hasKey = false;

    //public Transform player;
    //public Transform respawnPoint;

    //stuff for invisibility
    public bool isInvisible;
    [SerializeField] Material visible;
    [SerializeField] Material invisible;
    [SerializeField] SkinnedMeshRenderer capsuleRenderer;

    public float invisUseAmount = 0.5f;
    //public int InvisLevel;

    // Interactables
    public bool doorInteract;
    public bool lockerInteract;
    public bool switchInteract;
    public bool TeleportInteract;
    public bool objectInteract;
    public bool hasObject;
    private float throwForce;
    public bool touchingPush;

    [SerializeField] ParticleSystem carryEffect;


    private void Start()
    {
        capsuleRenderer = GetComponentInChildren<SkinnedMeshRenderer>();
        playerSpeed = originalSpeed;
    }

    void Update()
    {

        //Debug.Log(anim.GetFloat("Speed"));
        RaycastHit hit;
        Ray bottomray = new Ray(transform.position + Vector3.down * 1f, transform.up * -1f);
        Ray topray = new Ray(transform.position, transform.up);
        Ray bottomray1 = new Ray(transform.position + Vector3.right * 0.35f, transform.up * -1f);
        Ray bottomray2 = new Ray(transform.position + Vector3.right * -0.35f, transform.up * -1f);
        Ray fowardray = new Ray(transform.position + Vector3.down * 0.4f, transform.forward);
        Debug.DrawRay(fowardray.origin, fowardray.direction * 3, Color.red);
        Debug.DrawRay(bottomray2.origin, bottomray2.direction * groundlength, Color.red);
        Debug.DrawRay(bottomray1.origin, bottomray1.direction * groundlength, Color.red);
        Debug.DrawRay(bottomray.origin, bottomray.direction * 1f, Color.red);

        if (Physics.Raycast(fowardray, out hit, 0.5f))
        {
            isFacingFoward = true;
            if (hit.collider.CompareTag("Pushable"))
            {
                touchingPush = true;
            }
            else
            {
                touchingPush = false;
            }
        }
        else
        {
            isFacingFoward = false;
            touchingPush = false;
        }

        //Debug.DrawRay(topray.origin, topray.direction * groundlength, Color.green);
        //Debug.DrawRay(bottomray1.origin, bottomray1.direction * groundlength, Color.green);
        //Debug.DrawRay(bottomray2.origin, bottomray2.direction * groundlength, Color.green);
        //Debug.DrawRay(bottomray.origin, bottomray.direction * groundlength, Color.green);

        if (controllable)
        {
            if (canInvisible)
            {
                //when button is pressed invis bar goes down
                if (!cooldown)
                {


                    if (Input.GetKeyDown(KeyCode.X) || Input.GetKeyDown(KeyCode.LeftShift))
                    {
                        BecomeInvisible();
                        cooldown = true;
                    }
                }

                //when button is released invisibility lifted
                if (Input.GetKeyUp(KeyCode.X) || Input.GetKeyUp(KeyCode.LeftShift))
                {
                    BecomeVisible();
                    if (cooldown)
                    {
                        StartCoroutine(ResetCoolDown());
                    }

                    GameManager.instance.invisBar.RegenBar();
                }

                if (GameManager.instance.invisBar.currInvis <= .25)
                {
                    BecomeVisible();

                    GameManager.instance.invisBar.RegenBar();
                }

            }
            else
            {
                // Called every single frame
                BecomeVisible();
            }

            //Checks to see if the player has touched the ground
            groundedPlayer = controller.isGrounded;
            if (groundedPlayer && playerVelocity.y < 0)
            {
                timesJumped = 0;
                //anim.SetBool("IsJump", false);

                playerVelocity.y = 0f;
            }
            //if ( Physics.Raycast(topray, out hit, groundlength) && controller.velocity.y >= 0)
            //{
            //}
            if (Physics.Raycast(bottomray, out hit, 1) || Physics.Raycast(bottomray1, out hit, groundlength) || Physics.Raycast(bottomray2, out hit, groundlength))
            {
               
                    groundedPlayer = true;
                    anim.SetBool("Falling?", false);
                    anim.SetBool("IsJump", false);
                
             
            }
            else
            {
                groundedPlayer = false;
                timesJumped++;
                anim.SetBool("Falling?", true);
                anim.SetBool("IsJump", true);
            }

            //Allows the player to move left and right and climb ladders if it doen't have a MoveableObject as child
            if (!onLadder && !isPushing)
            {
                move = new Vector3(Input.GetAxis("Horizontal"), 0, 0);
                if (move != Vector3.zero)
                {
                    //gameObject.transform.forward = move;
                    //if (!moveableObjectCollision)
                    //    transform.rotation = Quaternion.LookRotation(Vector3.RotateTowards(transform.forward, move, rotatespeed * Time.deltaTime, 0));
                    //anim.SetFloat("Speed", Mathf.Lerp(anim.GetFloat("Speed"), 1, animSpeed * Time.deltaTime));

                    if (!isPushing)
                    {
                        transform.rotation = Quaternion.LookRotation(Vector3.RotateTowards(transform.forward, move, rotatespeed * Time.deltaTime, 0));
                        anim.SetFloat("Speed", Mathf.Lerp(anim.GetFloat("Speed"), 1, animSpeed * Time.deltaTime));
                     
                        //Debug.Log(anim.GetFloat("Speed"));
                    }
                    else if (isPushing)
                    {
                        anim.SetFloat("Speed", Mathf.Lerp(anim.GetFloat("Speed"), 0.5f, animSpeed * Time.deltaTime));
                       
                        //Debug.Log(anim.GetFloat("Speed"));
                    }
                }
                else
                {
                    anim.SetFloat("Speed", Mathf.Lerp(anim.GetFloat("Speed"), 0, animSpeed * Time.deltaTime));
                    if (anim.GetFloat("Speed") <= 0.08f)
                    {
                        anim.SetFloat("Speed", 0);
                        //Debug.Log(anim.GetFloat("Speed"));
                    }
                }
            }
            else if (!isPushing)
            {
                move = new Vector3(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical"), 0);
                if (move != Vector3.zero)
                {
                    Vector3 temp = new Vector3(move.x, 0, 0);
                    gameObject.transform.forward = temp;
                    anim.SetBool("IsJump", false);
                    anim.SetBool("Falling?", false);
                    if (!isPushing)
                    {
                        anim.SetFloat("Speed", Mathf.Lerp(anim.GetFloat("Speed"), 1, animSpeed * Time.deltaTime));
                        //Debug.Log(anim.GetFloat("Speed"));
                    }
                    else if (isPushing)
                    {
                        anim.SetFloat("Speed", Mathf.Lerp(anim.GetFloat("Speed"), 0.5f, animSpeed * Time.deltaTime));
                        //Debug.Log(anim.GetFloat("Speed"));
                    }
                }
                else
                {
                    anim.SetBool("IsJump", false);
                    anim.SetBool("Falling?", false);
                    anim.SetFloat("Speed", Mathf.Lerp(anim.GetFloat("Speed"), 0, animSpeed * Time.deltaTime));
                }
            }

            if (controller.enabled)
            {
                controller.Move(move * Time.deltaTime * playerSpeed);

                PlayerJump();

                if (canCrouch)
                {
                    PlayerCrouch();
                }
            }
            if (Input.GetKeyDown(KeyCode.Z) || Input.GetKeyDown(KeyCode.E))
            {
                Interact();
            }

            // Grab/throw
            if (objectInteract)
            {
                if (!hasObject)
                {
                    if (Input.GetKeyDown(KeyCode.Z) || Input.GetKeyDown(KeyCode.E))
                    {
                        EventManager.instance.OnObjectInteract();
                        carryEffect.Play();
                    }
                    if (Input.GetKeyUp(KeyCode.Z) || Input.GetKeyUp(KeyCode.E))
                        hasObject = true;
                }
                else
                {
                    if (Input.GetKey(KeyCode.Z) || Input.GetKey(KeyCode.E))
                        throwForce += 120 * Time.deltaTime;
                    if (Input.GetKeyUp(KeyCode.Z) || Input.GetKeyUp(KeyCode.E))
                    {
                        //Debug.Log(throwForce);
                        if (throwForce > 120)
                            throwForce = 120;
                        else if (throwForce < 60)
                            throwForce = 60;
                        //Debug.Log(throwForce);
                        EventManager.instance.OnObjectInteract(throwForce);
                        carryEffect.Stop();
                        //hasObject = false;
                        throwForce = 0;
                    }
                }
            }
        }

        if (canInvisible && isPushing && !GameManager.instance.gameOver.activeInHierarchy)
        {
            //when button is pressed invis bar goes down
            if (!cooldown)
            {


                if (Input.GetKeyDown(KeyCode.X) || Input.GetKeyDown(KeyCode.LeftShift))
                {
                    BecomeInvisible();
                    cooldown = true;
                }
            }

            //when button is released invisibility lifted
            if (Input.GetKeyUp(KeyCode.X) || Input.GetKeyUp(KeyCode.LeftShift))
            {
                BecomeVisible();
                if (cooldown)
                {
                    StartCoroutine(ResetCoolDown());
                }

                GameManager.instance.invisBar.RegenBar();
            }

            if (GameManager.instance.invisBar.currInvis <= .25)
            {
                BecomeVisible();

                GameManager.instance.invisBar.RegenBar();
            }


        }
        else if(isPushing)
        {
            // Called every single frame
            BecomeVisible();
        }

        // Update() Interactions - Push
        // Can only push GameObjects with a Collider, a RigidBody and the Gravity.cs script
        if (touchingPush)
        {
            if (Input.GetKey(KeyCode.Z) || Input.GetKey(KeyCode.E))
            {

                PushOn();
            }
            else
            {
                // Executes but does nothing if Player doesnt have MoveableObject as Child
                PushOff();
            }
        }
        else
        {
            PushOff();
        }
    }

    private void LateUpdate()
    {
        if (GetOriginalSpeed() > GetPlayerSpeed())
            reducedSpeed = true;
        else if (GetOriginalSpeed() <= GetPlayerSpeed())
            reducedSpeed = false;

        //if (!isParalyzed)
        //{
        //    SetPlayerMaterial(visible);
        //}
    }

    ////Checks for player collision and activates conditions
    //private void OnTriggerEnter(Collider other)
    //{
    //    //PlayerLoss(other.gameObject);
    //}
    //private void OnTriggerExit(Collider other)
    //{
    //    isUnseen = true;
    //    onLadder = false;
    //}

    ////Controls what happens when player collides with an object
    //public void PlayerLoss()
    //{
    //   isUnseen = false;
    //   player.transform.position = respawnPoint.transform.position;
    //}

    //Allows the player to jump
    private void PlayerJump()
    {
        if (Input.GetButtonDown("Jump") && timesJumped == 0 && canJump)
        {
            timesJumped++;
            anim.SetBool("IsJump", true);
            if (onGoo)
                playerVelocity.y += Mathf.Sqrt(jumpHeight * -1.2f * gravityValue);
            else
                playerVelocity.y += Mathf.Sqrt(jumpHeight * -3.0f * gravityValue);
        }

        // Stops gravity when Player is on a ladder
        if (!onLadder)
        {
            playerVelocity.y += gravityValue * Time.deltaTime;
            controller.Move(playerVelocity * Time.deltaTime);
        }
    }

    //Allows to player to crouch 
    private void PlayerCrouch()
    {
        if (timesJumped < 1 && (Input.GetKey(KeyCode.DownArrow) || Input.GetKey(KeyCode.S)))
        {
            isCrouched = true;
            //controller.stepOffset = 0.1f;
            //controller.radius = 0.2f;
            controller.height = 1.3f;
            controller.center = new Vector3(0, -0.35f, 0);
            if (!GetSpeedReduced())
                SetSpeed(crouchSpeed);
            anim.SetBool("Crouch", true);
        }
        else
        {
            CrouchOff();
        }
    }

    public void CrouchOff()
    {
        anim.SetBool("Crouch", false);

        isCrouched = false;
        controller.stepOffset = 0f;
        controller.radius = 0.36f;
        controller.center = new Vector3(0, -0.18f, 0);
        controller.height = 1.7f;
        //playerSpeed = originalSpeed;
        if (GetSpeedReduced() && !onGoo)
            SetSpeed(GetOriginalSpeed());
    }

    public void Paralysis(bool paralyze)
    {
        if (paralyze)
        {

            controllable = false;
            //anim.SetFloat("Speed", Mathf.Lerp(GameManager.instance.playerScript.anim.GetFloat("Speed"), 0, GameManager.instance.playerScript.animSpeed * Time.deltaTime));
            anim.SetFloat("Speed", 0f);
            //jumpHeight = 0;
            anim.SetBool("IsJump", false);
            anim.SetBool("Falling?", false);
            canInvisible = false;
            isInvisible = false;
            //GameManager.instance.invisBar.stop = true;
            GameManager.instance.player.gameObject.layer = 0;
            isParalyzed = true;
            playerVelocity.y += gravityValue * Time.deltaTime;
            controller.Move(playerVelocity * Time.deltaTime);
        }
        else
        {

            controllable = true;
            canInvisible = true;
            isParalyzed = false;
            SetPlayerMaterial(visible);
            //GameManager.instance.invisBar.stop = false;
            //jumpHeight = 2;
        }


    }
    public void FallingDown()
    {
        playerVelocity.y += gravityValue * Time.deltaTime;
        controller.Move(playerVelocity * Time.deltaTime);
    }


    //Interactions
    void Interact()
    {
        if (doorInteract)
            EventManager.instance.OnDoorInteract();

        if (lockerInteract)
            EventManager.instance.OnLockerInteract();

        if (switchInteract)
            EventManager.instance.OnSwitchInteract();

        if (TeleportInteract)
            EventManager.instance.OnTeleportInteract();

        //if (objectInteract)
        //    EventManager.instance.OnObjectInteract(throwForce);
    }

    // ControllerCollider Interactions - Push    
    // Colision only sets moveableObjectCollision bool, push logic in Update()
    private void OnControllerColliderHit(ControllerColliderHit hit)
    {
        // This checks if the Player is already moving an object while colliding another
        if (child == null)
        {
            Ray frontray = new Ray(transform.position + Vector3.up * -0.9f, transform.forward);
            if (!Physics.Raycast(frontray, controller.radius + 0.01f))
                moveableObjectCollision = false;
            // This checks if the colliding object is tagged moveable
            if (hit.gameObject.CompareTag("MoveableObject") && Physics.Raycast(frontray, controller.radius + 0.01f))
            {
                moveableObjectCollision = true;
                childRB = hit.rigidbody;
            }
        }
    }

    // Setter for objects to set the player's onLadder bool
    public void OnLadder()
    {
        onLadder = true;
        canCrouch = false;
        playerVelocity = new Vector3(0f, 0f, 0f);
    }

    public void OffLadder()
    {
        onLadder = false;
        canCrouch = true;
    }

    // Setters and Getter for objects to set/get the player's hasKey bool
    public void GiveKey()
    {
        hasKey = true;
        GameManager.instance.keyCollected.gameObject.SetActive(true);
    }

    public void UseKey()
    {
        hasKey = false;
        GameManager.instance.keyCollected.gameObject.SetActive(false);
    }

    IEnumerator ResetCoolDown()
    {
        if (reset)
            yield break;
        reset = true;
         yield return new WaitForSeconds(1f);
        cooldown = false;
        reset = false;
    }
    public bool HasKey()
    {
        return hasKey;
    }

    // Getters and Setter for the players speed variable
    public float GetPlayerSpeed()
    {
        return playerSpeed;
    }
    public float GetOriginalSpeed()
    {
        return originalSpeed;
    }
    public bool GetSpeedReduced()
    {
        return reducedSpeed;
    }
    public void SetSpeed(float _speed)
    {
        playerSpeed = _speed;
    }

    public void BecomeInvisible()
    {
        GameManager.instance.invisBar.stop = false;
        if (GameManager.instance.player.gameObject.layer == 0)
        {
            GameManager.instance.player.gameObject.layer = 2;
        }
        isInvisible = true;
        SetPlayerMaterial(invisible);

        GameManager.instance.invisBar.UseInvis(invisUseAmount);
    }

    public void BecomeVisible()
    {
        GameManager.instance.invisBar.stop = true;
        if (GameManager.instance.player.gameObject.layer == 2)
        {
            GameManager.instance.player.gameObject.layer = 0;
        }
        isInvisible = false;
        SetPlayerMaterial(visible);
    }

    // Used (publicly) when reverting the colors of the player's Mesh
    public Material GetPlayerMaterial()
    {
        return visible;
    }
    public void SetPlayerMaterial(Material _material)
    {
        capsuleRenderer.material = _material;
    }

    // Push Methods
    private void PushOn()
    {



        isPushing = true;

        anim.SetBool("Pushing", true);
        //if (childRB != null && childRB.velocity.y == 0)
        //{
        //    child = childRB.gameObject;
        //    child.transform.SetParent(this.transform);
        //}
        //canJump = false;
        //canCrouch = false;
        //playerSpeed = originalSpeed / 2;

    }

    private void PushOff()
    {

        anim.SetBool("Pushing", false);

        isPushing = false;



        //if (childRB != null)
        //{
        //    childRB.transform.SetParent(null);
        //    if (Physics.Raycast(_dropMovable))
        //        //childRB.constraints = RigidbodyConstraints.FreezeAll;
        //        child = null;
        //}
        //isPushing = false;
        //canJump = true;
        //canCrouch = true;
        //playerSpeed = originalSpeed;
    }
}
