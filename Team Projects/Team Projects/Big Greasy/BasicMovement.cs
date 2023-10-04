using System.Collections;
using System.Collections.Generic;
using System.Data;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem.XR;

/***********************************************
 * Filename:  		BasicMovement.cs
 * Date:      		04/11/2023
 * Mod. Date: 		05/01/2023
 * Mod. Initials:	NB
 * Author:    		Nicolas Browning 
 ************************************************/

/// <summary>
/// Lets Player use basic movement controls 
/// </summary>
public class BasicMovement : MonoBehaviour
{
    public CharacterController g_ccCharacter;

    Vector3 m_vec3CurrentVelocity;
    public Transform g_tfCameraPos;
    public bool g_bSwitchOn = true;
    public int g_nJumpCount = 0;

    public float g_fSpeed = 6.0f;
    [SerializeField] private float m_fGravity = -9.8f;
    public float g_fJumpHeight = 6f;
    public float g_fMouseSensitivity = 2f;

    // Update is called once per frame
    void Update()
    {
        if (g_bSwitchOn)
        {
            Move();
            Jump();
            Rotate();
        }
    }

    private void Jump()
    {
        // If the player jumps and hit's their head, they will bounce off the surface
        if ((g_ccCharacter.collisionFlags & CollisionFlags.Above) != 0)
            m_vec3CurrentVelocity.y = 0;

        // Jump
        if (Input.GetButtonDown("Jump") && g_nJumpCount < 1)
        {
            m_vec3CurrentVelocity.y = Mathf.Sqrt(g_fJumpHeight);
            g_nJumpCount++;
            
            Debug.Log("jumper");
        }
        else if(g_ccCharacter.isGrounded == true && g_nJumpCount > 0)
        {
            g_nJumpCount--;
        }
        // Gravity
        //if (m_ccCharacter.isGrounded)
        //{
        //    //Debug.Log("yeah");

        //    m_vec3CurrentVelocity.y = -1f * Time.deltaTime;
        //}
        //else
        //{
        //Debug.Log("nah");
        m_vec3CurrentVelocity.y += m_fGravity * Time.deltaTime;
        g_ccCharacter.Move(m_vec3CurrentVelocity * Time.deltaTime);
        //}

    }

    private void Move()
    {
        // Get player input
        float fHorizontal = Input.GetAxis("Horizontal");
        float fVertical = Input.GetAxis("Vertical");

        // Move player based on player input
        Vector3 vec3Move = transform.forward * fVertical + transform.right * fHorizontal;
        g_ccCharacter.Move(g_fSpeed * Time.deltaTime * vec3Move);
    }

    private void Rotate()
    {
        float fHorizontal = Input.GetAxis("Mouse X");
        float fVertical = Input.GetAxis("Mouse Y");

        transform.Rotate(0, fHorizontal * g_fMouseSensitivity, 0);
        g_tfCameraPos.Rotate(-fVertical * g_fMouseSensitivity, 0, 0);

        Vector3 vec3CurrentRotation = g_tfCameraPos.localEulerAngles;
        if (vec3CurrentRotation.x > 180)
        {
            vec3CurrentRotation.x -= 360;
        }
        vec3CurrentRotation.x = Mathf.Clamp(vec3CurrentRotation.x, -89, 89);
        g_tfCameraPos.localRotation = Quaternion.Euler(vec3CurrentRotation);
    }
}
