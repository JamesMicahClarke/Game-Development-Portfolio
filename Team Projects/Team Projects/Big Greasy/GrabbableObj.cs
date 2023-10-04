using System.Collections;
using System.Collections.Generic;
using System.Linq.Expressions;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;

/***********************************************
 * Filename:  		GrabbableObject.cs
 * Date:      		04/04/2023
 * Mod. Date: 		05/03/2023
 * Mod. Initials:	JC
 * Author:    		James Clarke
 ************************************************/

/// <summary>
/// 
/// </summary>
public class GrabbableObj : MonoBehaviour
{
    Rigidbody m_rbGrabbableObjectRigidbody;
    Transform m_tfGrabPointTransform;

    public bool g_bPickedUp = false;
    public float m_fMoveSpeed = 100;
    public float m_fTimeSet = 10;
    public float m_fDropSpeed = 1;
    float timer = 0.0f;
    Vector3 vec3Startpoint;

    private void Awake()
    {
        //initialize the grabbable object's rigidbody
        m_rbGrabbableObjectRigidbody = GetComponent<Rigidbody>();
    }

    public void Grab(Transform GrabTransform)
    {
        this.m_tfGrabPointTransform = GrabTransform;
        
        //disables gravity for the object
        m_rbGrabbableObjectRigidbody.useGravity = false;

        //freezes rotation of objects
        m_rbGrabbableObjectRigidbody.freezeRotation = true;

        m_rbGrabbableObjectRigidbody.isKinematic = true;

        m_rbGrabbableObjectRigidbody.detectCollisions = false;

    }
    public void Drop()
    {
        this.m_tfGrabPointTransform = null;

        //enables gravity for the object
        m_rbGrabbableObjectRigidbody.useGravity = true;
        //unfreezes rotation of objects
        m_rbGrabbableObjectRigidbody.freezeRotation = false;

        m_rbGrabbableObjectRigidbody.isKinematic = false;

        m_rbGrabbableObjectRigidbody.detectCollisions = true;
    }

    //helper function for drop to make dropped items fall faster
    public void DropAtSpeed()
    {
        m_rbGrabbableObjectRigidbody.velocity += new Vector3(0, -m_fDropSpeed, 0);
    }

    private void FixedUpdate()
    {
        if (m_tfGrabPointTransform != null)
        {
            vec3Startpoint = transform.position;

            timer = Time.deltaTime;

            transform.rotation = Quaternion.identity;
            //Lerp from the current transform's position to the target's * deltatime * speed
            Vector3 vec3GoalPos = Vector3.Lerp(vec3Startpoint, m_tfGrabPointTransform.position, (timer / m_fTimeSet) * m_fMoveSpeed);

            //move GrabbableObjectRigidbody's position to the GrabPointTransform's position
            transform.position = vec3GoalPos;
            g_bPickedUp = true;
        }
    }
}
