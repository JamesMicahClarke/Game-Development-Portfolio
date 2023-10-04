using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goo : MonoBehaviour
{
    [SerializeField] float slowRate = 2f;
    [SerializeField] bool exit;

    private void Update()
    {

        if (exit && GameManager.instance.playerScript.groundedPlayer)
        {

            GameManager.instance.playerScript.canCrouch = true;
            GameManager.instance.playerScript.canJump = true;
            if (GameManager.instance.playerScript.GetSpeedReduced())
                GameManager.instance.playerScript.SetSpeed(GameManager.instance.playerScript.GetOriginalSpeed());
            GameManager.instance.playerScript.onGoo = false;
            exit = false;

        }

    }

    private void OnTriggerStay(Collider other)
    {
        if (!GameManager.instance.playerScript.GetSpeedReduced())
        {
            if (other.CompareTag("Player"))
            {
                //GameManager.instance.playerScript.CrouchOff();
                //GameManager.instance.playerScript.canCrouch = false;
                //GameManager.instance.playerScript.canJump = false;
               
                if (GameManager.instance.playerScript.groundedPlayer)
                {
                    GameManager.instance.playerScript.onGoo = true;
                    GameManager.instance.playerScript.SetSpeed(slowRate);
                }
               
            }
        }
    }
    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            //GameManager.instance.playerScript.canCrouch = true;
            //GameManager.instance.playerScript.canJump = true;
            //if (GameManager.instance.playerScript.GetSpeedReduced())
            //    GameManager.instance.playerScript.SetSpeed(GameManager.instance.playerScript.GetOriginalSpeed());
            //GameManager.instance.playerScript.onGoo = false;
            exit = true;
        }
    }
}
