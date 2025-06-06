using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using Unity.Collections;
using Unity.VisualScripting;
using UnityEngine.Audio;
using UnityEngine.SceneManagement;
#if UNITY_EDITOR
using UnityEditor;
using UnityEditor.Animations;
using UnityEditor.Experimental.GraphView;
using System.Reflection; //debug
#endif
using UnityEngine;

/***********************************************
 * Filename:  		Player.cs
 * Date:      		05/05/2023
 * Mod. Date: 		06/27/2023
 * Mod. Initials:	JC
 * Author:    		James Clarke
 ************************************************/

/// <summary>
/// General script for Player actions
/// </summary>
public class Player : MonoBehaviour
{
    #region Player Vars
    //public static Player g_Instance;

    #region Input Vars
    public CharacterController g_ccCharacter;
    [SerializeField] Transform m_tfPlayerCamTransform;
    [SerializeField] GameObject m_goGrabPoint;
    [SerializeField] GameObject m_goThrowPoint;
    [SerializeField] public GameObject g_gointeractCanvas;
    [SerializeField] public GameObject m_goReference;
    [SerializeField] public GameObject g_goPickUpObj;

    //Audio
    [SerializeField] AudioSource m_asPlayerSFX;
    [SerializeField] List<AudioClip> m_lacPlayerClips;

    #endregion

    #region Float Vars
    public float g_fSpeed = 6.0f;
    public float g_fJumpHeight = 6f;
    public float g_fMouseSensitivity = 2f;
    [SerializeField] private float m_fGravity = -9.8f;
    //[SerializeField] private float m_fDropDist = 0;
    //[SerializeField] private float m_fUpDetect = 1;
    [SerializeField] private float m_fDownDetect = 1;


    public float g_fGrabDist = 10;
    public float g_fInteractDist = 10;
    public float g_fZForce = 10;
    public float g_fYForce = 10;
    public float g_fDownPushForce = 10;
    #endregion

    #region Bool Vars
    //Bool
    public bool g_bHasObject;
    public bool g_bIsGrounded;
    public bool g_bCanMove;
    public bool g_bPlayWalk = true;
    #endregion
    //public bool g_bJumped = false;
    //public bool shutdown = false;
    //others
    #region Other Vars
    GrabbableObj m_ObjGrab;
    Vector3 m_vec3CurrentVelocity;
    Vector3 m_vec3DropVec;

    //float m_fAudioTimer = 0;

    //animation
    //[SerializeField] Animator m_animAnime;

#if UNITY_EDITOR
    //[SerializeField] BlendTree m_btAnimBlend;
#endif
    #endregion

    #endregion
    //////////////////////////////////////////

    //Inventory Variables
    #region Inventory Vars
    LinkedList<GameObject> m_llInventory;
    LinkedListNode<GameObject> m_llnCurNode = null;
    public int g_nInvLimit = 5;
    public bool g_bScrolling = true;
    public bool g_bRemoved;
    #endregion
    //////////////////////////////////////////
    private void Awake()
    {
        m_asPlayerSFX = GetComponent<AudioSource>();
        m_llInventory = new LinkedList<GameObject>();
    }

    private void Start()
    {
        //Instantiates an empty inventory
        g_bCanMove = true;
        g_gointeractCanvas.SetActive(false);
    }


    // Update is called once per frame
    void Update()
    {
        //Basic Movement
        if (UIManager.g_Instance.g_bPaused != true && g_bCanMove)
        {
            Move();
            Jump();
            Rotate();

            //interface stuff
            //Vector3 PointRay = Physics.Raycast(m_tfPlayerCamTransform.position, m_tfPlayerCamTransform.forward, g_fInteractDist);// m_tfPlayerCamTransform.forward;
            Ray rRay = Camera.main.ViewportPointToRay(new Vector3(.5f, .5f, 1));
            if (Physics.Raycast(rRay, out RaycastHit rhHitbed, g_fInteractDist))
            {
                if (m_goReference == rhHitbed.collider.gameObject)
                {
                    LookAtAble(rhHitbed.collider.gameObject);
                }
                else
                {
                    if (m_goReference != null) // if there is a reference
                    {
                        LookingAway(m_goReference);
                    }
                    m_goReference = rhHitbed.collider.gameObject;
                }
            }

            //Interactions & Pickup
            if (Input.GetButtonDown("Interact"))
            {
                //if there's no object currently being held, then grab otherwise drop
                if (Physics.Raycast(rRay, out RaycastHit rhItemHit, g_fInteractDist) && m_llInventory.Count != g_nInvLimit)
                {
                    if (rhItemHit.collider.gameObject.layer == 3) //if on pickup layer
                    {
                        if (m_ObjGrab == null)
                        {
                            RayCastPickup();
                        }
                        else
                        {
                            if (m_ObjGrab.enabled == true)
                            {
                                AddItem();
                            }
                            RayCastPickup();
                        }

                    }
                }

                if (Physics.Raycast(rRay, out RaycastHit rhHit, g_fInteractDist))
                {
                    if (rhHit.collider.gameObject.layer != 3)
                    {
                        Interactable(rhHit.collider.gameObject);
                    }
                }
            }

            //Dropping
            if (Input.GetButtonDown("Drop"))
            {
                if (m_ObjGrab != null)
                {
                    ItemDrop();

                    if (m_llInventory.Count != 0)
                    {
                        ProduceItem();
                    }
                    g_bRemoved = true;
                }
            }

            //Throwing
            if (Input.GetButtonDown("Throw"))
            {
                if (g_bHasObject)
                {
                    Throw();

                    if (m_llInventory.Count != 0)
                    {
                        ProduceItem();
                    }
                    g_bRemoved = true;
                }
            }

            //Inventory Selection
            if (m_llInventory.Count > 0)
            {
                m_llnCurNode = SelectItem(m_llInventory, m_llnCurNode);
            }

            if (SceneManager.GetSceneByName("ResturantLevel").isLoaded) //|| SceneManager.GetSceneByName("Tutorial").isLoaded)
            {
                /// Debug.Log("we are looking for the resturant function for the image now");
                RestaurantManager.g_Instance.IsGhostInRange();
            }
        }
    }
    //Accessor Functions
    #region Accessor Functions
    public bool IsInvFull()
    {
        if (m_llInventory.Count == g_nInvLimit)
        {
            return true;
        }

        return false;
    }
    public List<GameObject> GetInventory()
    {
        return m_llInventory.ToList();
    }
    #endregion
    //////////////////////////////////////////

    //Movement Functions
    #region Movement Functions
    private AudioClip PlayerWalkSFX()
    {
        AudioClip acClip = m_lacPlayerClips[0];//Random.Range(0, m_lacPlayerClips.Count)
        return acClip;
    }
    private void Jump()
    {
        // If the player jumps and hit's their head, they will bounce off the surface
        if ((g_ccCharacter.collisionFlags & CollisionFlags.Above) != 0)
        {
            m_vec3CurrentVelocity.y = -g_fJumpHeight;
        }

        Vector3 vec3Down = new Vector3(transform.up.x, -transform.up.y, transform.up.z);
        Ray rDownRay = new Ray(transform.position + new Vector3(0, -m_fDownDetect, 0), vec3Down);

        if (Physics.Raycast(rDownRay, m_fDownDetect))
        {
            g_bIsGrounded = true;
        }
        else
        {
            g_bIsGrounded = false;
        }

        //Jump
        if (Input.GetButtonDown("Jump") && g_bIsGrounded)
        {
            //g_bJumped = true;
            m_vec3CurrentVelocity.y = Mathf.Sqrt(g_fJumpHeight);
        }

        //Audio
        //if (g_bJumped)//== true && !m_asPlayerSFX.isPlaying
        //{
        //    g_bJumped = false;
        //    if (m_asPlayerSFX.clip == null)
        //    {
        //        m_asPlayerSFX.clip = PlayerWalkSFX();
        //    }
        //    m_asPlayerSFX.PlayOneShot(m_asPlayerSFX.clip);
        //}


        //Gravity
        if (!g_bIsGrounded)
        {
            m_vec3CurrentVelocity.y += m_fGravity * Time.deltaTime;
        }
        g_ccCharacter.Move(m_vec3CurrentVelocity * Time.deltaTime);




    }

    private void Move()
    {
        // Get player input
        float fHorizontal = Input.GetAxis("Horizontal");
        float fVertical = Input.GetAxis("Vertical");

        // Move player based on player input
        Vector3 vec3Move = transform.forward * fVertical + transform.right * fHorizontal;
        g_ccCharacter.Move(g_fSpeed * Time.deltaTime * vec3Move);

        //Audio
        if (vec3Move != Vector3.zero && g_bIsGrounded && !m_asPlayerSFX.isPlaying)
        {
            g_bPlayWalk = true;
            if (g_bPlayWalk)
            {
                if (m_asPlayerSFX.clip == null)
                {
                    m_asPlayerSFX.clip = PlayerWalkSFX();
                }

                m_asPlayerSFX.PlayOneShot(m_asPlayerSFX.clip);
            }

        }
        else if (vec3Move == Vector3.zero)
        {
            if (m_asPlayerSFX.isPlaying)
            {
                m_asPlayerSFX.Stop();
            }
            g_bPlayWalk = false;
        }
    }

    private void Rotate()
    {
        float fHorizontal = Input.GetAxis("Mouse X");
        float fVertical = Input.GetAxis("Mouse Y");

        transform.Rotate(0, fHorizontal * g_fMouseSensitivity, 0);
        m_tfPlayerCamTransform.Rotate(-fVertical * g_fMouseSensitivity, 0, 0);

        Vector3 vec3CurrentRotation = m_tfPlayerCamTransform.localEulerAngles;
        if (vec3CurrentRotation.x > 180)
        {
            vec3CurrentRotation.x -= 360;
        }
        vec3CurrentRotation.x = Mathf.Clamp(vec3CurrentRotation.x, -80, 80);
        m_tfPlayerCamTransform.localRotation = Quaternion.Euler(vec3CurrentRotation);
    }
    #endregion
    //////////////////////////////////////////

    //Player Pickup Functions
    #region Player Pickup Functions
    private void ItemDrop()
    {
        //m_vec3DropVec = new Vector3(m_fDropDist, 0, 0);
        m_ObjGrab.transform.position = m_goThrowPoint.transform.position + m_vec3DropVec;
        m_ObjGrab.Drop();


        //detacthes single child obj
        m_ObjGrab.transform.parent = null;

        g_bHasObject = false;
        m_ObjGrab = null;
    }
    private void Throw()
    {

        m_ObjGrab.transform.position = m_goThrowPoint.transform.position;
        m_ObjGrab.GetComponent<Rigidbody>().velocity = (m_tfPlayerCamTransform.forward * g_fZForce) + (m_tfPlayerCamTransform.up * g_fYForce);
        ItemDrop();
    }
    public void InteractPickUp()
    {
        if (m_llInventory.Count != g_nInvLimit)
        {
            if (m_ObjGrab != null)
            {
                AddItem();
            }

            m_ObjGrab = g_goPickUpObj.GetComponent<GrabbableObj>();
            m_ObjGrab.Grab(m_goGrabPoint.transform);
            m_goGrabPoint.SetActive(true);
            g_bHasObject = true;
            m_ObjGrab.transform.SetParent(m_goGrabPoint.transform);
        }

    }
    private void RayCastPickup()
    {
        //Using Raycast to track the transform of the player
        if (Physics.Raycast(m_tfPlayerCamTransform.position, m_tfPlayerCamTransform.forward, out RaycastHit rhRayHit, g_fGrabDist))
        {
            //check for the component (script) of the grabbable object 
            //this allows for objects with this script to be identified rather than all objects.
            if (rhRayHit.transform.TryGetComponent(out m_ObjGrab))
            {
                if (m_ObjGrab.enabled == true)
                {
                    m_ObjGrab.Grab(m_goGrabPoint.transform);
                    m_goGrabPoint.SetActive(true);
                    g_bHasObject = true;
                    m_ObjGrab.transform.SetParent(m_goGrabPoint.transform);
                }

            }

        }
    }
    #endregion
    //////////////////////////////////////////

    //Interface IInteract Functions
    #region Interface IInteract Functions
    private void Interactable(GameObject goObj)
    {
        if (goObj.TryGetComponent(out IInteract I))
        {
            I.Interact();
        }
    }
    private void LookAtAble(GameObject goObj)
    {
        if (goObj.TryGetComponent(out IInteract I))
        {
            I.LookAt();
        }
    }
    private void LookingAway(GameObject goObj)
    {
        if (goObj.TryGetComponent(out IInteract I))
        {
            I.LookAway();
        }
    }
    #endregion
    //////////////////////////////////////////

    //Inventory Functions
    #region Inventory Functions



    private void AddItem()
    {
        LinkedListNode<GameObject> llnObjNode = new LinkedListNode<GameObject>(m_ObjGrab.gameObject);
        int nSlotCount = m_llInventory.Count;


        if (nSlotCount != g_nInvLimit)
        {
            //adds item being currently held to inventory
            m_llInventory.AddLast(llnObjNode);
            nSlotCount++;

            //turns off item instance in level
            m_ObjGrab.gameObject.SetActive(false);

            //removes item from hand
            m_ObjGrab = null;

            g_bHasObject = false;
        }
        else if (nSlotCount == g_nInvLimit)
        {
            if (g_bHasObject)
            {
                LinkedListNode<GameObject> tempNode = m_llInventory.First;
                SwapItem(ref m_ObjGrab, ref m_llInventory, ref tempNode);
            }
            else
            {
                Debug.Log("Full Inventory");

            }
        }
    }

    private void ProduceItem()
    {
        m_ObjGrab = m_llInventory.First.Value.GetComponent<GrabbableObj>();
        m_ObjGrab.transform.position = m_goGrabPoint.transform.position;
        m_ObjGrab.gameObject.SetActive(true);
        m_llInventory.RemoveFirst();
        g_bHasObject = true;
    }
    private void SwapItem(ref GrabbableObj GrabObj, ref LinkedList<GameObject> llList, ref LinkedListNode<GameObject> llnNode)
    {
        if (m_ObjGrab == null)
        {
            m_ObjGrab = llnNode.Value.GetComponent<GrabbableObj>();

            GrabObj.gameObject.transform.position = m_goGrabPoint.transform.position;
            GrabObj.gameObject.SetActive(true);
            g_bHasObject = true;
            llList.Remove(m_ObjGrab.gameObject);
            llnNode = null;

        }
        else
        {
            GameObject goTemp = GrabObj.gameObject;
            GrabObj.gameObject.SetActive(false);

            m_ObjGrab = llnNode.Value.GetComponent<GrabbableObj>();
            GrabObj.gameObject.transform.position = m_goGrabPoint.transform.position;
            GrabObj.gameObject.SetActive(true);
            g_bHasObject = true;
            llList.Remove(m_ObjGrab.gameObject);

            if (g_bScrolling)
            {
                llList.AddFirst(goTemp);
            }
            else
            {
                llList.AddLast(goTemp);
            }

            llnNode = null;
        }

    }

    private LinkedListNode<GameObject> SelectItem(LinkedList<GameObject> llInventory, LinkedListNode<GameObject> llnCurNode)
    {
        if (Input.GetAxis("SelectScroll") > 0)
        {
            g_bScrolling = false;

            if (llnCurNode == null)
            {
                llnCurNode = llInventory.First;
            }

            SwapItem(ref m_ObjGrab, ref llInventory, ref llnCurNode);
        }
        else if (Input.GetAxis("SelectScroll") < 0)
        {
            g_bScrolling = true;

            if (llnCurNode == null)
            {
                llnCurNode = llInventory.Last;
            }

            SwapItem(ref m_ObjGrab, ref llInventory, ref llnCurNode);
        }

        return llnCurNode;
    }
    #endregion
    public void SummonSaysMe(string text)
    {
        UIManager.g_Instance.m_goDisplayText.text = text;
        g_gointeractCanvas.SetActive(true);
    }
   public void UnSummonSaysMe()
   {
       g_gointeractCanvas.SetActive(false);
   }
}
