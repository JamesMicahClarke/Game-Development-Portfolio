using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/***********************************************
 * Filename:  		ItemPickup.cs
 * Date:      		04/11/2023
 * Mod. Date: 		05/01/2023
 * Mod. Initials:	JC
 * Author:    		James Clarke 
 ************************************************/

/// <summary>
///  Dependent on GrabbableObj Script
/// </summary>
public class ItemPickup : MonoBehaviour
{
    [SerializeField] Transform m_tfPlayerCamTransform;
    [SerializeField] GameObject m_goGrabPoint;
    [SerializeField] LayerMask m_lmPickupLayerMask;

    GrabbableObj m_ObjGrab;

    public float g_fGrabDist = 10;
    public float g_fInteractDist = 10;
    public float g_fZForce = 10;
    public float g_fYForce = 10;

    public bool g_bHasObject;
    public LinkedList<GameObject> g_llInventory;
    //private Vector3 target;

    private void Start()
    {
        //queues up an empty inventory
        GameObject[] m_agoSpaces =
        {
            null,null,null,null,null
        };
        g_llInventory = new LinkedList<GameObject>(m_agoSpaces);
    }

    // Update is called once per frame
    void Update()
    {
        //interface stuff
        Ray rRay = Camera.main.ViewportPointToRay(new Vector3(.5f, .5f, 0));
        //Debug.DrawRay(m_PlayerCamTransform.position, m_PlayerCamTransform.forward, Color.red, 100);

        if (Physics.Raycast(rRay, out RaycastHit rhHitbed, g_fInteractDist))
        {
            LookAtAble(rhHitbed.collider.gameObject);
        }
        if (Input.GetKeyDown(KeyCode.J))
        {
            Debug.Log("it was called");

            if (Physics.Raycast(rRay, out RaycastHit rhHit, g_fInteractDist))
            {
                Interactable(rhHit.collider.gameObject);
            }
        }
        if (Input.GetButtonDown("Interact"))
        {
            PickUp();
        }

        if (Input.GetButtonDown("Throw"))
        {
            if (g_bHasObject)
            {
                Throw();
            }
        }
        if (g_bHasObject && Input.GetButtonDown("Inventory"))
        {
            AddItem();
        }
        else if (g_llInventory.First.Value != null)
        {
            if (!g_bHasObject && Input.GetKeyDown(KeyCode.F))
            {
                ProduceItem();
            }
        }
    }

    #region Interface IInteract Functions
    //interfacestuff
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
    #endregion

    #region Player Pickup Functions
    private void ItemDrop()
    {
        m_ObjGrab.Drop();
        m_goGrabPoint.transform.DetachChildren();

        g_bHasObject = false;
        m_ObjGrab = null;
    }
    private void Throw()
    {
        m_ObjGrab.GetComponent<Rigidbody>().velocity += m_ObjGrab.transform.parent.transform.forward * g_fZForce + m_ObjGrab.transform.parent.transform.up * g_fYForce;
        ItemDrop();
    }
    private void PickUp()
    {

        //Using Raycast to track the transform of the player
        if (Physics.Raycast(m_tfPlayerCamTransform.position, m_tfPlayerCamTransform.forward, out RaycastHit rhRayHit, g_fGrabDist))
        {
            //if there's no object currently being held, then grab otherwise drop
            if (m_ObjGrab == null)
            {
                //check for the component (script) of the grabbable object //this allows for objects with this script to be identified rather than all objects.
                if (rhRayHit.transform.TryGetComponent(out m_ObjGrab))
                {
                    m_ObjGrab.Grab(m_goGrabPoint.transform);
                    m_goGrabPoint.SetActive(true);
                    g_bHasObject = true;
                    m_ObjGrab.transform.SetParent(m_goGrabPoint.transform);
                }
            }
            else
            {
                ItemDrop();
            }
        }
    }
    #endregion

    //First item does not appear directly in front of player when taken out of inventory
    //items that are not current item get detached from parent when placed in inventory

    //The first time you try to take something out of inventory it draws from original position from where
    //it was turned off
    #region Inventory Functions
    private void AddItem()
    {
        //adds item to list
        if (g_llInventory.First.Value == null)//first spot
        {
            g_llInventory.AddFirst(m_ObjGrab.gameObject);
        }
        else if (g_llInventory.First.Next.Value == null)//second spot
        {
            g_llInventory.AddAfter(g_llInventory.First, m_ObjGrab.gameObject);
        }
        else if (g_llInventory.First.Next.Next.Value == null)//third spot
        {
            g_llInventory.AddAfter(g_llInventory.First.Next, m_ObjGrab.gameObject);
        }
        else if (g_llInventory.First.Next.Next.Next.Value == null)//fourth spot
        {
            g_llInventory.AddAfter(g_llInventory.First.Next.Next, m_ObjGrab.gameObject);
        }
        else if (g_llInventory.Last.Value == null)//fifth spot
        {
            g_llInventory.AddLast(m_ObjGrab.gameObject);
        }
        else
        {
            Debug.Log("Inventory's full!!!");
            return;
        }
        //turns off item instance in level
        m_ObjGrab.gameObject.SetActive(false);
        //destroys item reference in player
        m_ObjGrab.Drop();
        g_bHasObject = false;
        //m_goGrabPoint.transform.DetachChildren();
        Debug.Log("Inventory's first object is " + g_llInventory.First.Value.name.ToString());
        Debug.Log("Inventory's second object is " + g_llInventory.First.Next.Value.name.ToString());
    }

    private void ProduceItem()
    {
        m_ObjGrab = g_llInventory.First.Value.GetComponent<GrabbableObj>();

        //target.Set(PlayerCamTransform.position.x, PlayerCamTransform.position.y, PlayerCamTransform.position.z);
        m_ObjGrab.gameObject.SetActive(true);
        m_ObjGrab.Grab(m_goGrabPoint.transform);
        m_ObjGrab.transform.SetParent(m_goGrabPoint.transform);
        g_bHasObject = true;
        g_llInventory.RemoveFirst();
    }
    #endregion

}